package rl.huojing.dp.visitor;

public class NodeB extends Node {

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}

	/**
	 * NodeB���е���ҵ����
	 * @return
	 */
	public String operationB(){
		return "NodeB is visited";
	}
}
