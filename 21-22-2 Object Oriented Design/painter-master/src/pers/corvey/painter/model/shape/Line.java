package pers.corvey.painter.model.shape;
import java.awt.Shape;
import java.awt.geom.Line2D;

import pers.corvey.painter.bll.strategy.JudgerMyImpl;

/**
 * 线段（继承图形抽象类）
 */
public class Line extends MyShapeAbs {
	
	public Line() {
		super(new JudgerMyImpl());
	}
	
	@Override
	public Shape createShape() {
		return new Line2D.Float(start.x, start.y, end.x, end.y);
	}
}

