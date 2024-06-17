package rl.huojing.dp.strategy;

public class StrategyClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BookStoreContext cxt = new BookStoreContext();
		cxt.setCopies(100);
		cxt.setPrice(32.50f);
		cxt.setAmount(1.00f);
		cxt.setPercent(0.15f);
		DiscountStrategy strategy0 = new NoDiscountStrategy(cxt.getPrice(),cxt.getCopies());
		cxt.setStrategy(strategy0);
		System.out.println("NoDiscountStrategy: "+cxt.calculateDiscount());
		DiscountStrategy strategy1 = new FlatRateStrategy(cxt.getPrice(),cxt.getCopies(),cxt.getAmount());
		cxt.setStrategy(strategy1);
		System.out.println("FlatRateStrategy: "+cxt.calculateDiscount());
		DiscountStrategy strategy2 = new PercentageStrategy(cxt.getPrice(),cxt.getCopies(),cxt.getPercent());
		cxt.setStrategy(strategy2);
		System.out.println("PercentageStrategy: "+cxt.calculateDiscount());
	}

}
