package rl.huojing.dp.flyweight.composite;

public class CompositeFlyweightClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//�����Ԫ��������
		FlyweightFactorySingleton factory = FlyweightFactorySingleton.getInstance();
		//����Ԫ������������һ���ڲ�״̬Ϊ"abacc"�ĸ�����Ԫ����
		Flyweight fly = factory.factory("abacc");
		//�Բ�����ʽ�����ⲿ״̬
		fly.operation("composite call");
		//�鿴�����м�����Ԫ���󱻴���
		factory.checkFlyweight();	

	}

}
