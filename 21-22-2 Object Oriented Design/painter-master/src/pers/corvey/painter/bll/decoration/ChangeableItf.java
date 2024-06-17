package pers.corvey.painter.bll.decoration;

import java.awt.Point;

/**
 * 可变性的接口
 */
public interface ChangeableItf {
	
	/**
	 * 放大图形
	 */
	public void zoomIn();
	
	/**
	 * 缩小图形
	 */
	public void zoomOut();
	
	/**
	 * 根据鼠标的位移移动图形
	 * @param from - 鼠标起始位置
	 * @param to - 鼠标终止位置
	 */
	public void move(Point from, Point to);
}
