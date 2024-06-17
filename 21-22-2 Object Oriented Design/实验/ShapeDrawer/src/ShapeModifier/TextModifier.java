package ShapeModifier;

import javax.swing.JOptionPane;

import ShapeDecorator.TextDecorator;
import Shapes.AbstractShape;

public class TextModifier extends AbstractModifier {
	
	@Override
	public AbstractShape Modify(AbstractShape shape) {
		if (shape.getClass().equals(TextDecorator.class)) {
			String text = (String) JOptionPane.showInputDialog(
					null, "请输入文字", "文字描述", 0, null, null,
					((TextDecorator)shape).getText());
			if (text != null) {
				((TextDecorator)shape).setText(text);
				return shape;
			}
			else
				return ((TextDecorator)shape).getShape();
		}
		else {
			String text = (String) JOptionPane.showInputDialog(
					null, "请输入文字", "文字描述", 0, null, null, null);
			if (text != null) {
				TextDecorator newShape = new TextDecorator(shape);
				newShape.setText(text);
				return newShape;
			}
			else
				return shape;
		}
	}
}
