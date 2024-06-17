package Shapes;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;
import java.io.IOException;
import java.util.ArrayList;

import ShapeImplementor.AbstractImplementor;

public class CompositeShape extends AbstractShape {
	
	private ArrayList<AbstractShape> shapeList = new ArrayList<AbstractShape>();
	
	public CompositeShape(ArrayList<AbstractShape> shapes) {
		for (AbstractShape shape : shapes) {
			try {
				shapeList.add(shape.deepClone());
			}
			catch (ClassNotFoundException | IOException e) {
				e.printStackTrace();
			}
		}
		int s_x = 1000000000, s_y = 1000000000;
		int e_x = -1, e_y = -1;
		for (AbstractShape shape : shapes) {
			if (shape.getStart().x < s_x)
				s_x = shape.getStart().x;
			if (shape.getStart().y < s_y)
				s_y = shape.getStart().y;
			if (shape.getEnd().x > e_x)
				e_x = shape.getEnd().x;
			if (shape.getEnd().y > e_y)
				e_y = shape.getEnd().y;
		}
		start.setLocation(s_x, s_y);
		end.setLocation(e_x, e_y);
	}
	
	public ArrayList<AbstractShape> getShapeList() {
		return shapeList;
	}

	@Override
	public Shape createShape() {
		return null;
	}
	
	@Override
	public void move(Point s, Point e) {
		int x = e.x - s.x;
		int y = e.y - s.y;
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		for (AbstractShape shape: shapeList)
			shape.move(s, e);
	}
	
	@Override
	public void move(int x, int y) {
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		for (AbstractShape shape: shapeList)
			shape.move(x, y);
	}
	
	@Override
	public void drawSelf(Graphics2D g2) {
		for (AbstractShape shape: shapeList)
			shape.drawSelf(g2);
	}
	
	@Override
	public boolean selected(Point p) {
		for (AbstractShape shape: shapeList)
			if (shape.selected(p))
				return true;
		return false;
	}
	
	@Override
	public void setAppearance(AbstractImplementor appearance) {
		for (AbstractShape shape: shapeList) {
			shape.appearance.setColor(appearance.getColor());
			shape.appearance.setWidth(appearance.getWidth());
			shape.appearance.setTransparency(appearance.getTransparency());
		}
	}
}
