package pers.corvey.painter.bll.pattern;

import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseMotionAdapter;

import javax.swing.JPanel;

import pers.corvey.painter.bll.bridge.AppearanceImpl;
import pers.corvey.painter.bll.bridge.AppearanceItf;
import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 模式抽象类
 */
public abstract class PatternAbs {
	/**
	 * 外观属性（桥接模式）
	 */
	protected AppearanceItf appearance = new AppearanceImpl();
	
	/**
	 * 模式当前状态（true为可用，false为不可用）
	 */
	protected boolean state = false;
	
	/**
	 * 鼠标点击事件标识符
	 */
	protected boolean tag = false;
	protected MouseAdapter mouseAdapter;
	protected MouseMotionAdapter mouseMotionAdapter;
	protected Point start, end;
	protected MyShapeItf myShape;
	
	/**
	 * 画板
	 */
	protected JPanel board;
	
	/**
	 * 设置模式状态（true为可用，false为不可用）
	 */
	public void setState(boolean state) {
		this.state = state;
	}
	
	/**
	 * 获取外观属性
	 * @return 外观属性
	 */
	public AppearanceItf getApperance() {
		return appearance;
	}
	
	/**
	 * 设置外观属性
	 * @param appearance - 外观属性
	 */
	public void setAppearance(AppearanceItf appearance) {
		this.appearance = appearance;
	}
	
	public MyShapeItf getMyShape() {
		return myShape;
	}
	
	/**
	 * 应用外观属性
	 */
	public abstract void applyAppearance();
}
