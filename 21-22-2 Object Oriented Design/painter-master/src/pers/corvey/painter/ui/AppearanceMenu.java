package pers.corvey.painter.ui;

import pers.corvey.painter.bll.bridge.AppearanceItf;

public class AppearanceMenu {

	private static ColorMenu colorMenu;
	private static ThicknessMenu thicknessMenu;
	private static TransparencyMenu transparencyMenu;
	
	public static void activeItemByAppearance(AppearanceItf appearance) {
		colorMenu.setActiveItem(colorMenu.getMap().get(appearance.getColor()));
		thicknessMenu.setActiveItem(thicknessMenu.getMap().get(appearance.getWidth()));
		transparencyMenu.setActiveItem(transparencyMenu.getMap().get(appearance.getTransparency()));
	}
	
	public static void setColorMenu(ColorMenu menu) {
		colorMenu = menu;
	}
	
	public static void setThicknessMenu(ThicknessMenu menu) {
		thicknessMenu = menu;
	}
	
	public static void setTransparencyMenu(TransparencyMenu menu) {
		transparencyMenu = menu;
	}
}
