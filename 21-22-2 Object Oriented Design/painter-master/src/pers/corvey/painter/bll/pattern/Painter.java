package pers.corvey.painter.bll.pattern;

import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import javax.swing.JPanel;

import pers.corvey.painter.bll.factory.FactoryItf;
import pers.corvey.painter.bll.factory.LineFactory;
import pers.corvey.painter.ui.Board;

/**
 * 画笔模式（继承模式抽象类）
 */
public class Painter extends PatternAbs {
	
	private FactoryItf factory;
	
	public Painter(JPanel board) {
		super();
		this.board = board;
		setFactory(new LineFactory());
		mouseAdapter = new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if(state) {
					myShape = getFactory().createProduct();
					applyAppearance();
					start = new Point(e.getX(), e.getY());
					end = new Point(start);
					myShape.setStartPoint(start);
					myShape.setEndPoint(end);
					tag = true;						
				}
			}
			@Override
			public void mouseReleased(MouseEvent e) {
				if(state && tag) {
					((Board)board).getArrayList().add(myShape);
					tag = false;
					board.repaint();
					myShape = null;
					start = end = null;
				}
			}
		};
		board.addMouseListener(mouseAdapter);
		
		mouseMotionAdapter = new MouseMotionAdapter() {
			@Override
			public void mouseDragged(MouseEvent e) {
				if(state && tag) {
					end.setLocation(e.getX(), e.getY());
					myShape.setEndPoint(end);
					board.repaint();
				}
			}
		};
		board.addMouseMotionListener(mouseMotionAdapter);
	}

	public FactoryItf getFactory() {
		return factory;
	}
	public void setFactory(FactoryItf factory) {
		this.factory = factory;
	}

	/**
	 * 将画笔当前的外观属性克隆一份新的并赋给刚刚画的图形
	 */
	@Override
	public void applyAppearance() {
		if(myShape != null)
			myShape.setAppearance(getApperance().clone());
	}
}