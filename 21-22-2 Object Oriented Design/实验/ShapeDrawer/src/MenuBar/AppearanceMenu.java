package MenuBar;

import ShapeImplementor.AppearanceImplementor;

public class AppearanceMenu extends AbstractMenu {

	public AppearanceMenu(String name) {
		super(name);
	}

	private static ColorMenu colorMenu;
	private static WidthMenu widthMenu;
	private static TransparencyMenu transparencyMenu;
	
	public static void activeItemByAppearance(AppearanceImplementor appearance) {
		colorMenu.setActiveItem(colorMenu.getMap().get(appearance.getColor()));
		widthMenu.setActiveItem(widthMenu.getMap().get(appearance.getWidth()));
		transparencyMenu.setActiveItem(
				transparencyMenu.getMap().get(appearance.getTransparency()));
	}
	
	public static void setColorMenu(ColorMenu menu) {
		colorMenu = menu;
	}
	
	public static void setWidthMenu(WidthMenu menu) {
		widthMenu = menu;
	}
	
	public static void setTransparencyMenu(TransparencyMenu menu) {
		transparencyMenu = menu;
	}
}
