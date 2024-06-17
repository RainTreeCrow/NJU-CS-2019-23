package Shapes;

import java.awt.Point;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;

public class CircleShape extends AbstractShape{
	
	public CircleShape(Point s, Point e) {
		super(s, e);
	}

	@Override
	public Shape createShape() {
		double s_x = Math.min(start.x, end.x);
		double s_y = Math.min(start.y, end.y);
		double d = Math.max(Math.abs(end.x-start.x), Math.abs(end.y-start.y));
		start.setLocation(s_x, s_y);
		end.setLocation(s_x + d, s_y + d);;
		return new Ellipse2D.Double(s_x, s_y, d, d);
	}
}
