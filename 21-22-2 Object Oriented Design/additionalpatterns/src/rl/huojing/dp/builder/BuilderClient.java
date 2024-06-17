package rl.huojing.dp.builder;

public class BuilderClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Builder builder = new ConcreteBuilder1();
		Director director = new Director(builder);
		director.construct();
		Product product = builder.getResult();
	}

}
