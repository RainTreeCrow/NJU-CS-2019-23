package rl.huojing.dp.singleton;

import java.util.HashMap;

public class Singleton {
	//用来存放对应关系
	private static HashMap sinRegistry = new HashMap();
	private static Singleton s = new Singleton();

	//受保护的构造函数
	protected Singleton() {}

	public static Singleton getInstance(String name){
		if(name == null)
			name = "Singleton";
		if(sinRegistry.get(name)==null){
			try{
				sinRegistry.put(name , Class.forName(name).newInstance());

			}catch(Exception e){
				e.printStackTrace();
			}      
		}
		return (Singleton)(sinRegistry.get(name));  
	}

	public void test(){
		System.out.println("get Singleton class success!");       
	}
}
