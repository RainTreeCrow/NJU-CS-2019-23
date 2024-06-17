package rl.huojing.dp.doubledispatch.sample.revision;

public class WhiteHorse extends Horse {
    public void ridedBy(Mozi m){
    	   m.rideW(this);
    }

	@Override
	public String getName() {
		return "WhiteHorse";
	}
}
