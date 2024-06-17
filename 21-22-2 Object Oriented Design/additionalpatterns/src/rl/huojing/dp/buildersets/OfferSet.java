package rl.huojing.dp.buildersets;

import java.util.ArrayList;

public class OfferSet {
	private ArrayList<OfferPart> parts;
	public void SetParts(ArrayList<OfferPart> p){
		parts = p;
	}
	public void PrintInfo() {
		System.out.println("This offer contains:");
		for(OfferPart p:parts){
			p.PrintInfo();
		}
	}
}
