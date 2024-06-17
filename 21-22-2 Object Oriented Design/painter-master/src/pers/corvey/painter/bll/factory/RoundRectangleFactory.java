package pers.corvey.painter.bll.factory;
import pers.corvey.painter.model.shape.MyShapeItf;
import pers.corvey.painter.model.shape.RoundRectangle;

/**
 * 圆角矩形工厂（实现工厂接口）
 */
public class RoundRectangleFactory implements FactoryItf {

	@Override
	public MyShapeItf createProduct() {
		return new RoundRectangle();
	}
}
