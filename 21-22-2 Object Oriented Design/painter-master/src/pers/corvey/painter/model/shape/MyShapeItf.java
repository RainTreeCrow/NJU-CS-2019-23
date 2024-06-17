package pers.corvey.painter.model.shape;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;

import pers.corvey.painter.bll.bridge.AppearanceItf;
import pers.corvey.painter.bll.strategy.JudgerItf;

/**
 * 图形接口
 */
public interface MyShapeItf {
	
	public Point getStartPoint();
	public void setStartPoint(Point p);
	public Point getEndPoint();
	public void setEndPoint(Point p);
	
	/**
	 * 生成一个形状
	 * @return Shape - 形状类（系统自带的类）
	 */
	public Shape createShape();
	
	/**
	 * 获取形状（系统自带的类）
	 * @return Shape
	 */
	public Shape getShape();
	
	/**
	 * 设定形状（系统自带的类）
	 */
	public void setShape(Shape shape);
	
	/**
	 * 获取外观属性
	 * @return AppearanceItf
	 */
	public AppearanceItf getAppearance();
	
	/**
	 * 设定外观属性
	 */
	public void setAppearance(AppearanceItf appearance);
	
	/**
	 * 应用外观属性
	 */
	public void applyAppearance(Graphics2D g2);
	
	/**
	 * 获取判断器
	 * @return JudgerItf
	 */
	public JudgerItf getJudger();
	
	/**
	 * 设定判断器
	 */
	public void setJudger(JudgerItf wayToJudge);
}
