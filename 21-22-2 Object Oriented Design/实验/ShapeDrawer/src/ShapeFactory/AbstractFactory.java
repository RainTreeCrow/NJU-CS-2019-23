package ShapeFactory;

import java.awt.Point;

import Shapes.AbstractShape;

public abstract class AbstractFactory {
	public abstract AbstractShape getShape(Point s, Point e);
}
