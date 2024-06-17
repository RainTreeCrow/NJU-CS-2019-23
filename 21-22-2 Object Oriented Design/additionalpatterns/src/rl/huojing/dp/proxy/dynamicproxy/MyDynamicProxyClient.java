package rl.huojing.dp.proxy.dynamicproxy;

import java.lang.reflect.Proxy;

public class MyDynamicProxyClient {
	public Person getOwnerPersonBeanProxy(Person person){
		return (Person)Proxy.newProxyInstance(person.getClass().getClassLoader(),
				person.getClass().getInterfaces(), new OwnerInvocationHandler(person));
	}

	public Person getNotOwnerProxy(Person person){
		return (Person)Proxy.newProxyInstance(person.getClass().getClassLoader(),
				person.getClass().getInterfaces(), new NotOwnerInvocationHandler(person));
	}
	
	public void test(){
		//
		System.out.println("---test OwnerInvocationHandler---");
		Person person1 = getPersonBeanFromDB1();
		Person personProxy = getOwnerPersonBeanProxy(person1);
		System.out.println(personProxy.getName());
		try {
			personProxy.setRate(2);
		} catch (Exception e) {
			System.out.println("can not setRate");
		}

		//
		System.out.println("---test NotOwnerInvocationHandler---");
		Person person2 = getPersonBeanFromDB2();
		Person personProxy2 = getNotOwnerProxy(person2);
		System.out.println(personProxy2.getName());
		personProxy2.setRate(2);
		System.out.println(personProxy2.getRate());
		try{
			personProxy2.setGender("girl");
		} catch(Exception e){
			System.out.println("can not set other property");
		}
	}

	private Person getPersonBeanFromDB1(){
		Person pb = new PersonImpl();
		pb.setName("remy");
		pb.setGender("girl");
		pb.setRate(1);
		return pb; 
	}
	
	private Person getPersonBeanFromDB2(){
		Person pb = new PersonImpl();
		pb.setName("Jack");
		pb.setGender("boy");
		pb.setRate(1);
		return pb; 
	}

	public static void main(String[] args) {
		MyDynamicProxyClient mdp = new MyDynamicProxyClient();
		mdp.test();
	}
}
