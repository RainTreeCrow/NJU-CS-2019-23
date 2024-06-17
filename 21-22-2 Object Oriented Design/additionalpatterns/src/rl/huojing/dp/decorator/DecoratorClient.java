package rl.huojing.dp.decorator;

public class DecoratorClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Work squarePeg = new SquarePeg(); 
		squarePeg.insert();
		
		System.out.println("add a decorator, do it again:");
		Work decorator1 = new ConcreteDecorator1(squarePeg);
		decorator1.insert(); 
		
		System.out.println("add another decorator, do it again:");
		Work decorator2 = new ConcreteDecorator2(decorator1);
		decorator2.insert();
	}

}
