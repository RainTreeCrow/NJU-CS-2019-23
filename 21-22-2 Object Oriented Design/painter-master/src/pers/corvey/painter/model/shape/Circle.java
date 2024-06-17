package pers.corvey.painter.model.shape;

import java.awt.Shape;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;

/**
 * 圆形（继承图形抽象类）
 */
public class Circle extends MyShapeAbs {

	public Circle() {
		super();
	}
	
	@Override
	public Shape createShape() {
		Point2D o = new Point2D.Double(start.x, start.y);
		double r = o.distance(end);
		return new Ellipse2D.Double(o.getX() - r, o.getY() - r, 2 * r, 2 * r);
	}
}
