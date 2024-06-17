package rl.huojing.dp.iterator.java;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ConcreteAggregate extends Aggregate {	
	private List<String> list = new ArrayList<String>();
	
	public ConcreteAggregate(){
		String[] objs  = {"Monk Tang", "Monkey","Pigsy","Sandy","Horse"};
		for (int i=0;i<objs.length;i++){
			list.add(objs[i]);
		}
	}
	
	@Override
	public Iterator<String> createIterator() {
		return list.iterator();
	}

}
