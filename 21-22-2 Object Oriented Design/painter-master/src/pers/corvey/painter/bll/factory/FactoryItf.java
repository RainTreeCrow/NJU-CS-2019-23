package pers.corvey.painter.bll.factory;
import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 工厂接口
 */
public interface FactoryItf {
	/**
	 * 工厂方法
	 * @return MyShapeItf
	 */
	public MyShapeItf createProduct();
}
