package pers.corvey.painter.model.shape;

import java.awt.Shape;
import java.awt.geom.Ellipse2D;
/**
 * 椭圆（继承图形抽象类）
 */
public class Ellipse extends MyShapeAbs {

	public Ellipse() {
		super();
	}
	
	@Override
	public Shape createShape() {
		return new Ellipse2D.Float(Math.min(start.x, end.x), Math.min(start.y, end.y), 
								   Math.abs(end.x-start.x), Math.abs(end.y-start.y));
	}

}
