package pers.corvey.painter.model.shape;

import java.awt.Shape;
import java.awt.geom.GeneralPath;

/**
 * 三角形（继承图形抽象类）
 */
public class Triangle extends MyShapeAbs {

	public Triangle() {
		super();
	}
	
	@Override
	public Shape createShape() {
		GeneralPath path = new GeneralPath(GeneralPath.WIND_NON_ZERO);
		path.moveTo(start.x, start.y);
	    path.lineTo(end.x, end.y);
	    path.lineTo(start.x, end.y);
	    path.lineTo(start.x, start.y);
	    path.closePath();
		return path;
	}
}
