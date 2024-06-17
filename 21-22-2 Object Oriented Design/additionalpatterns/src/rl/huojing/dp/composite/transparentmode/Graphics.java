package rl.huojing.dp.composite.transparentmode;

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
}
