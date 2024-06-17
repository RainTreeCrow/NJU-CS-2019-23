package rl.huojing.dp.doubledispatch.ballkicking;

public class SubEast2 extends East {

	@Override
	public void goEast(West w) {
		w.goWest2(this);
	}
	
	public String myName2(){
		return "SubEast2";
	}

}
