package rl.huojing.dp.prototype.prototypemanager;

public class Client {
	private PrototypeManager mgr;
	private Prototype prototype;
	public void registerPrototype(){
		prototype = new ConcretePrototype();
		Prototype copytype = (Prototype)prototype.clone();
		mgr.add(copytype);
	}
}
