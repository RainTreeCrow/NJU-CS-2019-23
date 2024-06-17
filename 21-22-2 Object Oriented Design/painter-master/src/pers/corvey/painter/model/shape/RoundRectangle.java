package pers.corvey.painter.model.shape;

import java.awt.Shape;
import java.awt.geom.RoundRectangle2D;

/**
 * 圆角矩形（继承图形抽象类）
 */
public class RoundRectangle extends MyShapeAbs {

	public RoundRectangle() {
		super();
	}
	
	public Shape createShape() {
		return new RoundRectangle2D.Float(Math.min(start.x, end.x), Math.min(start.y, end.y), 
									 	  Math.abs(start.x - end.x), Math.abs(start.y - end.y),
									 	  45, 45);
	}
}
