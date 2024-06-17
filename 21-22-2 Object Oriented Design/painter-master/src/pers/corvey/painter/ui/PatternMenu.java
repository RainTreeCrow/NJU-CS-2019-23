package pers.corvey.painter.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

/**
 * 模式菜单（继承我的菜单）
 */
public class PatternMenu extends MyJMenu {
	
	private JMenuItem mi_paint = new JMenuItem("画图");
	private JMenuItem mi_choose = new JMenuItem("选择");
	
	public PatternMenu(JPanel board) {
		super("模式");
		
		((Board)board).ActivePainter();
		setActiveItem(mi_paint);
		
		mi_paint.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				((Board)board).ActivePainter();
				AppearanceMenu.activeItemByAppearance(((Board)board).getPainter().getApperance());
				setActiveItem(mi_paint);
			}
		});
		add(mi_paint);
		
		mi_choose.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				((Board)board).ActiveChooser();
				setActiveItem(mi_choose);
			}
		});
		add(mi_choose);
	}
}
