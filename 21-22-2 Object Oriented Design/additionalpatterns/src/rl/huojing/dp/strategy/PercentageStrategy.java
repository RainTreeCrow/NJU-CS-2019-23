package rl.huojing.dp.strategy;

public class PercentageStrategy extends DiscountStrategy {
	
	private float percent;

	public PercentageStrategy(float price, int copies, float percent) {
		super(price, copies);		
		this.percent = percent;
	}
	
	public void setPercent(float percent){
		this.percent = percent;
	}
	
	public float getPercent(){
		return this.percent;
	}

	@Override
	public float calculateDiscount() {		
		return copies*price*percent;
	}

}
