package rl.huojing.dp.visitor;

public interface Visitor {
	/**
	 * ��Ӧ��NodeA�ķ��ʲ���
	 */
	void visit(NodeA node);
	
	/**
	 * ��Ӧ��NodeB�ķ��ʲ���
	 * @param node
	 */
	void visit(NodeB node);
}
