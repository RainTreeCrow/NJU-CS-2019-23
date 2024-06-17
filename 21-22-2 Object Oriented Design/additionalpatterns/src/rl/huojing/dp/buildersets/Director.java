package rl.huojing.dp.buildersets;


public class Director {
	private Builder builder = null;
	public Director(Builder b){
		builder = b;
	}
	public void construct(){
		builder.buildPart();
	}

}
