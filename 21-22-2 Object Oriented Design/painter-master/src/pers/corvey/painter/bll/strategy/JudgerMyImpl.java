package pers.corvey.painter.bll.strategy;

import java.awt.Shape;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;

/**
 * 判断器之我的实现<br>
 * 具体策略类，仅用于判断鼠标位置是否位于线段附近
 */
public class JudgerMyImpl implements JudgerItf {

	/**
	 * 当鼠标点击位置与线段的距离小于该值时认为鼠标点击位置位于线段上
	 */
	private final int distance = 3;
	@Override
	public boolean judge(Shape shape, Point2D point) {
		Line2D line = (Line2D)shape;
		if(line.getBounds().contains(point))
			return line.ptLineDist(point) < distance;
		else
			return false;
	}
}
