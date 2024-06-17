package ShapeImplementor;

import java.awt.AlphaComposite;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.io.Serializable;

public class AppearanceImplementor implements AbstractImplementor, Serializable {
	
	private Color color;
	private float width;
	private float transparency;

	public AppearanceImplementor() {
		setColor(Color.black);
		setWidth(2);
		setTransparency(0.6f);
	}

	public AppearanceImplementor(Color color, float width, float transparency) {
		setColor(color);
		setWidth(width);
		setTransparency(transparency);
	}
	
	@Override
	public Color getColor() {
		return color;
	}

	@Override
	public void setColor(Color color) {
		this.color = color;
	}
	
	@Override
	public float getWidth() {
		return width;
	}

	@Override
	public void setWidth(float width) {
		this.width = width;
	}

	@Override
	public float getTransparency() {
		return transparency;
	}

	@Override
	public void setTransparency(float transparency) {
		this.transparency = transparency;
	}

	public void applyAppearance(Graphics2D g2) {
		g2.setPaint(getColor());
		g2.setStroke(new BasicStroke(getWidth()));
		g2.setComposite(AlphaComposite.getInstance(
				AlphaComposite.SRC_OVER, getTransparency()));
	}
}
