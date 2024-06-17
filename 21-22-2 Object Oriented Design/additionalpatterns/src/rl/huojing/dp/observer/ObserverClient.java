package rl.huojing.dp.observer;

public class ObserverClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ConcreteSubject subject = new ConcreteSubject();
		Observer obs1 = new ConcreteObserver();
		Observer obs2 = new ConcreteObserver();
		subject.attach(obs1);
		subject.attach(obs2);
		subject.changeState("changed");
	}

}
