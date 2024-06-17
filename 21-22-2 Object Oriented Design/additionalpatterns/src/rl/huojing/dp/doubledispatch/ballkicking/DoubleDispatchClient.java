package rl.huojing.dp.doubledispatch.ballkicking;

public class DoubleDispatchClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("First Composition:");
		East east = new SubEast1();
		West west = new SubWest1();
		east.goEast(west);
		System.out.println("Second Composition:");
		east = new SubEast1();
		west = new SubWest2();
		east.goEast(west);
		System.out.println("Third Composition:");
		east = new SubEast2();
		west = new SubWest1();
		east.goEast(west);
		System.out.println("Forth Composition:");
		east = new SubEast2();
		west = new SubWest2();
		east.goEast(west);
	}

}
