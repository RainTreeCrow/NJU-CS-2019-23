package rl.huojing.dp.visitor;

import java.util.Enumeration;
import java.util.Vector;

public class ObjectStructure {

	private Vector<Node> nodes;
	private Node node;
	
	public ObjectStructure(){
		nodes = new Vector<Node>();
	}
	
	/**
	 * 执行访问操作
	 * @param visitor
	 */
	public void action(Visitor visitor){
		for(Enumeration<Node> e = nodes.elements(); e.hasMoreElements();){
			node = (Node)e.nextElement();
			node.accept(visitor);
		}
	}
	
	/**
	 * 增加一个新元素
	 * @param node
	 */
	public void add(Node node){
		nodes.addElement(node);
	}
}
