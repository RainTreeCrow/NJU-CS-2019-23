package MenuBar;

import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

public class AbstractMenu extends JMenu {
	
	protected final static ImageIcon icon = new ImageIcon("./image/yes.png");
	protected JMenuItem activeItem;
	
	public AbstractMenu(String name) {
		super(name);
	}

	public JMenuItem getActiveItem() {
		return activeItem;
	}
	
	public void setActiveItem(JMenuItem activeItem) {
		if(getActiveItem() != null)
			getActiveItem().setIcon(null);
		activeItem.setIcon(icon);
		this.activeItem = activeItem;
	}
}