package rl.huojing.dp.monostate;

public class MonostateClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Monostate m1 = new Monostate();
		Monostate m2 = new Monostate();
		for (int x=0; x<10; x++){
			m1.setX(x);
			System.out.println("m1.getX():"+m1.getX());
			System.out.println("m2.getX():"+m2.getX());
		}	
	}
}
