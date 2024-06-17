package rl.huojing.dp.adapter.objectadapter;

public class Adapter implements Target {
	private Adaptee adaptee;
	
	public Adapter(Adaptee a){
		adaptee = a;
	}
	
	public void request() {
		adaptee.specificRequest();
		System.out.println("Adapter.request() is invoked");
	}

}
