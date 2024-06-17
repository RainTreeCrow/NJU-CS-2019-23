package ShapeDecorator;

import java.awt.Graphics2D;

import Shapes.AbstractShape;

public class TextDecorator extends AbstractDecorator {
	
	String text;
	
	public TextDecorator(AbstractShape shape) {
		super(shape);
	}
	
	public void setText(String text) {
		this.text = text;
	}
	
	public String getText() {
		return text;
	}
	
	public AbstractShape getShape() {
		return shape;
	}
	
	@Override
	public void drawSelf(Graphics2D g2) {
		shape.drawSelf(g2);
		g2.drawString(text, shape.getStart().x - 10, shape.getStart().y - 10);
	}
}
