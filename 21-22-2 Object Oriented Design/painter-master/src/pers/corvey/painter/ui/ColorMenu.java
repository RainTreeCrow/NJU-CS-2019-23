package pers.corvey.painter.ui;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

import pers.corvey.painter.bll.bridge.AppearanceItf;
import pers.corvey.painter.bll.pattern.PatternAbs;

/**
 * 颜色菜单（继承我的菜单）
 */
public class ColorMenu extends MyJMenu {
	
	private JPanel board;
	private final Color default_color = Color.black;
	private JMenuItem mi_red = new JMenuItem(" 红 ");
	private JMenuItem mi_yellow = new JMenuItem(" 黄 ");
	private JMenuItem mi_blue = new JMenuItem(" 蓝 ");
	private JMenuItem mi_green = new JMenuItem(" 绿 ");
	private JMenuItem mi_cyan = new JMenuItem(" 青 ");
	private JMenuItem mi_orange = new JMenuItem(" 橙 ");
	private JMenuItem mi_black = new JMenuItem(" 黑 ");
	private HashMap<Color, JMenuItem> map = new HashMap<Color, JMenuItem>();
	
	public ColorMenu(JPanel board) {
		super("颜色");
		this.board = board;
		applySetting(mi_black, default_color);
		
		mi_red.setBackground(Color.red);
		mi_red.addActionListener(createActionListener(mi_red, Color.red));
		add(mi_red);
		
		mi_yellow.setBackground(Color.yellow);
		mi_yellow.addActionListener(createActionListener(mi_yellow, Color.yellow));
		add(mi_yellow);
		
		mi_blue.setBackground(Color.blue);
		mi_blue.addActionListener(createActionListener(mi_blue, Color.blue));
		add(mi_blue);
		
		mi_green.setBackground(Color.green);
		mi_green.addActionListener(createActionListener(mi_green, Color.green));
		add(mi_green);
		
		mi_cyan.setBackground(Color.cyan);
		mi_cyan.addActionListener(createActionListener(mi_cyan, Color.cyan));
		add(mi_cyan);
		
		mi_orange.setBackground(Color.orange);
		mi_orange.addActionListener(createActionListener(mi_orange, Color.orange));
		add(mi_orange);
		
		mi_black.setBackground(Color.black);
		mi_black.addActionListener(createActionListener(mi_black, Color.black));
		add(mi_black);
	}
	
	/**
	 * 生成对应的监听器
	 */
	public ActionListener createActionListener(JMenuItem item, Color color) {
		map.put(color, item);
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, color);
			}
		};
	}
	
	/**
	 * 应用设定颜色
	 */
	public void applySetting(JMenuItem item, Color color) {
		PatternAbs pattern = ((Board)board).getNowPattern();
		AppearanceItf appearance = pattern.getApperance();
		if(appearance != null) {
			appearance.setColor(color);
			pattern.applyAppearance();
			setActiveItem(item);
		}
	}
	
	public HashMap<Color, JMenuItem> getMap() {
		return map;
	}
}
