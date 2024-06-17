package ShapeDecorator;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;

import Shapes.AbstractShape;

public class AbstractDecorator extends AbstractShape {
	
	protected AbstractShape shape;
	
	public AbstractDecorator(AbstractShape shape) {
		this.shape = shape;
	}

	@Override
	public Point getStart() {
		return shape.getStart();
	}
	
	@Override
	public Point getEnd() {
		return shape.getEnd();
	}
	
	@Override
	public void process(Point e) {
		shape.process(e);;
	}
	
	@Override
	public void move(Point s, Point e) {
		int x = e.x - s.x;
		int y = e.y - s.y;
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		shape.move(s, e);
	}
	
	@Override
	public void move(int x, int y) {
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		shape.move(x, y);
	}
	
	@Override
	public Shape shape() {
		return shape.shape();
	}
	
	@Override
	public void drawSelf(Graphics2D g2) {
		shape.drawSelf(g2);
	}
	
	@Override
	public boolean selected(Point p) {
		return shape.selected(p);
	}
	
	@Override
	public Shape createShape() {
		return shape.createShape();
	}
}
