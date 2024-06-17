package rl.huojing.dp.visitor;

public class VisitorClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//����һ���ṹ����
		ObjectStructure aObjects = new ObjectStructure();
		//���ӽڵ�
		aObjects.add(new NodeA());
		aObjects.add(new NodeB());
		aObjects.add(new NodeA());
		//����һ��������
		Visitor visitor1 = new VisitorA();
		//�÷����߷��ʽṹ
		aObjects.action(visitor1);
		//����һ���µķ�����
		Visitor visitor2 = new VisitorB();
		//���µķ����߷��ʽṹ
		aObjects.action(visitor2);
	}

}
