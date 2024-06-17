package ShapeFactory;

import java.awt.Point;

import Shapes.AbstractShape;
import Shapes.OvalShape;

public class OvalFactory extends AbstractFactory {
	
	@Override
	public AbstractShape getShape(Point s, Point e) {
		AbstractShape shape = new OvalShape(s, e);
		return shape;
	}
}
