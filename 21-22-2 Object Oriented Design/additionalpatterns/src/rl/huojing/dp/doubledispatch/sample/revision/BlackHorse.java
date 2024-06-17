package rl.huojing.dp.doubledispatch.sample.revision;

public class BlackHorse extends Horse {
	public void ridedBy(Mozi m){
 	   m.rideB(this);
	}

	@Override
	public String getName() {
		return "BlackHorse";
	}
}
