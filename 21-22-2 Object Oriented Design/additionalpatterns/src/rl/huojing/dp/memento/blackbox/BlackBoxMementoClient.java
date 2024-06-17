package rl.huojing.dp.memento.blackbox;

public class BlackBoxMementoClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Originator o = new Originator();
		Caretaker c = new Caretaker();
		o.setState("On");
		c.saveMemento(o.createMemento());
		o.setState("Off");
		o.restoreMemento(c.retrieveMemento());
		System.out.println("Current State: "+o.getState());
	}

}
