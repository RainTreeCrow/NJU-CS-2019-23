package rl.huojing.dp.observer.lib;

public class Tester {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Watched watched = new Watched();
		Watcher watcher = new Watcher(watched);
		watched.changeData("In C, we create bugs.");
		watched.changeData("In Java, we inherit bugs.");
		watched.changeData("In Java, we inherit bugs.");
		watched.changeData("In Visual Basic, we visualize bugs.");
	}

}
