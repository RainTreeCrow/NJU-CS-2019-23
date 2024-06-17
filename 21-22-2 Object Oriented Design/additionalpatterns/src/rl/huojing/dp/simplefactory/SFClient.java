package rl.huojing.dp.simplefactory;

public class SFClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//Fruit f = new Apple();
		try{
			Fruit f1 = FruitGardener.factory("Apple");
			f1.plant();
			Fruit f2 = FruitGardener.factory("Grape");
			f2.grow();
			Fruit f3 = FruitGardener.factory("Strawberry");
			f3.harvest();
			Fruit f4 = FruitGardener.factory("Banana");
			f4.harvest();
		}
		catch(BadFruitException e){
			System.out.println(e.getMessage());
		}
	}

}
