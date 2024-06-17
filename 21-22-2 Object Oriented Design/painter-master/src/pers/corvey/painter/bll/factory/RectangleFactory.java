package pers.corvey.painter.bll.factory;

import pers.corvey.painter.model.shape.MyShapeItf;
import pers.corvey.painter.model.shape.Rectangle;

/**
 * 矩形工厂（实现工厂接口）
 */
public class RectangleFactory implements FactoryItf{

	@Override
	public MyShapeItf createProduct() {
		return new Rectangle();
	}
}
