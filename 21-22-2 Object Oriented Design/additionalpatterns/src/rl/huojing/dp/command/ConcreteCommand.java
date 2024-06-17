package rl.huojing.dp.command;

public class ConcreteCommand implements Command {
	private Receiver receiver;
	
	public ConcreteCommand(Receiver receiver){
		this.receiver = receiver;
	}
	
	public void execute() {
		receiver.action();
	}

}
