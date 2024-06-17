package rl.huojing.dp.visitor;

public class VisitorA implements Visitor {

	public void visit(NodeA node) {
		System.out.println("VisitorA: "+node.operationA());
	}

	public void visit(NodeB node) {
		System.out.println("VisitorA: "+node.operationB());

	}

}
