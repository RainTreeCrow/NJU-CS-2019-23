package pers.corvey.painter.bll.factory;

import pers.corvey.painter.model.shape.Circle;
import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 圆形工厂（实现工厂接口）
 */
public class CircleFactory implements FactoryItf {

	@Override
	public MyShapeItf createProduct() {
		return new Circle();
	}
	
}
