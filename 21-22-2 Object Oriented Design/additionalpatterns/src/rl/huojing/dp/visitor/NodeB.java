package rl.huojing.dp.visitor;

public class NodeB extends Node {

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}

	/**
	 * NodeB特有的商业方法
	 * @return
	 */
	public String operationB(){
		return "NodeB is visited";
	}
}
