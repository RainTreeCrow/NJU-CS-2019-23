package rl.huojing.dp.bridge;

public class MediumCoffee extends Coffee {

	public MediumCoffee(CoffeeImp coffeeImp) {
		super(coffeeImp);		
	}

	@Override
	public void pourCoffee() {
		for(int i=0;i<2;i++){
			System.out.print(i+": ");
			coffeeImp.pourCoffeeImp();
		}
		
	}

}
