package rl.huojing.dp.flyweight.composite;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class ConcreteCompositeFlyweight extends Flyweight {
	private HashMap<Character, Flyweight> files = new HashMap<Character, Flyweight>();
	
	public ConcreteCompositeFlyweight(){		
	}
	
	/*
	 * 增加一个新的单纯享元对象到聚集中
	 */
	public void add(Character key, Flyweight fly){
		files.put(key, fly);
	}
	
	@SuppressWarnings("unchecked")
	@Override
	/*
	 * 外部状态作为参量传入方法中，改变方法的行为，但是不改变对象的内部状态
	 */
	public void operation(String extrinsicState) {
		Flyweight fly = null;
		for(Iterator<?> it = files.entrySet().iterator();it.hasNext();){
			Map.Entry<Character, Flyweight> e = (Map.Entry<Character, Flyweight>)it.next();
			fly = (Flyweight)e.getValue();
			fly.operation(extrinsicState);
		}

	}

}
