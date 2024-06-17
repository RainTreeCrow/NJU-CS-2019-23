package rl.huojing.dp.iterator.blackbox;

public class IntrinsicIteratorClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Aggregate agg = new ConcreteAggregate();
		Iterator it = agg.createIterator();
		while(!it.isDone()){
			System.out.println(it.currentItem().toString());
			it.next();
		}
	}

}
