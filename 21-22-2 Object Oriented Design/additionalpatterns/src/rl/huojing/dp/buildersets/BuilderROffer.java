package rl.huojing.dp.buildersets;

import java.util.ArrayList;

public class BuilderROffer implements Builder{
	private ArrayList<OfferPart> parts = new ArrayList<OfferPart>();
	public void buildPart() {
		parts.clear();
		parts.add(new RBurger());
		parts.add(new RChip());
	}
	public OfferSet getResult() {
		OfferSet oneoffer = new OfferSet();
		oneoffer.SetParts(parts);
		return oneoffer;
	}
}
