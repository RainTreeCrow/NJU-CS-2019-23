package pers.corvey.painter.bll.strategy;

import java.awt.Shape;
import java.awt.geom.Point2D;

/**
 * 判断器之系统实现（实现判断器接口）<br>
 * 具体策略类，除了线段之外其余图形都默认都使用该策略
 */
public class JudgerSysImpl implements JudgerItf {

	@Override
	public boolean judge(Shape shape, Point2D point) {
		return shape.contains(point);
	}
}
