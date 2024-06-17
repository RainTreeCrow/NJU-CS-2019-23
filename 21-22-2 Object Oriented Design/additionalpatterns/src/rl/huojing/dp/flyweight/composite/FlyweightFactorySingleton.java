package rl.huojing.dp.flyweight.composite;

import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

public class FlyweightFactorySingleton {
	private HashMap<Character, Flyweight> files = new HashMap<Character, Flyweight>();

	private static FlyweightFactorySingleton instance = new FlyweightFactorySingleton();
	
	/*
	 * ��������˽�еģ��ⲿ�޷�ֱ��ʵ����
	 */	
	private FlyweightFactorySingleton(){		
	}
	
	/*
	 * ��̬����������������ṩΨһ��ʵ��
	 */
	public static FlyweightFactorySingleton getInstance(){
		return instance;
	}
	
	/*
	 * ������Ԫ��������������״̬�Բ�����ʽ���� 
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
	 * ������Ԫ��������������״̬�Բ�����ʽ����
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
