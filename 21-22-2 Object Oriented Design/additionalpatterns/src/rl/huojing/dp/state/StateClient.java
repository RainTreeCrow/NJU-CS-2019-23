package rl.huojing.dp.state;

public class StateClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Context cxt = new Context();
		State state1 = new ConcreteState1();
		cxt.setState(state1);
		cxt.request();
		State state2 = new ConcreteState2();
		cxt.setState(state2);
		cxt.request();

	}

}
