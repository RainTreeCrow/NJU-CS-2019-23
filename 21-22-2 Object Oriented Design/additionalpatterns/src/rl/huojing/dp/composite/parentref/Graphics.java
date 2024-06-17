package rl.huojing.dp.composite.parentref;

import java.util.Vector;

public abstract class Graphics {
	public abstract void draw();
	public void add(Graphics g){
		throw new UnsupportedOperationException("add operation not supported");
	}
	public void remove(Graphics g){
		throw new UnsupportedOperationException("remove operation not supported");
	}
	public Graphics getChild(int i){
		throw new UnsupportedOperationException("getChild operation not supported");
	}
	/*------------------------*/
	private Graphics parent = null;
	public Graphics getParent(){
		return parent;
	}
	public void setParent(Graphics parent){
		this.parent = parent; 
	}
	public Vector<Graphics> getChildren(){
		throw new UnsupportedOperationException("getChildren operation not supported");
	}
}
