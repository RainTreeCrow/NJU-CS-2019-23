package rl.huojing.dp.builder;

public class Director {
	private Builder builder = null;
	public Director(Builder b){
		builder = b;
	}
	public void construct(){
		builder.buildPartA();
		builder.buildPartB();
		builder.buildPartC();
	}


}
