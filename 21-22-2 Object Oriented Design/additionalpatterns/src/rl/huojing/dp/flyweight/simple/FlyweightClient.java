package rl.huojing.dp.flyweight.simple;

public class FlyweightClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//����һ����Ԫ��������
		FlyweightFactory factory = new FlyweightFactory();
		//����Ԫ������������һ���ڲ�״̬Ϊ'a'����Ԫ����
		Flyweight fly = factory.factory(new Character('a'));
		//�Բ�����ʽ����һ���ⲿ״̬
		fly.operation("First Call");
		//����Ԫ������������һ���ڲ�״̬Ϊ'b'����Ԫ����
		fly = factory.factory(new Character('b'));
		//�Բ�����ʽ����һ���ⲿ״̬
		fly.operation("Second Call");
		//������Ԫ������������һ���ڲ�״̬Ϊ'a'����Ԫ����
		fly = factory.factory(new Character('a'));
		//�Բ�����ʽ����һ���ⲿ״̬
		fly.operation("Third Call");
		//���Ŀǰ���еĶ�������Ԫ����
		factory.checkFlyweight();

	}

}
