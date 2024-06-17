package UserInterface;

import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;

import Shapes.AbstractShape;

public abstract class AbstractInterface {
	
	protected WhiteBoard board;
	protected boolean on;
	protected MouseAdapter mouseAdapter;
	protected MouseMotionAdapter mouseMotionAdapter;
	
	public AbstractInterface() {
		on = false;
	}
	
	public void switchOn() {
		on = true;
	}
	
	public void switchOff() {
		on = false;
	}
	
	public boolean isOn() {
		return on;
	}
	
	public int select(Point p) {
		int index = -1;
		ArrayList<AbstractShape> shapes = board.getShapeList();
		for(int i = shapes.size() - 1; i >= 0; --i) {
			AbstractShape shape = shapes.get(i);
			if(shape.selected(p)) {
				index = i;
				break;
			}
		}
		return index;
	}
	
	public abstract void implement();
}
