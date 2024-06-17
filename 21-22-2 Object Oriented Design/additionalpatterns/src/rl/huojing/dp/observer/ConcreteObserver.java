package rl.huojing.dp.observer;

public class ConcreteObserver implements Observer {

	public void update(String str) {
	   System.out.println("Updated Status: "+str);
	}

}
