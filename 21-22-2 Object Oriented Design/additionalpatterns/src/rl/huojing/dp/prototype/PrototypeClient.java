package rl.huojing.dp.prototype;

public class PrototypeClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws CloneNotSupportedException{
//		Prototype p1 = new ConcretePrototype1();
//		Prototype p2 = new ConcretePrototype2();
//		Prototype gp1 = p1.getClone();
//		Prototype gp2 = p2.getClone();
//		
//		gp1.operation();
//		gp2.operation();
//		
//		ConcretePrototype1 p_origin = new ConcretePrototype1();
//		p_origin.init();
//		ConcretePrototype1 p_copy = (ConcretePrototype1) p_origin.getClone();
//		System.out.println(p_copy.getProto_int());
//		System.out.println(p_copy.getProto_string());
//		System.out.println(p_copy.getProto_List());
//		
//		System.out.println(p_origin.getProto_int());
//		System.out.println(p_origin.getProto_string());
//		System.out.println(p_origin.getProto_List());
		
		ConcretePrototype2 p_origin2 = new ConcretePrototype2();
		p_origin2.init();
		ConcretePrototype2 p_copy2 = (ConcretePrototype2) p_origin2.getClone();
		p_copy2.setProto_int(10);
		p_copy2.setProto_string("new_string");
		p_copy2.addProto_List("another string");
		System.out.println(p_copy2.getProto_int());
		System.out.println(p_copy2.getProto_string());
		System.out.println(p_copy2.getProto_List());
		
		System.out.println(p_origin2.getProto_int());
		System.out.println(p_origin2.getProto_string());
		System.out.println(p_origin2.getProto_List());
	}

}
