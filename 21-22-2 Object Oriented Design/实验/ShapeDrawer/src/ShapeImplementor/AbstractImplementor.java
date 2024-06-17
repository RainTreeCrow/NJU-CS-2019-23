package ShapeImplementor;

import java.awt.Color;
import java.awt.Graphics2D;

public interface AbstractImplementor {
	public Color getColor();
	public void setColor(Color color);
	public float getWidth();
	public void setWidth(float width);
	public float getTransparency();
	public void setTransparency(float transparency);
	public void applyAppearance(Graphics2D g2);
}
