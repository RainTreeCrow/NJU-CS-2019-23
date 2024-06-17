package rl.huojing.dp.iterator.blackbox;

public class ConcreteAggregate extends Aggregate {
	public Object[] objs  = {"Monk Tang", "Monkey","Pigsy","Sandy","Horse"};
	
	@Override
	public Iterator createIterator() {
		return new ConcreteIterator();
	}
	
	/**
	 * 内部成员类：具体迭代子类
	 *
	 */
	private class ConcreteIterator implements Iterator{
		private int currentIndex = 0;
		
		public void first(){
			currentIndex = 0;
		}
		
		public void next(){
			if(currentIndex<objs.length){
				currentIndex++;
			}
		}
		
		public boolean isDone(){
			return (currentIndex == objs.length);
		}
		
		public Object currentItem(){
			return objs[currentIndex];
		}
	}
}
