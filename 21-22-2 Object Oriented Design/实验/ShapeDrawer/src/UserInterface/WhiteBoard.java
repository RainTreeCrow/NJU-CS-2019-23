package UserInterface;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import ShapeFactory.AbstractFactory;
import ShapeImplementor.AbstractImplementor;
import ShapeImplementor.AppearanceImplementor;
import ShapeMemento.MementoCaretaker;
import ShapeMemento.ShapeMemento;
import ShapeModifier.AbstractModifier;
import Shapes.AbstractShape;

public class WhiteBoard extends JPanel{
	
	private ArrayList<AbstractShape> shapeList = new ArrayList<AbstractShape>();
	protected ArrayList<AbstractInterface> interfaceList =
			new ArrayList<AbstractInterface>();
	protected boolean changeSinceLastSaved = false;
	
	protected DrawInterface drawer = new DrawInterface(this);
	protected ModifyInterface selecter = new ModifyInterface(this);
	protected DefaultInterface defaulter = new DefaultInterface(this);
	protected AbstractImplementor implementor = new AppearanceImplementor();
	private MementoCaretaker mc = new MementoCaretaker();
	
	public WhiteBoard() {
		super();
		setFocusable(true);
		setBackground(Color.white);
		interfaceList.add(drawer);
		interfaceList.add(selecter);
		interfaceList.add(defaulter);
	}
	
	public ArrayList<AbstractShape> getShapeList() {
		return shapeList;
	}
	
	public AbstractShape getShape(int index) {
		return shapeList.get(index);
	}
	
	public void addShape(AbstractShape shape) {
		shapeList.add(shape);
	}
	
	public void removeShape(AbstractShape shape) {
		if (shapeList.contains(shape))
			shapeList.remove(shape);
	}
	
	public void changeShape(int index, AbstractShape newShape) {
		shapeList.set(index, newShape);
	}
	
	public void setDefaultMode() {
		for (AbstractInterface inter : interfaceList) {
			inter.switchOff();
		}
		defaulter.switchOn();
	}
	
	public void setDrawFactory(AbstractFactory factory) {
		for (AbstractInterface inter : interfaceList) {
			inter.switchOff();
		}
		drawer.switchOn();
		drawer.setFactory(factory);
	}
	
	public void setSelectModifier(AbstractModifier modifier) {
		for (AbstractInterface inter : interfaceList) {
			inter.switchOff();
		}
		selecter.switchOn();
		selecter.setModifier(modifier);
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		Graphics2D g2 = (Graphics2D)g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		for(AbstractShape item : shapeList) {
			item.drawSelf(g2);
			if (defaulter.selectedShape().contains(item))
				g2.drawString("Selected", item.getEnd().x, item.getEnd().y);
		}
		AbstractShape shape = drawer.currentShape();
		if(shape != null && shape.getStart() != null && shape.getEnd() != null) {
			shape.drawSelf(g2);
		}
		g.dispose();
	}
	
	public AbstractInterface currentMode() {
		for (AbstractInterface inter : interfaceList) {
			if (inter.isOn())
				return inter;
		}
		return defaulter;
	}
	
	public AbstractImplementor getImplementor() {
		return implementor;
	}
	
	public void setAppearance(AbstractImplementor implementor) {
		this.implementor = implementor;
	}
	
	public void clean() {
		shapeList.clear();
		repaint();
	}
	
	public void save(String path) {
		try {
			ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(path));
			os.writeObject(shapeList);
			os.close();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		changeSinceLastSaved = false;
	}
	
	@SuppressWarnings("unchecked")
	public void open(String path) {
		try {
			ObjectInputStream is = new ObjectInputStream(new FileInputStream(path));
			shapeList = (ArrayList<AbstractShape>) is.readObject();
			repaint();
			is.close();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void saveAsJPG(String path) {
		BufferedImage image = new BufferedImage(getWidth(), getHeight(),
				BufferedImage.TYPE_INT_RGB);
		paint(image.createGraphics());
		File file = new File(path);
		try {
			ImageIO.write(image, "jpg", file);
		}
		catch (IOException e) {
			e.printStackTrace();
		}	
	}
	
	public void saveMemento() {
		mc.addMemento(new ShapeMemento(shapeList));
		changeSinceLastSaved = true;
	}
	
	public void undoMemento() {
		ShapeMemento leftMemento = mc.getLeftMemento();
		if (leftMemento != null) {
			shapeList = leftMemento.getMementoList();
			repaint();
		}
	}
	
	public void redoMemento() {
		ShapeMemento rightMemento = mc.getRightMemento();
		if (rightMemento != null) {
			shapeList = rightMemento.getMementoList();
			repaint();
		}
	}
	
	public boolean changed() {
		return changeSinceLastSaved;
	}
	
	public void setChanged(boolean changed) {
		changeSinceLastSaved = changed;
	}
}
