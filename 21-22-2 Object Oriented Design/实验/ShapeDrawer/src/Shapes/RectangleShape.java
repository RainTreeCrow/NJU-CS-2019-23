package Shapes;

import java.awt.Point;
import java.awt.Shape;
import java.awt.geom.Rectangle2D;

public class RectangleShape extends AbstractShape {
	
	public RectangleShape(Point s, Point e) {
		super(s, e);
	}

	@Override
	public Shape createShape() {
		return new Rectangle2D.Double(
			Math.min(start.x, end.x), Math.min(start.y, end.y), 					 
			Math.abs(start.x - end.x), Math.abs(start.y - end.y)
		);
	}
}
