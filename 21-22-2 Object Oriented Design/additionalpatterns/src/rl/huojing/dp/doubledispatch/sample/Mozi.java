package rl.huojing.dp.doubledispatch.sample;

public class Mozi {

	public void ride(Horse h){
		System.out.println("Riding a horse");
	}
	
	public void ride(WhiteHorse wh){
		System.out.println("Riding a white horse");
	}
	
	public void ride(BlackHorse bh){
		System.out.println("Riding a black horse");
	}
	
	public String getName(){
		return "Mozi";
	}
}
