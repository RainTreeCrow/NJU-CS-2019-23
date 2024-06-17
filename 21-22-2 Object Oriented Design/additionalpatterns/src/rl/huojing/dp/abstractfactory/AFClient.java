package rl.huojing.dp.abstractfactory;

public class AFClient {
	public static void main(String[] args){
		AbstractFactory af1 = new ConcreteFactory1();
		AbstractProductA aa = af1.createProductA();
		aa.operationA();
		AbstractProductB bb = af1.createProductB();
		bb.opeartionB();
		
		AbstractFactory af2 = new ConcreteFactory2();
		aa = af2.createProductA();
		aa.operationA();
		bb = af2.createProductB();
		bb.opeartionB();
	}
}
