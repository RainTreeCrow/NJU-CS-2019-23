package rl.huojing.dp.bridge;

public abstract class Coffee {
    CoffeeImp coffeeImp;
    
    public Coffee(CoffeeImp coffeeImp){
    	setCoffeeImp(coffeeImp);
    }
    
    public void setCoffeeImp(CoffeeImp coffeeImp){
    	this.coffeeImp = coffeeImp;
    }
    public CoffeeImp getCoffeeImp(){
    	return this.coffeeImp;
    }
    public abstract void pourCoffee();
}
