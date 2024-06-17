package rl.huojing.dp.singleton;

public class LazyInitHolderSingleton {
	private static class SingletonHolder{
		private static LazyInitHolderSingleton instance = new LazyInitHolderSingleton();
	}
	
	private LazyInitHolderSingleton(){		
	}
	
	public static LazyInitHolderSingleton getInstance(){
		return SingletonHolder.instance;
	}
	
	public void operation(){
		System.out.println("LazyInitHolderSignleton.operation() is executed");
	}
}
