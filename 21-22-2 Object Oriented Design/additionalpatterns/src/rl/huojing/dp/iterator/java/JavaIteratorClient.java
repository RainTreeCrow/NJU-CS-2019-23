package rl.huojing.dp.iterator.java;

import java.util.Iterator;

public class JavaIteratorClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Aggregate agg = new ConcreteAggregate();
		Iterator<String> it = agg.createIterator();
		while(it.hasNext()){
			System.out.println(it.next());			
		}
	}
}
