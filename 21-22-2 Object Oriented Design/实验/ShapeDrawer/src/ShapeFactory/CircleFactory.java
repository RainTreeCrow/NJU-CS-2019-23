package ShapeFactory;

import java.awt.Point;

import Shapes.AbstractShape;
import Shapes.CircleShape;

public class CircleFactory extends AbstractFactory {
	
	@Override
	public AbstractShape getShape(Point s, Point e) {
		AbstractShape shape = new CircleShape(s, e);
		return shape;
	}
}
