package rl.huojing.dp.observer.variation;

public class VarObserverClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ConcreteSubject subject = new ConcreteSubject();
		Observer obs1 = new ConcreteObserver();
		Observer obs2 = new ConcreteObserver();
		subject.attach(obs1);
		subject.attach(obs2);
		subject.changeState("new state");

	}

}
