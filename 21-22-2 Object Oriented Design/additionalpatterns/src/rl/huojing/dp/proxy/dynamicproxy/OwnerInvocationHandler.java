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
				//���������Ϊget���͵���person���ڵ�get��Ӧ����
				return method.invoke(personBean, args);
			}else if(method.getName().equals("setRate")){ 
				// ���������setRate�����׳��쳣
				throw new IllegalAccessException("access deny");
			}else if(method.getName().startsWith("set")){ 
				//���Ϊset���͵���person���ڵ�set��Ӧ����
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
