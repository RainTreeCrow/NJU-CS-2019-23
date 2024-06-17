package MenuBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenuItem;

import UserInterface.WhiteBoard;

public class EditMenu extends AbstractMenu {
	
	private WhiteBoard board;
	
	private JMenuItem mi_undo = new JMenuItem("撤销");
	private JMenuItem mi_redo = new JMenuItem("重做");
	private JMenuItem mi_clear = new JMenuItem("清空");
	
	public EditMenu(WhiteBoard board) {
		super("编辑");
		this.board = board;
		
		mi_undo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				board.undoMemento();
			}
		});
		add(mi_undo);
		
		mi_redo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				board.redoMemento();
			}
		});
		add(mi_redo);
		
		mi_clear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				board.clean();
				board.saveMemento();
			}
		});
		add(mi_clear);
	}
}
