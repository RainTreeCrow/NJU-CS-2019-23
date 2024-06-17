package rl.huojing.dp.command.callback;

public class Invoker {
	public void startPrint(Command cmd){
		System.out.println("---Before service---");
		cmd.execute();
		System.out.println("---After service---");
	}
}
