package rl.huojing.dp.doubledispatch.ballkicking;

public class SubEast1 extends East {

	@Override
	public void goEast(West w) {
		w.goWest1(this);
	}
	
	public String myName1(){
		return "SubEast1";
	}

}
