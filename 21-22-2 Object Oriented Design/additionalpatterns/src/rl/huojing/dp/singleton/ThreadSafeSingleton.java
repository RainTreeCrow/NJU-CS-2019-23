package rl.huojing.dp.singleton;

public class ThreadSafeSingleton {
	private static ThreadSafeSingleton instance = null;
	protected ThreadSafeSingleton(){
		System.out.println("Singleton's consturct method is invoked. " +
				"This method should not be public");
	}
	//double-check locking
	public static ThreadSafeSingleton getInstance(){
		if (instance == null){
			synchronized (ThreadSafeSingleton.class){
				if(instance == null){
					instance = new ThreadSafeSingleton();		
				}
			}
		}
		return instance;
	}
	public void operation(){
		System.out.println("ThreadSafeSingleton.operation() is executed");
	}
}
