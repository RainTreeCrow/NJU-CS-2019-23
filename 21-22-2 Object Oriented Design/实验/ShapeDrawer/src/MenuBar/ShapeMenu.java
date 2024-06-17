package MenuBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenuItem;

import ShapeFactory.AbstractFactory;
import ShapeFactory.CircleFactory;
import ShapeFactory.LineFactory;
import ShapeFactory.OvalFactory;
import ShapeFactory.RectangleFactory;
import ShapeFactory.TriangleFactory;
import UserInterface.WhiteBoard;

public class ShapeMenu extends AbstractMenu {
	
	private WhiteBoard board;
	
	private JMenuItem mi_triangle = new JMenuItem("三角形");
	private JMenuItem mi_rectangle = new JMenuItem("方框");
	private JMenuItem mi_circle = new JMenuItem("圆形");
	private JMenuItem mi_oval = new JMenuItem("椭圆");
	private JMenuItem mi_line = new JMenuItem("连接线");
	
	public ShapeMenu(WhiteBoard board) {
		super("绘制");
		this.board = board;
		
		mi_triangle.addActionListener(
				createActionListener(mi_triangle, new TriangleFactory()));
		add(mi_triangle);
		
		mi_rectangle.addActionListener(
				createActionListener(mi_rectangle, new RectangleFactory()));
		add(mi_rectangle);
		
		mi_circle.addActionListener(
				createActionListener(mi_circle, new CircleFactory()));
		add(mi_circle);
		
		mi_oval.addActionListener(
				createActionListener(mi_oval, new OvalFactory()));
		add(mi_oval);
		
		mi_line.addActionListener(
				createActionListener(mi_line, new LineFactory()));
		add(mi_line);
	}
	
	public ActionListener createActionListener(JMenuItem item, AbstractFactory factory) {
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				selectShapeFactory(item, factory);
			}
		};
	}
	
	public void selectShapeFactory(JMenuItem item, AbstractFactory factory) {
		board.setDrawFactory(factory);
		setActiveItem(item);
	}
}