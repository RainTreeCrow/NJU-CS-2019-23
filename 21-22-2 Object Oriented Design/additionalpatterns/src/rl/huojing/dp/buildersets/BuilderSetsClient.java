package rl.huojing.dp.buildersets;



public class BuilderSetsClient {
	
	public static void main(String[] args) {
		Builder builder = new BuilderROffer();
		Director director_offer = new Director(builder);
		director_offer.construct();
		OfferSet offer = builder.getResult();
		offer.PrintInfo();
		
//		Builder builder = new BuilderROffer();
//		Director director_offer = new Director(builder);
//		director_offer.construct();
//		OfferSet offer = builder.getResult();
//		offer.PrintInfo();
	}
}
