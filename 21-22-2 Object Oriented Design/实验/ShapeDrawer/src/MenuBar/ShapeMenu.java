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
	
	private JMenuItem mi_triangle = new JMenuItem("������");
	private JMenuItem mi_rectangle = new JMenuItem("����");
	private JMenuItem mi_circle = new JMenuItem("Բ��");
	private JMenuItem mi_oval = new JMenuItem("��Բ");
	private JMenuItem mi_line = new JMenuItem("������");
	
	public ShapeMenu(WhiteBoard board) {
		super("����");
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