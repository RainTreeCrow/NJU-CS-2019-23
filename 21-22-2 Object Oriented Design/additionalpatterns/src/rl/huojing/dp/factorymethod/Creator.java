package rl.huojing.dp.factorymethod;

public abstract class Creator {
	public abstract Product factoryMethod();
	private Product lnkProduct;
	public void operateProduct(){
		lnkProduct = factoryMethod();
		lnkProduct.operation();
	}
}
