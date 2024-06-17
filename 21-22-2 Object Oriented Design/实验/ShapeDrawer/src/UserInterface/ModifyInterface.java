package UserInterface;

import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import ShapeModifier.AbstractModifier;
import Shapes.AbstractShape;

public class ModifyInterface extends AbstractInterface {
	
	protected AbstractModifier modifier;
	protected boolean pressing;
	
	public ModifyInterface(WhiteBoard board) {
		super();
		this.board = board;
		pressing = false;
		
		mouseAdapter = new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if(on) {
					pressing = true;
				}
			}
			@Override
			public void mouseReleased(MouseEvent e) {
				if(on && pressing) {
					Point p = new Point(e.getX(), e.getY());
					int index = select(p);
					if (index != -1) {
						AbstractShape cur = board.getShape(index);
						board.changeShape(index, Modify(cur));
						board.repaint();
						board.saveMemento();
					}
					index = -1;
					pressing = false;
					board.setDefaultMode();
				}
			}
		};
		board.addMouseListener(mouseAdapter);
	}
	
	public void setModifier(AbstractModifier modifier) {
		this.modifier = modifier;
	}
	
	public AbstractShape Modify(AbstractShape shape) {
		return modifier.Modify(shape);
	}
	
	@Override
	public void implement() { }
}
