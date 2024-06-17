package rl.huojing.dp.visitor;

public interface Visitor {
	/**
	 * 对应于NodeA的访问操作
	 */
	void visit(NodeA node);
	
	/**
	 * 对应于NodeB的访问操作
	 * @param node
	 */
	void visit(NodeB node);
}
