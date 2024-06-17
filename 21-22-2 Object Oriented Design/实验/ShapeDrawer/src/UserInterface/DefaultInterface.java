package UserInterface;

import java.awt.Point;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.io.IOException;
import java.util.ArrayList;

import Shapes.AbstractShape;
import Shapes.CompositeShape;

public class DefaultInterface extends AbstractInterface {
	
	protected AbstractShape shape;
	protected ArrayList<AbstractShape> selectedList = new ArrayList<AbstractShape>();
	
	protected boolean left_pressing;
	protected boolean right_pressing;
	protected boolean select_pressing;
	protected boolean composite_pressing;
	protected boolean duplicate_pressing;
	protected boolean erase_pressing;
	protected boolean fragment_pressing;
	protected boolean cross_pressing;
	
	Point start;
	Point end;
	int index;
	KeyAdapter keyAdapter;
	
	public DefaultInterface(WhiteBoard board) {
		super();
		this.board = board;
		left_pressing = false;
		right_pressing = false;
		select_pressing = false;
		composite_pressing = false;
		index = -1;
		
		mouseAdapter = new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if(on) {
					if (e.getButton() == MouseEvent.BUTTON3) {
						left_pressing = true;
						start = new Point(e.getX(), e.getY());
						index = select(start);
						end = new Point(start);
					}
					else if (e.getButton() == MouseEvent.BUTTON1)
						right_pressing = true;
				}
			}
			@Override
			public void mouseReleased(MouseEvent e) {
				if(on && right_pressing) {
					if (e.getButton() == MouseEvent.BUTTON1) {
						if (select_pressing) {
							int temp = select(e.getPoint());
							if (temp != -1) {
								AbstractShape selected = board.getShape(temp);
								if (!selectedList.contains(selected)) {
									selectedList.add(selected);
									board.repaint();
								}
							}
						}
						right_pressing = false;
					}
				}
				else if (on && left_pressing) {
					if (e.getButton() == MouseEvent.BUTTON3) {
						end.setLocation(e.getX(), e.getY());
						if (index != -1) {
							board.getShape(index).move(start, end);
							board.repaint();
							board.saveMemento();
						}
						index = -1;
						left_pressing = false;
					}
				}
			}
		};
		board.addMouseListener(mouseAdapter);
		
		mouseMotionAdapter = new MouseMotionAdapter() {
			@Override
			public void mouseDragged(MouseEvent e) {
				if(on && left_pressing) {
					start.setLocation(end);
					end.setLocation(e.getX(), e.getY());
					if (index != -1) {
						board.getShape(index).move(start, end);
						board.repaint();
					}
				}
			}
		};
		board.addMouseMotionListener(mouseMotionAdapter);
		
		keyAdapter = new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				if (on) {
					if (e.getKeyCode() == KeyEvent.VK_S) {
						select_pressing = true;
					}
					else if (e.getKeyCode() == KeyEvent.VK_C)
						composite_pressing = true;
					else if (e.getKeyCode() == KeyEvent.VK_D)
						duplicate_pressing = true;
					else if (e.getKeyCode() == KeyEvent.VK_E)
						erase_pressing = true;
					else if (e.getKeyCode() == KeyEvent.VK_F)
						fragment_pressing = true;
					else if (e.getKeyCode() == KeyEvent.VK_X)
						cross_pressing = true;
				}
			}
			@Override
			public void keyReleased(KeyEvent e) {
				if (on) {
					if (select_pressing)
						select_pressing = false;
					else if (composite_pressing) {
						if (selectedList.size() > 1) {
							board.addShape(new CompositeShape(selectedList));
							for (AbstractShape shape : selectedList) {
								board.removeShape(shape);
							}
							board.repaint();
							board.saveMemento();
						}
						composite_pressing = false;
						selectedList = new ArrayList<AbstractShape>();
					}
					else if (duplicate_pressing && !selectedList.isEmpty()) {
						for (AbstractShape shape : selectedList) {
							try {
								AbstractShape copy = shape.deepClone();
								copy.move(20, 20);
								board.addShape(copy);
							}
							catch (ClassNotFoundException | IOException e1) {
								e1.printStackTrace();
							}
						}
						board.repaint();
						board.saveMemento();
						duplicate_pressing = false;
						selectedList = new ArrayList<AbstractShape>();
					}
					else if (erase_pressing && !selectedList.isEmpty()) {
						for (AbstractShape shape : selectedList)
							board.removeShape(shape);
						board.repaint();
						board.saveMemento();
						erase_pressing = false;
						selectedList = new ArrayList<AbstractShape>();
					}
					else if (fragment_pressing && !selectedList.isEmpty()) {
						for (AbstractShape shape : selectedList) {
							if (shape.getClass().equals(CompositeShape.class)) {
								ArrayList<AbstractShape> tempList = ((CompositeShape)shape).getShapeList();
								for (AbstractShape tempShape : tempList)
									board.addShape(tempShape);
								board.removeShape(shape);
							}
						}
						board.repaint();
						board.saveMemento();
						fragment_pressing = false;
						selectedList = new ArrayList<AbstractShape>();
					}
					else if (cross_pressing && !selectedList.isEmpty()) {
						cross_pressing = false;
						selectedList = new ArrayList<AbstractShape>();
						board.repaint();
					}
				}
			}
		};
		board.addKeyListener(keyAdapter);
	}
	
	public ArrayList<AbstractShape> selectedShape() {
		return selectedList;
	}
	
	@Override
	public void implement() { }
}
