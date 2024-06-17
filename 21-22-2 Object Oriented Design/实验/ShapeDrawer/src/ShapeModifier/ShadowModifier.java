package ShapeModifier;

import javax.swing.JOptionPane;

import ShapeDecorator.ShadowDecorator;
import Shapes.AbstractShape;

public class ShadowModifier extends AbstractModifier {
	
	@Override
	public AbstractShape Modify(AbstractShape shape) {
		String[] options = {"左上", "左下", "右上", "右下"};
		int x = JOptionPane.showOptionDialog(
				null, "请选择方向", "添加阴影", 0, 0, null, options, options[0]);
		ShadowDecorator newShape = new ShadowDecorator(shape, x);
		return newShape;
	}
}
