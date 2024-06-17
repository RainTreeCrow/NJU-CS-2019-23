package rl.huojing.dp.adapter.objectadapter;

public class ObjAdapterClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		Target theTarget = new Adapter(new Adaptee());
		theTarget.request();
		
		Target anotherTarget = new Adapter(new SubAdaptee());
		anotherTarget.request();
	}

}
