package rl.huojing.dp.strategy;

public abstract class DiscountStrategy {
	protected float price = 0;
	protected int copies = 0;
	
	public abstract float calculateDiscount();
	
	public DiscountStrategy(float price, int copies){
		this.price = price;
		this.copies = copies;
	}
}
