package pers.corvey.painter.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JMenuItem;
import javax.swing.JPanel;

import pers.corvey.painter.bll.bridge.AppearanceItf;
import pers.corvey.painter.bll.pattern.PatternAbs;

/**
 * 粗细度菜单（继承我的菜单）
 */
public class ThicknessMenu extends MyJMenu {

	private final static float default_width = 2f;
	private JPanel board;
	private JMenuItem mi_thickness1 = new JMenuItem("粗细度：1");
	private JMenuItem mi_thickness2 = new JMenuItem("粗细度：2");
	private JMenuItem mi_thickness3 = new JMenuItem("粗细度：3");
	private JMenuItem mi_thickness4 = new JMenuItem("粗细度：4");
	private JMenuItem mi_thickness5 = new JMenuItem("粗细度：5");
	private HashMap<Float, JMenuItem> map = new HashMap<Float, JMenuItem>();
	
	public ThicknessMenu(JPanel board) {
		super("粗细度");
		this.board = board;
		applySetting(mi_thickness2, default_width);
		
		mi_thickness1.addActionListener(createActionListener(mi_thickness1, 1));
		add(mi_thickness1);
		
		mi_thickness2.addActionListener(createActionListener(mi_thickness2, 2));
		add(mi_thickness2);
		
		mi_thickness3.addActionListener(createActionListener(mi_thickness3, 3));
		add(mi_thickness3);
		
		mi_thickness4.addActionListener(createActionListener(mi_thickness4, 4));
		add(mi_thickness4);
		
		mi_thickness5.addActionListener(createActionListener(mi_thickness5, 5));
		add(mi_thickness5);
	}
	
	/**
	 * 生成对应的监听器
	 */
	public ActionListener createActionListener(JMenuItem item, float width) {
		map.put(width, item);
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, width);
			}
		};
	}
	
	public HashMap<Float, JMenuItem> getMap() {
		return map;
	}
	
	/**
	 * 应用设置
	 */
	public void applySetting(JMenuItem item, float width) {
		PatternAbs pattern = ((Board)board).getNowPattern();
		AppearanceItf appearance = pattern.getApperance();
		if(appearance != null) {
			appearance.setWidth(width);
			pattern.applyAppearance();
			setActiveItem(item);
		}
	}
}
