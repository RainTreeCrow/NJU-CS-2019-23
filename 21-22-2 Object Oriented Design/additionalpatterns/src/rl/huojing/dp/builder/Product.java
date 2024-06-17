package rl.huojing.dp.builder;

public class Product {
	public Product(Part a, Part b, Part c)
	{
		System.out.println("Product includes: "+ a.getID()
				+";"+b.getID()+";"+c.getID());		
	}
}
