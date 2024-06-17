package rl.huojing.dp.builder;

public class Part {
	private String ID;
	public Part(String name){
		ID = name;
		System.out.println("This is Part "+name);
	}
	public String getID(){
		return ID;
	}
}
