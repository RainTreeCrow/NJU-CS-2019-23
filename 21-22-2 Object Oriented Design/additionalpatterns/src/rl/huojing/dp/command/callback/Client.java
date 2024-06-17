package rl.huojing.dp.command.callback;

public class Client {
	public static void main(String[] args){
		Command cmd = new Command(){
			private String str = "";
			public void setStr(String s){
				str = s;
			}
			public void execute(){
				System.out.println("Printing Content = "+str);
			}
		};
		cmd.setStr("Degraded command pattern is similar to Java callback");
		Invoker invoker = new Invoker();
		invoker.startPrint(cmd);
	}
}
