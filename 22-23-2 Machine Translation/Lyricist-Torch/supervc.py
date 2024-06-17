import torch
from data import Lyric
from config import fix_length, output_size
from utils import train


learning_rate = 5e-4
total_epoch = 101
batch_size = 256
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")


if __name__ == "__main__":
    singer = "邓丽君"
    print("fine tune:" + singer)
    dataset = Lyric(batch_size=batch_size,
                    fix_length=fix_length,
                    singer=singer,
                    target_vocab_size=output_size,
                    device=device)
    train(dataset, learning_rate, total_epoch, device, save_epoch=total_epoch-1, log_step=5, check_epoch=5)
