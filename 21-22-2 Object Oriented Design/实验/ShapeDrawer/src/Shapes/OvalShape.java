package Shapes;

import java.awt.Point;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;

public class OvalShape extends AbstractShape {
	
	public OvalShape(Point s, Point e) {
		super(s, e);
	}

	@Override
	public Shape createShape() {
		return new Ellipse2D.Double(
			Math.min(start.x, end.x), Math.min(start.y, end.y),
			Math.abs(end.x-start.x), Math.abs(end.y-start.y)
		);
	}
}
