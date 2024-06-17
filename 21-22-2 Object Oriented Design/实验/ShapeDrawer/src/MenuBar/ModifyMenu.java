package MenuBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenuItem;

import ShapeModifier.AbstractModifier;
import ShapeModifier.ShadowModifier;
import ShapeModifier.TextModifier;
import UserInterface.WhiteBoard;

public class ModifyMenu extends AbstractMenu {
	
	private WhiteBoard board;
	
	private JMenuItem mi_add_text = new JMenuItem("Œƒ◊÷√Ë ˆ");
	private JMenuItem mi_add_shadow = new JMenuItem("“ı”∞");
	
	public ModifyMenu(WhiteBoard board) {
		super("ÃÌº”");
		this.board = board;
		
		mi_add_text.addActionListener(
				createActionListener(mi_add_text, new TextModifier()));
		add(mi_add_text);
		
		mi_add_shadow.addActionListener(
				createActionListener(mi_add_shadow, new ShadowModifier()));
		add(mi_add_shadow);
	}
	
	public ActionListener createActionListener(JMenuItem item, AbstractModifier modifier) {
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				selectModifier(item, modifier);
			}
		};
	}
	
	public void selectModifier(JMenuItem item, AbstractModifier modifier) {
		board.setSelectModifier(modifier);
		setActiveItem(item);
	}
}
