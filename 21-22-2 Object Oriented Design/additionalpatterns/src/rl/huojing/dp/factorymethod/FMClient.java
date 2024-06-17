package rl.huojing.dp.factorymethod;

public class FMClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Creator lnkCreator = new ConcreteCreator1();
		lnkCreator.operateProduct();

	}

}
