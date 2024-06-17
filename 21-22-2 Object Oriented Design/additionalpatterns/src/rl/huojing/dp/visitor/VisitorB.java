package rl.huojing.dp.visitor;

public class VisitorB implements Visitor {

	public void visit(NodeA node) {
		System.out.println("VisitorB: "+node.operationA());
	}

	public void visit(NodeB node) {
		System.out.println("VisitorB: "+node.operationB());

	}

}
