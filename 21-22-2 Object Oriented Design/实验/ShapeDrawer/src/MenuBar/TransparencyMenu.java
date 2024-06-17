package MenuBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JMenuItem;

import ShapeImplementor.AbstractImplementor;
import UserInterface.AbstractInterface;
import UserInterface.WhiteBoard;

public class TransparencyMenu extends AbstractMenu {
	
	private WhiteBoard board;
	private final static float default_transparency = 0.6f;
	private HashMap<Float, JMenuItem> map = new HashMap<Float, JMenuItem>();
	
	private JMenuItem mi_transparency10 = new JMenuItem("透明度：0%");
	private JMenuItem mi_transparency8 = new JMenuItem("透明度：20%");
	private JMenuItem mi_transparency6 = new JMenuItem("透明度：40%");
	private JMenuItem mi_transparency4 = new JMenuItem("透明度：60%");
	private JMenuItem mi_transparency2 = new JMenuItem("透明度：80%");
	
	public TransparencyMenu(WhiteBoard board) {
		super("透明度");
		this.board = board;
		applySetting(mi_transparency6, default_transparency);
		
		mi_transparency10.addActionListener(
				createActionListener(mi_transparency10, 1));
		add(mi_transparency10);

		mi_transparency8.addActionListener(
				createActionListener(mi_transparency8, 0.8f));
		add(mi_transparency8);
		
		mi_transparency6.addActionListener(
				createActionListener(mi_transparency6, 0.6f));
		add(mi_transparency6);
		
		mi_transparency4.addActionListener(
				createActionListener(mi_transparency4, 0.4f));
		add(mi_transparency4);
		
		mi_transparency2.addActionListener(
				createActionListener(mi_transparency2, 0.2f));
		add(mi_transparency2);
	}
	
	public ActionListener createActionListener(JMenuItem item, float transparency) {
		map.put(transparency, item);
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, transparency);
			}
		};
	}
	
	public void applySetting(JMenuItem item, float transparency) {
		AbstractInterface currentMode = board.currentMode();
		AbstractImplementor appearance = board.getImplementor();
		if (appearance != null) {
			appearance.setTransparency(transparency);
			currentMode.implement();
			setActiveItem(item);
		}
	}
	
	public HashMap<Float, JMenuItem> getMap() {
		return map;
	}
}
