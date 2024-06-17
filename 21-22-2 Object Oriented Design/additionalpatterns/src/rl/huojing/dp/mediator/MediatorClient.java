package rl.huojing.dp.mediator;

public class MediatorClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ConcreteMediator mediator = new ConcreteMediator();
		mediator.createConcreteMediator();
		Colleague c1 = new Colleague1(mediator);
		Colleague c2 = new Colleague2(mediator);
		mediator.colleagueChanged(c1);
	}

}
