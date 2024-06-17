package rl.huojing.dp.iterator.whitebox;

public class ConcreteIterator implements Iterator {
	
	private ConcreteAggregate agg;
	private int index = 0;
	private int size = 0;
	
	public ConcreteIterator(ConcreteAggregate agg){
		this.agg = agg;
		size = agg.size();
		index = 0;
	}

	public Object currentItem() {		
		return agg.getElement(index);
	}

	public void first() {
		index = 0;
	}

	public boolean isDone() {
		return (index>=size);	
	}

	public void next() {
		if(index<size){
			index++;
		}
	}

}
