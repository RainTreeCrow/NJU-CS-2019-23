package rl.huojing.dp.visitor;

public abstract class Node {
	/**
	 * accept����
	 * @param visitor
	 */
	public abstract void accept(Visitor visitor);
}
