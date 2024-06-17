package rl.huojing.dp.composite.parentref;

import java.util.Vector;

public class Picture extends Graphics {

	private Vector<Graphics> list = new Vector<Graphics>();
	
	@Override
	public void draw() {
		System.out.println("draw a picture frame");
		for(int i=0;i<list.size();i++){
			Graphics g = (Graphics)list.get(i);
			g.draw();
		}
	}
	
	public void add(Graphics g){
		list.add(g);
		g.setParent(this);
	}
	
	public void remove(Graphics g){
		int index = list.indexOf(g);
		if(index!=-1){
			for (Graphics gra : g.getChildren()){
				gra.setParent(this);
				list.add(gra);
			}
		}
		list.remove(g);
	}
	
	public Graphics getChild(int i){
		return (Graphics)list.get(i);
	}

	public Vector<Graphics> getChildren(){
		return list;
	}
}
