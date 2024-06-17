package pers.corvey.painter.bll.factory;

import pers.corvey.painter.model.shape.MyShapeItf;
import pers.corvey.painter.model.shape.Rhombus;

/**
 * 菱形工厂（实现工厂接口）
 */
public class RhombusFactory implements FactoryItf {

	@Override
	public MyShapeItf createProduct() {
		return new Rhombus();
	}

}
