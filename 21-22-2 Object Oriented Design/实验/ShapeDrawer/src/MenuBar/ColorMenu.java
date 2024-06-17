package MenuBar;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JMenuItem;

import ShapeImplementor.AbstractImplementor;
import UserInterface.AbstractInterface;
import UserInterface.WhiteBoard;

public class ColorMenu extends AbstractMenu {
	
	private WhiteBoard board;
	private final Color default_color = Color.black;
	private HashMap<Color, JMenuItem> map = new HashMap<Color, JMenuItem>();
	
	private JMenuItem mi_red = new JMenuItem(" ºì ");
	private JMenuItem mi_yellow = new JMenuItem(" »Æ ");
	private JMenuItem mi_blue = new JMenuItem(" À¶ ");
	private JMenuItem mi_green = new JMenuItem(" ÂÌ ");
	private JMenuItem mi_black = new JMenuItem(" ºÚ ");
	
	public ColorMenu(WhiteBoard board) {
		super("ÑÕÉ«");
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
		
		mi_black.setBackground(Color.black);
		mi_black.addActionListener(createActionListener(mi_black, Color.black));
		add(mi_black);
	}
	
	public ActionListener createActionListener(JMenuItem item, Color color) {
		map.put(color, item);
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, color);
			}
		};
	}
	
	public void applySetting(JMenuItem item, Color color) {
		AbstractInterface currentMode = board.currentMode();
		AbstractImplementor appearance = board.getImplementor();
		if (appearance != null) {
			appearance.setColor(color);
			currentMode.implement();
			setActiveItem(item);
		}
	}
	
	public HashMap<Color, JMenuItem> getMap() {
		return map;
	}
}
