package rl.huojing.dp.templatemethod;

public class TemplateMethodClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		AbstractClass c1 = new ConcreteClass1();
		c1.templateMethod();
		System.out.println("===================");
		AbstractClass c2 = new ConcreteClass2();
		c2.templateMethod();

	}

}
