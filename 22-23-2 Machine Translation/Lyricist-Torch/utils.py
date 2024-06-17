import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from network import Model
import numpy as np
import config
import random
import glob
import re
import os
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.font_manager import FontProperties
FILE_PATH = os.path.dirname(os.path.abspath(__file__))
VEC_PATH = FILE_PATH + '/data/word2vec.txt'
myfont = FontProperties(fname=FILE_PATH + "/data/SimHei.ttf")


def train(dataset, learning_rate, total_epoch, device=None, save_epoch=5, log_step=100, check_epoch=1):
    """
    训练
    :param dataset: data.py中的Data/Lyric对象
    :param learning_rate: 学习率
    :param total_epoch: 训练的总轮数
    :param device: "cpu"/"cuda"
    :param save_epoch: 保存模型的周期
    :param log_step: 打印训练log的步数
    :param check_epoch: 用check方法查看训练效果的周期
    """
    device = device or torch.device("cuda" if torch.cuda.is_available() else "cpu")
    net = model(dataset, device=device)             # 构建网络
    model_name = dataset.singer or "pre_trained"    # 如果没有指定某位歌手名, 就加载通用的pre-trained模型
    pre_trained_model = check_pre_trained_model()   # 检查是否有已经训练过的模型
    if pre_trained_model:                           # 如果有, 就加载
        pre_trained_state_dict = torch.load(FILE_PATH + config.model_path + pre_trained_model, map_location='cpu')
        state_dict = net.state_dict()
        state_dict.update(pre_trained_state_dict)
        net.load_state_dict(state_dict)
        if dataset.singer:
            start_epoch = 0                         # 如果指定了歌手(fine-tune), 就从第0轮开始训练
        else:
            # 如果是预训练, 从预训练的轮次开始训练
            start_epoch = int(re.findall("\d+", pre_trained_model)[0])
    else:
        start_epoch = 0
    # 设置loss的权重, <go>/<unk>/<pad>不会对损失有贡献
    loss_weight = torch.ones(dataset.target_vocab_size).to(device)
    loss_weight[dataset.stoi["<go>"]] = 0
    loss_weight[dataset.stoi["<unk>"]] = 0
    loss_weight[dataset.stoi["<pad>"]] = 0
    # loss function
    criterion = nn.NLLLoss(reduction='mean', weight=loss_weight)
    # optimizer
    optimizer = optim.Adam(net.parameters(), lr=learning_rate)
    net.train()
    for epoch in range(start_epoch, total_epoch):
        total_loss = 0                              # 平均Loss
        if epoch % config.decay_epoch == 0:         # loss衰减
            learning_rate = learning_rate * config.decay_rate
            print("current lr:", learning_rate)
            optimizer = optim.Adam(net.parameters(), lr=learning_rate)
        if epoch % save_epoch == 0 and epoch > start_epoch:     # 保存模型
            torch.save(state_dict_without_embedding(net),
                       FILE_PATH + config.model_path + model_name + '_%d.pkl' % epoch)
        for step, batch in enumerate(dataset.data_iter):        # 迭代
            # 获取每个batch的输入、和目标
            encoder_input, encoder_length = batch.encoder
            decoder_input, decoder_length = batch.decoder
            target = batch.target
            logists = net(encoder_input, encoder_length, decoder_input, decoder_length)     # 网络输出
            logists = F.log_softmax(logists, dim=2)             # Log Softmax
            loss = criterion(logists.permute(0, 2, 1), target[:, :logists.shape[1]])
            optimizer.zero_grad()
            loss.backward()
            nn.utils.clip_grad_norm_(net.parameters(), config.clip_grad)    # 防止梯度爆炸
            optimizer.step()
            total_loss += loss.cpu().data.numpy()
            if step % log_step == 0:
                if step > 0:
                    print("epoch", epoch, "step", step, "loss:", total_loss / log_step)     # 显示平均Loss
                    total_loss = 0
                elif step == 0 and epoch % check_epoch == 0:
                    # 随机显示一条语料的输入、输出, 方便了解网络效果
                    check(dataset, net, encoder_input, encoder_length, decoder_input, decoder_length, target)


def model(dataset, model_name=None, device=None, train=True):
    """加载模型"""
    device = device or torch.device("cuda" if torch.cuda.is_available() else "cpu")
    net = Model(vocab_size=dataset.vocab_size, embedding_dim=config.embedding_dim,
                output_size=dataset.target_vocab_size,
                encoder_hidden_size=config.encoder_hidden_size, decoder_hidden_size=config.decoder_hidden_size,
                encoder_layers=config.encoder_layers, decoder_layers=config.decoder_layers,
                dropout=config.dropout, embedding_weights=dataset.vector_weights, device=device)
    if model_name:  # 如果指定了模型名称, 就加载对应的模型
        pre_trained_state_dict = torch.load(FILE_PATH + config.model_path + model_name, map_location=device)
        state_dict = net.state_dict()
        state_dict.update(pre_trained_state_dict)
        net.load_state_dict(state_dict)
    net.train() if train else net.eval()
    return net


def state_dict_without_embedding(net):
    """在保存和加载网络模型时要去掉庞大的embedding, 因为它是通过word2vec格式保存, 不参与网络训练"""
    state_dict = net.state_dict()
    for s in state_dict.copy().keys():
        if "embedding" in s:
            state_dict.pop(s)
    return state_dict


def check_pre_trained_model():
    """检查最近一次保存的pre-trained model"""
    if not os.path.exists(FILE_PATH + config.model_path):
        os.mkdir(FILE_PATH + config.model_path)
        print("path '%s' doesn't exist, create it." % config.model_path)
    file_names = glob.glob(FILE_PATH + config.model_path + "pre_trained_*.pkl")
    if len(file_names) == 0:
        print("there isn't any pre-trained model in path '%s'" % (FILE_PATH + config.model_path))
        return None
    else:
        model_epoch = sorted([int(re.findall("\d+", n)[0]) for n in file_names])
        max_epoch = max(model_epoch)
        print("the latest pre-trained model is pre_trained_%d.pkl" % max_epoch)
        return "pre_trained_%d.pkl" % max_epoch


def check(dataset, net, encoder_input, encoder_length, decoder_input, decoder_length, target):
    """在train阶段随机显示一条语料的输入、输出, 方便了解网络效果"""
    sample = np.random.randint(encoder_input.shape[0])
    encoder_input = encoder_input[sample: sample + 1]
    encoder_length = encoder_length[sample: sample + 1]
    decoder_input = decoder_input[sample: sample + 1]
    decoder_length = decoder_length[sample: sample + 1]
    target = target[sample: sample + 1]
    input_text = [dataset.itos[i] for i in encoder_input[0][:encoder_length[0]]]
    input_target = [dataset.itos[i] for i in decoder_input[0][:decoder_length[0]]]
    net.eval()
    prediction = net(encoder_input, encoder_length, decoder_input, decoder_length)
    net.train()
    target = [dataset.itos[i] for i in target[0][:decoder_length[0]-1]]
    prediction = [dataset.itos[i] for i in prediction.argmax(2)[0][:decoder_length[0]-1]]
    print("encoder输入:", input_text)
    print("decoder输入:", input_target)
    print("target目标:", target)
    print("预测结果:", prediction)
    print("attention:\n", net.attn.attention[0, :, :, 0])


def attention_visualization(dataset, net, input_sentence, output_sentence=None, figsize=None, file_name=None):
    """
    注意力可视化
    :param dataset: data.py中的Data/Lyric对象
    :param net: network.py中的Model对象
    :param input_sentence: encoder文本, list格式, list的元素为str格式
    :param output_sentence: decoder输入文本, list格式, list的元素为str格式, 默认为None
    :param figsize: 图像大小
    :param file_name: 图片保存的名称
    """
    s = []
    attention = []
    encoder_input = dataset.process(input_sentence)
    tokens = dataset.ENCODER.preprocess(input_sentence)
    if output_sentence:
        output_sentence = dataset.ENCODER.preprocess(output_sentence) + ["<eos>"]
    output = net.predict(encoder_input)
    attention.append(net.attn.attention.cpu().view(1, -1).detach().numpy())
    word = dataset.logist2word(output)[0]
    if word[0] in dataset.itos[:20]:
        word = dataset.logist2word(output, topn=3)
        word = random.choice(word)
    if output_sentence:
        word = output_sentence[len(s)]
    next_input = dataset.stoi[word]
    s.append(word)
    while word != "<eos>":
        output = net.next(next_input)
        word = dataset.logist2word(output)[0]
        if output_sentence:
            word = output_sentence[len(s)]
        next_input = dataset.stoi[word]
        s.append(word)
        attention.append(net.attn.attention.cpu().view(1, -1).detach().numpy())
    attention = np.concatenate(attention[:-1])
    s = s[:-1]
    plt.figure(dpi=100)
    if figsize:
        f, ax = plt.subplots(figsize=figsize)
    else:
        f, ax = plt.subplots()
    sns.heatmap(attention, square=True, vmax=0.5, cmap="Reds", cbar=False)
    ax.set_xticklabels(tokens, fontsize=10, fontproperties=myfont)
    ax.xaxis.set_ticks_position('top')
    ax.set_yticklabels(s, fontsize=10, rotation=0, fontproperties=myfont)
    if file_name:
        plt.savefig(FILE_PATH + "/images/" + file_name)
    plt.show()
