package Shapes;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OptionalDataException;
import java.io.Serializable;

import ShapeImplementor.AbstractImplementor;
import ShapeImplementor.AppearanceImplementor;

public abstract class AbstractShape implements Serializable {
	
	protected Shape selfShape = null;
	protected Point start = new Point();
	protected Point end = new Point();
	protected AbstractImplementor appearance = new AppearanceImplementor();
	
	public abstract Shape createShape();
	
	public AbstractShape() {}
	
	public AbstractShape(Point s, Point e) {
		start.setLocation(s);
		end.setLocation(e);
		selfShape = createShape();
	}
	
	public Point getStart() {
		return start;
	}
	
	public Point getEnd() {
		return end;
	}
	
	public void process(Point e) {
		end.setLocation(e);
		selfShape = createShape();
	}
	
	public void move(Point s, Point e) {
		int x = e.x - s.x;
		int y = e.y - s.y;
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		selfShape = createShape();
	}
	
	public void move(int x, int y) {
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		selfShape = createShape();
	}
	
	public Shape shape() {
		return selfShape;
	}
	
	public void drawSelf(Graphics2D g2) {
		appearance.applyAppearance(g2);
		g2.draw(selfShape);
		g2.fill(selfShape);
	}
	
	public boolean selected(Point p) {
		return selfShape.contains(p);
	}
	
	public AbstractShape deepClone()
			throws IOException, ClassNotFoundException, OptionalDataException {
		ByteArrayOutputStream bao=new ByteArrayOutputStream();
		ObjectOutputStream oos=new ObjectOutputStream(bao);
		oos.writeObject(this);
		ByteArrayInputStream bis=new ByteArrayInputStream(bao.toByteArray());
		ObjectInputStream ois=new ObjectInputStream(bis);
		return (AbstractShape)ois.readObject();
	}
	
	public AbstractImplementor getAppearance() {
		return appearance;
	}
	
	public void setAppearance(AbstractImplementor appearance) {
		this.appearance.setColor(appearance.getColor());
		this.appearance.setWidth(appearance.getWidth());
		this.appearance.setTransparency(appearance.getTransparency());
	}
}
