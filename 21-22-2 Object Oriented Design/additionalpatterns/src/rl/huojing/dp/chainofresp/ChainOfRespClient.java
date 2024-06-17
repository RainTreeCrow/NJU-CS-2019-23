package rl.huojing.dp.chainofresp;

public class ChainOfRespClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Handler handler1,handler2,handler3;
		handler1 = new ConcreteHandler1();
		handler2 = new ConcreteHandler2();
		handler3 = new ConcreteHandler1();
		handler1.setSuccessor(handler2);
		handler2.setSuccessor(handler3);
		handler1.handleRequest();
		handler2.handleRequest();
		handler3.handleRequest();

	}

}
