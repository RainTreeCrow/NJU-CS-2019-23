package pers.corvey.painter.bll.strategy;

import java.awt.Shape;
import java.awt.geom.Point2D;

/**
 * 判断器接口（抽象策略类）
 */
public interface JudgerItf {
	/**
	 * 判断鼠标点击位置是否位于图形范围内
	 * @param shape - 图形
	 * @param point - 鼠标点击位置
	 * @return 鼠标点击位置是否位于图形范围内
	 */
	public boolean judge(Shape shape, Point2D point);
}
