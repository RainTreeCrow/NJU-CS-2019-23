package UserInterface;

import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

import ShapeFactory.AbstractFactory;
import Shapes.AbstractShape;

public class DrawInterface extends AbstractInterface {
	
	protected AbstractFactory factory;
	protected AbstractShape shape;
	protected boolean pressing;
	Point start;
	Point end;
	
	public DrawInterface(WhiteBoard board) {
		super();
		this.board = board;
		pressing = false;
		
		mouseAdapter = new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if(on) {
					start = new Point(e.getX(), e.getY());
					end = new Point(start);
					shape = factory.getShape(start, end);
					implement();
					pressing = true;
				}
			}
			@Override
			public void mouseReleased(MouseEvent e) {
				if(on && pressing) {
					board.addShape(shape);
					pressing = false;
					board.repaint();
					shape = null;
					start = end = null;
					board.setDefaultMode();
					board.saveMemento();
				}
			}
		};
		board.addMouseListener(mouseAdapter);
		
		mouseMotionAdapter = new MouseMotionAdapter() {
			@Override
			public void mouseDragged(MouseEvent e) {
				if(on && pressing) {
					end.setLocation(e.getX(), e.getY());
					shape.process(end);
					board.repaint();
				}
			}
		};
		board.addMouseMotionListener(mouseMotionAdapter);
	}
	
	public void setFactory(AbstractFactory factory) {
		this.factory = factory;
	}
	
	public AbstractShape currentShape() {
		return shape;
	}
	
	@Override
	public void implement() {
		if (shape != null) {
			shape.setAppearance(board.getImplementor());
		}
	}
}
