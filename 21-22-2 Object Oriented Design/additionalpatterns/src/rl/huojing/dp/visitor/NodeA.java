package rl.huojing.dp.visitor;

public class NodeA extends Node {

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
	
	/**
	 * NodeA特有的商业方法
	 * @return
	 */
	public String operationA(){
		return "NodeA is visited";
	}

}
