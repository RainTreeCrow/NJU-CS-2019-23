package rl.huojing.dp.doubledispatch.sample.revision;

public class Tester {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Horse wh = new WhiteHorse();
		Horse bh = new BlackHorse();
		Mozi mozi = new Mozi();
		System.out.println(mozi.getName());
		wh.ridedBy(mozi);
		bh.ridedBy(mozi);
		Mozi geli = new Geli();
		System.out.println(geli.getName());
		bh.ridedBy(geli);		       
	}

}
