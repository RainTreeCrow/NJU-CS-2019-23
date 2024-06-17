package ShapeModifier;

import javax.swing.JOptionPane;

import ShapeDecorator.ShadowDecorator;
import Shapes.AbstractShape;

public class ShadowModifier extends AbstractModifier {
	
	@Override
	public AbstractShape Modify(AbstractShape shape) {
		String[] options = {"����", "����", "����", "����"};
		int x = JOptionPane.showOptionDialog(
				null, "��ѡ����", "�����Ӱ", 0, 0, null, options, options[0]);
		ShadowDecorator newShape = new ShadowDecorator(shape, x);
		return newShape;
	}
}
