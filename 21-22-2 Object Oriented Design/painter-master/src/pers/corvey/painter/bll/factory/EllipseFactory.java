package pers.corvey.painter.bll.factory;

import pers.corvey.painter.model.shape.Ellipse;
import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 椭圆工厂（实现工厂接口）
 */
public class EllipseFactory implements FactoryItf {

	@Override
	public MyShapeItf createProduct() {
		return new Ellipse();
	}
	
}
