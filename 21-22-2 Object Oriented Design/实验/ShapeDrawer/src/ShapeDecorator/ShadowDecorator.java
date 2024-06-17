package ShapeDecorator;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.io.IOException;

import ShapeImplementor.AppearanceImplementor;
import Shapes.AbstractShape;

public class ShadowDecorator extends AbstractDecorator {
	
	AbstractShape shadow;
	
	public ShadowDecorator(AbstractShape shape, int x) {
		super(shape);
		try {
			shadow = shape.deepClone();
		}
		catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}
		Color shapeColor = shape.getAppearance().getColor();
		AppearanceImplementor shadowAppearance =
				new AppearanceImplementor(shapeColor, 1, 0.2f);
		shadow.setAppearance(shadowAppearance);
		switch (x) {
		case 0:
			shadow.move(-5, -5);
			break;
		case 1:
			shadow.move(-5, 5);
			break;
		case 2:
			shadow.move(5, -5);
			break;
		case 3:
			shadow.move(5, 5);
			break;
		default:
			break;
		}
	}
	
	@Override
	public void drawSelf(Graphics2D g2) {
		shadow.drawSelf(g2);
		shape.drawSelf(g2);
	}
	
	@Override
	public void move(Point s, Point e) {
		int x = e.x - s.x;
		int y = e.y - s.y;
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		shadow.move(s, e);
		shape.move(s, e);
	}
	
	@Override
	public void move(int x, int y) {
		start.setLocation(start.x + x, start.y + y);
		end.setLocation(end.x + x, end.y + y);
		shadow.move(x, y);
		shape.move(x, y);
	}
}
