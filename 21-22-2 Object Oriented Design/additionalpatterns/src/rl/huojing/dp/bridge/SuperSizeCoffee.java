package rl.huojing.dp.bridge;

public class SuperSizeCoffee extends Coffee {
	
	public SuperSizeCoffee(CoffeeImp coffeeImp) {
		super(coffeeImp);		
	}

	@Override
	public void pourCoffee() {
		for(int i=0;i<5;i++){
			System.out.print(i+": ");
			coffeeImp.pourCoffeeImp();
		}

	}

}
