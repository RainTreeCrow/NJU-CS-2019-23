package rl.huojing.dp.singleton;

public enum EnumSingleton {
	uniqueInstance;
	
	public void operation(){
		System.out.println("EnumSingleton.operation() is executed");
	}
}
