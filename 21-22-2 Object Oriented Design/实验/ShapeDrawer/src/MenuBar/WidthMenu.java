package MenuBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JMenuItem;

import ShapeImplementor.AbstractImplementor;
import UserInterface.AbstractInterface;
import UserInterface.WhiteBoard;

public class WidthMenu extends AbstractMenu {
	
	private WhiteBoard board;
	private final static float default_width = 2f;
	private HashMap<Float, JMenuItem> map = new HashMap<Float, JMenuItem>();
	
	private JMenuItem mi_width1 = new JMenuItem("¥÷œ∏∂»£∫1");
	private JMenuItem mi_width2 = new JMenuItem("¥÷œ∏∂»£∫2");
	private JMenuItem mi_width3 = new JMenuItem("¥÷œ∏∂»£∫3");
	private JMenuItem mi_width4 = new JMenuItem("¥÷œ∏∂»£∫4");
	private JMenuItem mi_width5 = new JMenuItem("¥÷œ∏∂»£∫5");
	
	public WidthMenu(WhiteBoard board) {
		super("¥÷œ∏∂»");
		this.board = board;
		applySetting(mi_width2, default_width);
		
		mi_width1.addActionListener(createActionListener(mi_width1, 1));
		add(mi_width1);
		
		mi_width2.addActionListener(createActionListener(mi_width2, 2));
		add(mi_width2);
		
		mi_width3.addActionListener(createActionListener(mi_width3, 3));
		add(mi_width3);
		
		mi_width4.addActionListener(createActionListener(mi_width4, 4));
		add(mi_width4);
		
		mi_width5.addActionListener(createActionListener(mi_width5, 5));
		add(mi_width5);
	}
	
	public ActionListener createActionListener(JMenuItem item, float width) {
		map.put(width, item);
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, width);
			}
		};
	}
	
	public void applySetting(JMenuItem item, float width) {
		AbstractInterface currentMode = board.currentMode();
		AbstractImplementor appearance = board.getImplementor();
		if (appearance != null) {
			appearance.setWidth(width);
			currentMode.implement();
			setActiveItem(item);
		}
	}
	
	public HashMap<Float, JMenuItem> getMap() {
		return map;
	}
}
