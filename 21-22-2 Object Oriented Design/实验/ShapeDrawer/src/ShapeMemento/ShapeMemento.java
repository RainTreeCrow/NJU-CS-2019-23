package ShapeMemento;

import java.io.IOException;
import java.util.ArrayList;

import Shapes.AbstractShape;

public class ShapeMemento {
	ArrayList<AbstractShape> mementoList = new ArrayList<AbstractShape>();
	public ShapeMemento() { }
	public ShapeMemento(ArrayList<AbstractShape> shapeList) {
		for (AbstractShape shape : shapeList) {
			try {
				mementoList.add(shape.deepClone());
			}
			catch (ClassNotFoundException | IOException e) {
				e.printStackTrace();
			}
		}
	}
	public ArrayList<AbstractShape> getMementoList() {
		ArrayList<AbstractShape> tempList = new ArrayList<AbstractShape>();
		for (AbstractShape shape : mementoList) {
			try {
				tempList.add(shape.deepClone());
			}
			catch (ClassNotFoundException | IOException e) {
				e.printStackTrace();
			}
		}
		return tempList;
	}
}
