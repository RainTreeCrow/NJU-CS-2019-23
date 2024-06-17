package pers.corvey.painter.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

import pers.corvey.painter.bll.factory.CircleFactory;
import pers.corvey.painter.bll.factory.EllipseFactory;
import pers.corvey.painter.bll.factory.FactoryItf;
import pers.corvey.painter.bll.factory.LineFactory;
import pers.corvey.painter.bll.factory.RectangleFactory;
import pers.corvey.painter.bll.factory.RhombusFactory;
import pers.corvey.painter.bll.factory.RoundRectangleFactory;
import pers.corvey.painter.bll.factory.TriangleFactory;

/**
 * 图形菜单（继承我的菜单）
 */
public class ShapeMenu extends MyJMenu {
	
	private final static FactoryItf default_factory = new LineFactory();
	private JPanel board;
	private JMenuItem mi_line = new JMenuItem("线段");
	private JMenuItem mi_triangle = new JMenuItem("三角形");
	private JMenuItem mi_rectangle = new JMenuItem("矩形");
	private JMenuItem mi_roundRectangle = new JMenuItem("圆角矩形");
	private JMenuItem mi_rhombus = new JMenuItem("菱形");
	private JMenuItem mi_circle = new JMenuItem("圆形");
	private JMenuItem mi_ellipse = new JMenuItem("椭圆");
	
	public ShapeMenu(JPanel board) {
		super("图形");
		this.board = board;
		applySetting(mi_line, default_factory);
		
		mi_line.addActionListener(createActionListener(mi_line, new LineFactory()));
		add(mi_line);
		
		mi_triangle.addActionListener(createActionListener(mi_triangle, new TriangleFactory()));
		add(mi_triangle);
		
		mi_rectangle.addActionListener(createActionListener(mi_rectangle, new RectangleFactory()));
		add(mi_rectangle);
		
		mi_roundRectangle.addActionListener(createActionListener(mi_roundRectangle, 
																 new RoundRectangleFactory()));
		add(mi_roundRectangle);
		
		mi_rhombus.addActionListener(createActionListener(mi_rhombus, new RhombusFactory()));
		add(mi_rhombus);
		
		mi_circle.addActionListener(createActionListener(mi_circle, new CircleFactory()));
		add(mi_circle);
		
		mi_ellipse.addActionListener(createActionListener(mi_ellipse, new EllipseFactory()));
		add(mi_ellipse);
	}
	
	/**
	 * 生成对应的监听器
	 */
	public ActionListener createActionListener(JMenuItem item, FactoryItf factory) {
		return new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				applySetting(item, factory);
			}
		};
	}
	
	/**
	 * 应用设置
	 */
	public void applySetting(JMenuItem item, FactoryItf factory) {
		((Board)board).getPainter().setFactory(factory);
		setActiveItem(item);
	}
}
