package rl.huojing.dp.doubledispatch.sample.revision;

public class Mozi {
	/*
	public void ride(Horse h){
 	   System.out.println("Ride a "+h.getName());
	}
	*/
    public void rideW(WhiteHorse wh){
    	   System.out.println("Ride a "+wh.getName());
    }
    
    public void rideB(BlackHorse bh){
 	   System.out.println("Ride a "+bh.getName());    	
    }
    
    public String getName(){
    		return "Mozi";
    }
}
