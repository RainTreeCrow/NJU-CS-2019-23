package rl.huojing.dp.flyweight.simple;

public class FlyweightClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//创建一个享元工厂对象
		FlyweightFactory factory = new FlyweightFactory();
		//向享元工厂对象请求一个内部状态为'a'的享元对象
		Flyweight fly = factory.factory(new Character('a'));
		//以参量方式传入一个外部状态
		fly.operation("First Call");
		//向享元工厂对象请求一个内部状态为'b'的享元对象
		fly = factory.factory(new Character('b'));
		//以参量方式传入一个外部状态
		fly.operation("Second Call");
		//再向享元工厂对象请求一个内部状态为'a'的享元对象
		fly = factory.factory(new Character('a'));
		//以参量方式传入一个外部状态
		fly.operation("Third Call");
		//检查目前所有的独立的享元对象
		factory.checkFlyweight();

	}

}
