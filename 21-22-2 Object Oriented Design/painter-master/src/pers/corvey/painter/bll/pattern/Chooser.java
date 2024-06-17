package pers.corvey.painter.bll.pattern;

import java.awt.Point;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import javax.swing.JPanel;

import pers.corvey.painter.bll.decoration.ChangeableDecoration;
import pers.corvey.painter.bll.decoration.ChangeableItf;
import pers.corvey.painter.bll.decoration.DecorationItf;
import pers.corvey.painter.model.shape.MyShapeItf;
import pers.corvey.painter.ui.AppearanceMenu;
import pers.corvey.painter.ui.Board;

/**
 * 选择模式（继承模式抽象类）
 */
public class Chooser extends PatternAbs {

	private DecorationItf decoration = new ChangeableDecoration();
	private MouseWheelListener mouseWheelListener;
	private KeyAdapter keyAdapter;
	
	public Chooser(JPanel board) {
		super();
		this.board = board;
		mouseAdapter = new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if(state) {
					Point2D point = new Point2D.Double(e.getX(), e.getY());
					start = new Point(e.getX(), e.getY());
					end = new Point(start);
					choose(point);
				}
			}
			@Override
			public void mouseReleased(MouseEvent e) {
				if(state && tag) {
					tag = false;
					board.repaint();
					start = end = null;
				}
			}
		};
		board.addMouseListener(mouseAdapter);
		
		mouseMotionAdapter = new MouseMotionAdapter() {
			@Override
			public void mouseDragged(MouseEvent e) {
				if(state && tag && myShape != null) {
					end.setLocation(e.getX(), e.getY());
					((ChangeableItf)decoration).move(start, end);
					board.repaint();
					start.setLocation(end);
				}
			}
		};
		board.addMouseMotionListener(mouseMotionAdapter);
		
		mouseWheelListener = new MouseWheelListener() {
			@Override
			public void mouseWheelMoved(MouseWheelEvent e) {
				if(state && myShape != null) {
					if(e.getWheelRotation() == -1)
						((ChangeableItf)decoration).zoomIn();
					else if (e.getWheelRotation() == 1)
						((ChangeableItf)decoration).zoomOut();
					board.repaint();
				}
			}
		};
		board.addMouseWheelListener(mouseWheelListener);
		
		keyAdapter = new KeyAdapter() {
			 public void keyPressed(KeyEvent e) {
				if(state && e.getKeyCode() == KeyEvent.VK_DELETE) {
					((Board)board).getArrayList().remove(myShape);
					board.repaint();
				}
			}
		};
		board.addKeyListener(keyAdapter);
	}

	/**
	 * 根据鼠标位置尝试去选中图形
	 * @param point - 鼠标位置
	 */
	public void choose(Point2D point) {
		myShape = null;
		appearance = null;
		decoration.setMyShape(null);
		ArrayList<MyShapeItf> shapes = ((Board)board).getArrayList();
		for(int i=shapes.size()-1; i>=0; --i) {
			MyShapeItf item = shapes.get(i);
			if(item.getJudger().judge(item.getShape(), point)) {
				myShape = item;
				appearance = item.getAppearance();
				AppearanceMenu.activeItemByAppearance(appearance);
				decoration.setMyShape(item);
				tag = true;
				break;
			}
		}
	}
	
	/**
	 * 修改被选中图形的外观属性
	 */
	@Override
	public void applyAppearance() {
		if(myShape != null) {
			myShape.setAppearance(appearance.clone());
			board.repaint();
		}
	}
}