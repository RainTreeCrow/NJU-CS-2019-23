package rl.huojing.dp.visitor;

public class VisitorClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//创建一个结构对象
		ObjectStructure aObjects = new ObjectStructure();
		//增加节点
		aObjects.add(new NodeA());
		aObjects.add(new NodeB());
		aObjects.add(new NodeA());
		//创建一个访问者
		Visitor visitor1 = new VisitorA();
		//让访问者访问结构
		aObjects.action(visitor1);
		//创建一个新的访问者
		Visitor visitor2 = new VisitorB();
		//让新的访问者访问结构
		aObjects.action(visitor2);
	}

}
