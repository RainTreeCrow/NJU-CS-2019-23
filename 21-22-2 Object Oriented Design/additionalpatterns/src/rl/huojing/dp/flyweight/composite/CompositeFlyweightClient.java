package rl.huojing.dp.flyweight.composite;

public class CompositeFlyweightClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//获得享元工厂对象
		FlyweightFactorySingleton factory = FlyweightFactorySingleton.getInstance();
		//向享元工厂对象请求一个内部状态为"abacc"的复合享元对象
		Flyweight fly = factory.factory("abacc");
		//以参量方式传入外部状态
		fly.operation("composite call");
		//查看到底有几个享元对象被创建
		factory.checkFlyweight();	

	}

}
