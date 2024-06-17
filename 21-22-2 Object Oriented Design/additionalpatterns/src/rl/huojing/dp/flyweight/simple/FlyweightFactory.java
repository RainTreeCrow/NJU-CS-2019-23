package rl.huojing.dp.flyweight.simple;

import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

public class FlyweightFactory {
	private HashMap<Character, Flyweight> files = new HashMap<Character, Flyweight>();
	
	public FlyweightFactory(){		
	}
	/*
	 * 生成一个内部状态为传入参数的享元对象，并保存在hash map中
	 */
	public Flyweight factory(Character state){
		if(files.containsKey(state)){
			return (Flyweight)files.get(state);
		}
		else{
			Flyweight fly = new ConcreteFlyweight(state);
			files.put(state, fly);
			return fly;
		}
	}

	@SuppressWarnings("unchecked")
	/*
	 * 辅助方法，检查所有独立的享元对象
	 */
	public void checkFlyweight(){
		int i = 0;
		System.out.println("===============checkFlyweight()===============");
		for(Iterator<?> it = files.entrySet().iterator();it.hasNext();){
			Map.Entry<Character, Flyweight> e=(Map.Entry<Character, Flyweight>)it.next();
			System.out.println("Item "+(++i)+": "+e.getKey());
		}
		System.out.println("===============checkFlyweight()===============");
	}
}
