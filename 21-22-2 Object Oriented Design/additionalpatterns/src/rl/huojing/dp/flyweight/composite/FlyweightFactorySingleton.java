package rl.huojing.dp.flyweight.composite;

import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

public class FlyweightFactorySingleton {
	private HashMap<Character, Flyweight> files = new HashMap<Character, Flyweight>();

	private static FlyweightFactorySingleton instance = new FlyweightFactorySingleton();
	
	/*
	 * 构造子是私有的，外部无法直接实例化
	 */	
	private FlyweightFactorySingleton(){		
	}
	
	/*
	 * 静态工厂方法，向外界提供唯一的实例
	 */
	public static FlyweightFactorySingleton getInstance(){
		return instance;
	}
	
	/*
	 * 复合享元工厂方法，所需状态以参量形式传入 
	 */
	public synchronized Flyweight factory(String compositeState){
		ConcreteCompositeFlyweight compositeFly = new ConcreteCompositeFlyweight();
		int length = compositeState.length();
		Character state = null;
		for(int i=0;i<length;i++){
			state = new Character(compositeState.charAt(i));
			System.out.println("factor("+state+")");
			compositeFly.add(state, this.factory(state));
		}
		return compositeFly;
	}
	/*
	 * 单纯享元工厂方法，所需状态以参量形式传入
	 */
	public synchronized Flyweight factory(Character state){
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
