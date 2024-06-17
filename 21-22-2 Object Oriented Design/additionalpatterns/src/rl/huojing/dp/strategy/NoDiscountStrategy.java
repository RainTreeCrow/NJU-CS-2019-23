package rl.huojing.dp.strategy;

public class NoDiscountStrategy extends DiscountStrategy {

	public NoDiscountStrategy(float price, int copies) {
		super(price, copies);		
	}

	@Override
	public float calculateDiscount() {		
		return 0;
	}

}
