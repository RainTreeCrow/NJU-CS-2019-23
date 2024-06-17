package rl.huojing.dp.bridge;

public class CoffeeCustom {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("order a medium cup of milk coffee:");
		CoffeeImp milkCoffee = new MilkCoffeeImp();
		Coffee medimuMilkCoffee= new MediumCoffee(milkCoffee);
		medimuMilkCoffee.pourCoffee();
		
		System.out.println("order a super size cup of balck coffee:");
		CoffeeImp balckCoffee = new BlackCoffeeImp();
		Coffee superBlackCoffee= new SuperSizeCoffee(balckCoffee);
		superBlackCoffee.pourCoffee();
		
		

	}

}
