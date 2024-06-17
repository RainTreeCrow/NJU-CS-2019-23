package pers.corvey.painter.model.shape;

import java.awt.Shape;
import java.awt.geom.GeneralPath;

/**
 * 菱形（继承图形抽象类）
 */
public class Rhombus extends MyShapeAbs {

	public Rhombus() {
		super();
	}
	
	@Override
	public Shape createShape() {
		float wMid = Math.min(start.x, end.x) + Math.abs(end.x - start.x)/2;
		float hMid = Math.min(start.y, end.y) + Math.abs(end.y - start.y)/2;
		GeneralPath path = new GeneralPath(GeneralPath.WIND_NON_ZERO);
		path.moveTo(wMid, start.y);
		path.lineTo(end.x, hMid);
		path.lineTo(wMid, end.y);
		path.lineTo(start.x, hMid);
		path.lineTo(wMid, start.y);
		path.closePath();
		return path;
	}

}
