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
	 * ִ�з��ʲ���
	 * @param visitor
	 */
	public void action(Visitor visitor){
		for(Enumeration<Node> e = nodes.elements(); e.hasMoreElements();){
			node = (Node)e.nextElement();
			node.accept(visitor);
		}
	}
	
	/**
	 * ����һ����Ԫ��
	 * @param node
	 */
	public void add(Node node){
		nodes.addElement(node);
	}
}
