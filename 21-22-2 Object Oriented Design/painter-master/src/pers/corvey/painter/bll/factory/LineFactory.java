package pers.corvey.painter.bll.factory;

import pers.corvey.painter.model.shape.Line;
import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 线段工厂（实现工厂接口）
 */
public class LineFactory implements FactoryItf{

	@Override
	public MyShapeItf createProduct() {
		return new Line();
	}
}
