package pers.corvey.painter.bll.decoration;

import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 装饰器接口
 */
public interface DecorationItf {
	public MyShapeItf getMyShape();
	public void setMyShape(MyShapeItf myShape);
}
