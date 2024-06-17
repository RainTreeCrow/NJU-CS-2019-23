package rl.huojing.dp.command;

public class CommandClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Receiver receiver = new Receiver();
		Command cmd = new ConcreteCommand(receiver);
		Invoker invoker = new Invoker(cmd);
		invoker.action();
	}

}
