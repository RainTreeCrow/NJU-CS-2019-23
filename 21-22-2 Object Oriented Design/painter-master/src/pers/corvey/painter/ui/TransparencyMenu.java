package pers.corvey.painter.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JMenuItem;
import javax.swing.JPanel;

import pers.corvey.painter.bll.bridge.AppearanceItf;
import pers.corvey.painter.bll.pattern.PatternAbs;

/**
 * 透明度菜单（继承我的菜单）
 */
public class TransparencyMenu extends MyJMenu {

	private final static float default_transparency = 0.6f;
	private JPanel board;
	private JMenuItem mi_transparency10 = new JMenuItem("透明度：100%");
	private JMenuItem mi_transparency8 = new JMenuItem("透明度：80%");
	private JMenuItem mi_transparency6 = new JMenuItem("透明度：60%");
	private JMenuItem mi_transparency4 = new JMenuItem("透明度：40%");
	private JMenuItem mi_transparency2 = new JMenuItem("透明度：20%");
	private HashMap<Float, JMenuItem> map = new HashMap<Float, JMenuItem>();
	
	public TransparencyMenu(JPanel board) {
		super("透明度");
		this.board = board;
		applySetting(mi_transparency6, default_transparency);
		
		mi_transparency10.addActionListener(createActionListener(mi_transparency10, 1));
		add(mi_transparency10);

		mi_transparency8.addActionListener(createActionListener(mi_transparency8, 0.8f));
		add(mi_transparency8);
		
		mi_transparency6.addActionListener(createActionListener(mi_transparency6, 0.6f));
		add(mi_transparency6);
		
		mi_transparency4.addActionListener(createActionListener(mi_transparency4, 0.4f));
		add(mi_transparency4);
		
		mi_transparency2.addActionListener(createActionListener(mi_transparency2, 0.2f));
		add(mi_transparency2);
	}
	
	/**
	 * 生成对应的监听器
	 */
	public ActionListener createActionListener(JMenuItem item, float transparency) {
		map.put(transparency, item);
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, transparency);
			}
		};
	}
	
	public HashMap<Float, JMenuItem> getMap() {
		return map;
	}
	
	/**
	 * 应用设置
	 */
	public void applySetting(JMenuItem item, float transparency) {
		PatternAbs pattern = ((Board)board).getNowPattern();
		AppearanceItf appearance = pattern.getApperance();
		if(appearance != null) {
			appearance.setTransparency(transparency);
			pattern.applyAppearance();
			setActiveItem(item);
		}
	}
}
