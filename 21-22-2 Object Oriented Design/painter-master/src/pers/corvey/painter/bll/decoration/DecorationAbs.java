package pers.corvey.painter.bll.decoration;

import java.awt.Shape;

import pers.corvey.painter.model.shape.MyShapeAbs;
import pers.corvey.painter.model.shape.MyShapeItf;

public abstract class DecorationAbs extends MyShapeAbs implements DecorationItf {
	
	protected MyShapeItf myShape;
	
	public MyShapeItf getMyShape() {
		return myShape;
	}
	
	public void setMyShape(MyShapeItf myShape) {
		this.myShape = myShape;
	}
	
	public Shape createShape() {
		return myShape.createShape();
	}
}
