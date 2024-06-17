package rl.huojing.dp.buildersets;


import java.util.ArrayList;

public class BuilderSOffer implements Builder{
	private ArrayList<OfferPart> parts = new ArrayList<OfferPart>();
	public void buildPart() {
		parts.clear();
		parts.add(new SBurger());
		parts.add(new SChip());
	}
	public OfferSet getResult() {
		OfferSet oneoffer = new OfferSet();
		oneoffer.SetParts(parts);
		return oneoffer;
	}
}
