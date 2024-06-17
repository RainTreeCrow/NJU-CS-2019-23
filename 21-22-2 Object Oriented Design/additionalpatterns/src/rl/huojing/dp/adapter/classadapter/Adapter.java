package rl.huojing.dp.adapter.classadapter;

public class Adapter extends Adaptee implements Target {

	public void request() {
		super.specificRequest();
		System.out.println("Adapter.request() is invoked");
	}

}
