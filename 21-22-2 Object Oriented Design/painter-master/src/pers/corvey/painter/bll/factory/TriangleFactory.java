package pers.corvey.painter.bll.factory;

import pers.corvey.painter.model.shape.MyShapeItf;
import pers.corvey.painter.model.shape.Triangle;

/**
 * 三角形工厂（实现工厂接口）
 */
public class TriangleFactory implements FactoryItf {

	@Override
	public MyShapeItf createProduct() {
		return new Triangle();
	}
	
}
