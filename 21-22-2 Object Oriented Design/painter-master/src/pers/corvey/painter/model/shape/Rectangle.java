package pers.corvey.painter.model.shape;

import java.awt.Shape;
import java.awt.geom.Rectangle2D;

/**
 * 矩形（继承图形抽象类）
 */
public class Rectangle extends MyShapeAbs{

	public Rectangle() {
		super();
	}
	
	@Override
	public Shape createShape() {
		return new Rectangle2D.Float(Math.min(start.x, end.x), Math.min(start.y, end.y), 
									 Math.abs(start.x - end.x), Math.abs(start.y - end.y));
	}
}
