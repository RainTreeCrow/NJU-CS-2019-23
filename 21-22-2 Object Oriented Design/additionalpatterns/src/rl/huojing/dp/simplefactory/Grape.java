package rl.huojing.dp.simplefactory;

public class Grape implements Fruit {
	private boolean seedless;
	
	public void grow() {
		System.out.println("Grape is growing...");

	}

	public void harvest() {
		System.out.println("Grape has been harvested.");

	}

	public void plant() {
		System.out.println("Grape has been planted.");

	}

	public boolean getSeedless(){
		return seedless;
	}
	
	public void setSeedless(boolean seedless){
		this.seedless = seedless;
	}
}
