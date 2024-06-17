package Shapes;

import java.awt.Point;
import java.awt.Shape;
import java.awt.geom.GeneralPath;

public class TriangleShape extends AbstractShape {
	
	public TriangleShape(Point s, Point e) {
		super(s, e);
	}

	@Override
	public Shape createShape() {
		GeneralPath triangle = new GeneralPath(GeneralPath.WIND_NON_ZERO);
		triangle.moveTo(start.x, start.y);
	    triangle.lineTo(end.x, end.y);
	    triangle.lineTo(start.x, end.y);
	    triangle.lineTo(start.x, start.y);
	    triangle.closePath();
		return triangle;
	}
}
