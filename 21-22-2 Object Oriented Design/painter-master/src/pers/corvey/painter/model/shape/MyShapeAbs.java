package pers.corvey.painter.model.shape;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;
import java.io.Serializable;

import pers.corvey.painter.bll.bridge.AppearanceItf;
import pers.corvey.painter.bll.strategy.JudgerItf;
import pers.corvey.painter.bll.strategy.JudgerSysImpl;


/**
 * 图形抽象类（实现图形接口）
 */
public abstract class MyShapeAbs implements MyShapeItf, Serializable {

	protected Point start = new Point();
	protected Point end = new Point();
	protected Shape myShape = null;
	protected AppearanceItf appearance;
	protected JudgerItf judger;
	
	public MyShapeAbs(JudgerItf wayToJudge) {
		this.judger = wayToJudge;
	}
	
	public MyShapeAbs() {
		this(new JudgerSysImpl());
	}
	
	public Shape getShape() {
		return myShape == null ? createShape() : myShape;
	}
	
	public void setShape(Shape shape) {
		this.myShape = shape;
	}
	
	public Point getStartPoint() {
		return start;
	}
	
	public void setStartPoint(Point p) {
		start.setLocation(p);
	}

	public Point getEndPoint() {
		return end;
	}
	
	public void setEndPoint(Point p) {
		end.setLocation(p);
	}
	
	public AppearanceItf getAppearance() {
		return appearance;
	}
	
	public void setAppearance(AppearanceItf appearance) {
		this.appearance = appearance;
	}
	
	public void applyAppearance(Graphics2D g2) {
		appearance.applyAppearance(g2);
	}
	
	@Override
	public JudgerItf getJudger() {
		return judger;
	}

	@Override
	public void setJudger(JudgerItf wayToJudge) {
		this.judger = wayToJudge;
	}
}
