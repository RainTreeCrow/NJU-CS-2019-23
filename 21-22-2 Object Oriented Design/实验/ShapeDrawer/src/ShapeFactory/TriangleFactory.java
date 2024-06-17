package ShapeFactory;

import java.awt.Point;

import Shapes.AbstractShape;
import Shapes.TriangleShape;

public class TriangleFactory extends AbstractFactory {
	
	@Override
	public AbstractShape getShape(Point s, Point e) {
		AbstractShape shape = new TriangleShape(s, e);
		return shape;
	}
}
