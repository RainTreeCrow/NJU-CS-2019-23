package rl.huojing.dp.doubledispatch.sample;

public class Tester {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Horse wh = new WhiteHorse();
		Horse bh = new BlackHorse();
		Mozi mozi = new Mozi();
		System.out.println(mozi.getName());
		mozi.ride(wh);
		mozi.ride(bh);
		Mozi geli = new Geli();
		System.out.println(geli.getName());
		geli.ride(bh);	
		
		///** usage of "instanceof"
		 
		if (bh instanceof BlackHorse){
			BlackHorse blackhorse = (BlackHorse)bh;
			geli.ride(blackhorse);
		}
		//*/ 
		
		/** another example
		System.out.println("another interesting example...");
		String s1 = "ab";
        Object o = s1 +"c";
        String s = "abc";
        boolean b = o.equals(s);        
        System.out.println(b);
        */        
	}

}
