package rl.huojing.dp.proxy.dynamicproxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

public class NotOwnerInvocationHandler implements InvocationHandler {
	private Person person;
	
	public NotOwnerInvocationHandler(Person person){
		this.person = person;
	}

	@Override
	public Object invoke(Object proxy, Method method, Object[] args)
	throws Throwable {
		if(method.getName().startsWith("setRate")){
			return method.invoke(person, args);
		}else if (method.getName().startsWith("get")){
			return method.invoke(person, args);
		} else {
			throw new IllegalAccessException("access deny");			
		}
	}

}
