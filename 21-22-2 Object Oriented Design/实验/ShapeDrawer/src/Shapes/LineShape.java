package Shapes;

import java.awt.Point;
import java.awt.Shape;
import java.awt.geom.Line2D;

public class LineShape extends AbstractShape {
	
	public LineShape(Point s, Point e) {
		super(s, e);
	}

	@Override
	public Shape createShape() {
		return new Line2D.Float(start.x, start.y, end.x, end.y);
	}
	
	@Override
	public boolean selected(Point p) {
		Line2D line = (Line2D)selfShape;
		if(line.getBounds().contains(p))
			return line.ptLineDist(p) < 3;
		else
			return false;
	}
}
