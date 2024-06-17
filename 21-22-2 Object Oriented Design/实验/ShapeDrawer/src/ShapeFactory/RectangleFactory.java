package ShapeFactory;

import java.awt.Point;

import Shapes.AbstractShape;
import Shapes.RectangleShape;

public class RectangleFactory extends AbstractFactory {
	
	@Override
	public AbstractShape getShape(Point s, Point e) {
		AbstractShape shape = new RectangleShape(s, e);
		return shape;
	}
}
