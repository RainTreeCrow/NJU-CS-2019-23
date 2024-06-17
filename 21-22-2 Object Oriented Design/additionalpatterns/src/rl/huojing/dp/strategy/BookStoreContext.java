package rl.huojing.dp.strategy;

public class BookStoreContext {
	private float price;
	private int copies;
	private float percent;
	private float amount;
	private DiscountStrategy strategy;
	
	public float getPrice() {
		return price;
	}
	public void setPrice(float price) {
		this.price = price;
	}
	public int getCopies() {
		return copies;
	}
	public void setCopies(int copies) {
		this.copies = copies;
	}
	public float getPercent() {
		return percent;
	}
	public void setPercent(float percent) {
		this.percent = percent;
	}
	public float getAmount() {
		return amount;
	}
	public void setAmount(float amount) {
		this.amount = amount;
	}
	
	public void setStrategy(DiscountStrategy strategy){
		this.strategy = strategy;
	}
	
	public float calculateDiscount(){
		return strategy.calculateDiscount();
	}
	
	
}
