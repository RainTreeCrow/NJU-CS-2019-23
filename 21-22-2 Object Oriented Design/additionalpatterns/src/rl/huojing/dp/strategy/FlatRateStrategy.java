package rl.huojing.dp.strategy;

public class FlatRateStrategy extends DiscountStrategy {

	private float amount;
	
	public FlatRateStrategy(float price, int copies, float amount) {
		super(price, copies);
		this.amount = amount;
	}

	/**
	public void setAmount(float amount){
		this.amount = amount;
	}

	public float getAmount(){
		return this.amount;
	}	
	**/
	
	@Override
	public float calculateDiscount() {
		return copies*amount;
	}

}
