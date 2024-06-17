package rl.huojing.dp.doubledispatch.ballkicking;

public class SubWest1 extends West {

	@Override
	public void goWest1(SubEast1 e) {
		System.out.println("SubWest1 + "+e.myName1());
	}

	@Override
	public void goWest2(SubEast2 e) {
		System.out.println("SubWest1 + "+e.myName2());

	}

}
