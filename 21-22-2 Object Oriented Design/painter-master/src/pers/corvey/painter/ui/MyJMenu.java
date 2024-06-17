package pers.corvey.painter.ui;

import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

/**
 * 我的菜单（继承JMenu）
 */
public class MyJMenu extends JMenu {
	/**
	 * 菜单项选中状态图标
	 */
	protected final static ImageIcon icon = new ImageIcon("./image/yes.png");
	
	/**
	 * 当前选中的菜单项
	 */
	protected JMenuItem activeItem;
	
	public MyJMenu(String name) {
		super(name);
	}
	
	/**
	 * 获取当前选中菜单项
	 * @return JMenuItem
	 */
	public JMenuItem getActiveItem() {
		return activeItem;
	}
	
	/**
	 * 设置当前选中菜单项
	 */
	public void setActiveItem(JMenuItem activeItem) {
		if(getActiveItem() != null)
			getActiveItem().setIcon(null);
		activeItem.setIcon(icon);
		this.activeItem = activeItem;
	}
}
