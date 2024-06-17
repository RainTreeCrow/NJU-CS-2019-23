package rl.huojing.dp.flyweight.composite;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class ConcreteCompositeFlyweight extends Flyweight {
	private HashMap<Character, Flyweight> files = new HashMap<Character, Flyweight>();
	
	public ConcreteCompositeFlyweight(){		
	}
	
	/*
	 * ����һ���µĵ�����Ԫ���󵽾ۼ���
	 */
	public void add(Character key, Flyweight fly){
		files.put(key, fly);
	}
	
	@SuppressWarnings("unchecked")
	@Override
	/*
	 * �ⲿ״̬��Ϊ�������뷽���У��ı䷽������Ϊ�����ǲ��ı������ڲ�״̬
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
