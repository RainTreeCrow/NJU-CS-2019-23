package rl.huojing.dp.builder;

public class ConcreteBuilder1 implements Builder {
	private Part partA,partB,partC;
	public void buildPartA() {
		partA = new Part("A");
	}
	public void buildPartB() {
		partB = new Part("B");
	}
	public void buildPartC() {
		partC = new Part("C");
	}
	public Product getResult(){
		return new Product(partA,partB,partC);
	}
}
