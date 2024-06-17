package pers.corvey.painter.bll.decoration;

import java.awt.Point;
import java.awt.geom.Point2D;

import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 赋予图形可变性的装饰器
 */
public class ChangeableDecoration extends DecorationAbs implements ChangeableItf {

	/**
	 * 每次放大或缩小时的变化程度
	 */
	private final double changeDegree = 10;
	
	/**
	 * 每次放大或缩小时横坐标的变化值
	 */
	private int deltaX;
	
	/**
	 * 每次放大或缩小时纵坐标的变化值
	 */
	private int deltaY;
	
	public ChangeableDecoration() {}
	
	public ChangeableDecoration(MyShapeItf myShape) {
		setMyShape(myShape);
	}
	
	@Override
	public void setMyShape(MyShapeItf myShape) {
		super.setMyShape(myShape);
		if(myShape != null)
			computeDelta();
	}
	
	@Override
	public void zoomIn() {
		Point start = myShape.getStartPoint();
		Point end = myShape.getEndPoint();
		start.move(start.x + deltaX, start.y + deltaY);
		end.move(end.x - deltaX, end.y - deltaY);
		myShape.setShape(myShape.createShape());
	}

	@Override
	public void zoomOut() {
		Point start = myShape.getStartPoint();
		Point end = myShape.getEndPoint();
		double d = new Point2D.Double(end.x, end.y).distance(start.x, start.y);
		if(d < 50)
			return ;
		start.move(start.x - deltaX, start.y - deltaY);
		end.move(end.x + deltaX, end.y + deltaY);
		myShape.setShape(myShape.createShape());
	}

	@Override
	public void move(Point from, Point to) {
		int dx = to.x - from.x;
		int dy = to.y - from.y;
		Point start = myShape.getStartPoint();
		Point end = myShape.getEndPoint();
		start.move(start.x + dx, start.y + dy);
		end.move(end.x + dx, end.y + dy);
		myShape.setShape(myShape.createShape());
	}
	
	/**
	 * 计算图形放大缩小时横纵坐标的变化值
	 */
	public void computeDelta() {
		double x1 = myShape.getStartPoint().x, y1 = myShape.getStartPoint().y;
		double x2 = myShape.getEndPoint().x, y2 = myShape.getEndPoint().y;
		double d = new Point2D.Double(x2, y2).distance(x1, y1);
		double cos = (x2 - x1) / d;
		double tan = (y2 - y1) / (x2 - x1);
		deltaX = (int)(Math.abs(changeDegree * cos) + 0.5);
		deltaY = (int)(Math.abs(deltaX * tan) + 0.5);
		if(x1 < x2 && y1 > y2) {	//右上方
			deltaX = 0 - deltaX;
			
		} else if (x1 > x2 && y1 < y2) {	//左下方
			deltaY = 0 - deltaY;
			
		} else if (x1 < x2 && y1 < y2) {	//右下方
			deltaX = 0 - deltaX;
			deltaY = 0 - deltaY;
		}
	}
}
