package rl.huojing.dp.prototype;

import java.util.ArrayList;

public class ConcretePrototype1 implements Prototype {
	private ArrayList<String> proto_list = new ArrayList<String>();
	private int proto_int;
	private String proto_string;
	public Prototype getClone() {
		return new ConcretePrototype1();
	}
	
	public void init()
	{
		proto_list.clear();
		proto_list.add("one string");
		proto_int = -1;
		proto_string = "init_string";
	}
	
	public void operation() {
		System.out.println("ConcretePrototype1.operation() executed");
	}

	public int getProto_int() {
		return proto_int;
	}

	public void setProto_int(int proto_int) {
		this.proto_int = proto_int;
	}

	public String getProto_string() {
		return proto_string;
	}

	public void setProto_string(String proto_string) {
		this.proto_string = proto_string;
	}
	
	public void addProto_List(String one_element){
		proto_list.add(one_element);
	}
	public ArrayList<String> getProto_List(){
		return this.proto_list;
	}
}
