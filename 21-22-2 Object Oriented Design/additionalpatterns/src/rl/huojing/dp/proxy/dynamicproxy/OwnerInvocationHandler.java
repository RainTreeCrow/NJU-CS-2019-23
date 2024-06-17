package rl.huojing.dp.proxy.dynamicproxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class OwnerInvocationHandler implements InvocationHandler {
	private Person personBean;
	
	public OwnerInvocationHandler(Person person){
		this.personBean = person;
	}
	
	@Override
	public Object invoke(Object proxy, Method method, Object[] args)
	throws Throwable {
		try {
			if(method.getName().startsWith("get")){
				//如果方法名为get，就调用person类内的get相应方法
				return method.invoke(personBean, args);
			}else if(method.getName().equals("setRate")){ 
				// 如果方法是setRate，则抛出异常
				throw new IllegalAccessException("access deny");
			}else if(method.getName().startsWith("set")){ 
				//如果为set，就调用person类内的set相应方法
				return method.invoke(personBean, args);
			}else {
				System.out.println("non method invoke");
			}

		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return null;			
	}
}
