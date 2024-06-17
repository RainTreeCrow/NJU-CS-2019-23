package pers.corvey.painter.bll.bridge;

import java.awt.AlphaComposite;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.io.Serializable;

/**
 * 外观属性具体类
 */
public class AppearanceImpl implements AppearanceItf, Serializable, Cloneable {

	private Color color; // 颜色
	private float width; // 粗细
	private float transparency; // 透明度

	public AppearanceImpl() {
		setColor(Color.black);
		setWidth(2);
		setTransparency(0.6f);
	}

	public AppearanceImpl(Color color, float width, float transparency) {
		setColor(color);
		setWidth(width);
		setTransparency(transparency);
	}

	public AppearanceItf clone() {
		try {
			return (AppearanceItf) super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return null;
	}

	@Override
	public float getTransparency() {
		return transparency;
	}

	@Override
	public void setTransparency(float transparency) {
		this.transparency = transparency;
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
	public Color getColor() {
		return color;
	}

	@Override
	public void setColor(Color color) {
		this.color = color;
	}

	public void applyAppearance(Graphics2D g2) {
		g2.setPaint(getColor());
		g2.setStroke(new BasicStroke(getWidth()));
		g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, getTransparency()));
	}
}
