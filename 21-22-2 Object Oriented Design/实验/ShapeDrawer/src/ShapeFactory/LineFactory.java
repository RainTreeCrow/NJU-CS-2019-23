package ShapeFactory;

import java.awt.Point;

import Shapes.AbstractShape;
import Shapes.LineShape;

public class LineFactory extends AbstractFactory {
	
	@Override
	public AbstractShape getShape(Point s, Point e) {
		AbstractShape shape = new LineShape(s, e);
		return shape;
	}
}
