package rl.huojing.dp.singleton;

public class EagerSingleton {
	//is it thread-safe? 
    private static final EagerSingleton instance = new EagerSingleton() ;
    
    private EagerSingleton() {}
    
    public static EagerSingleton getInstance()
    {
        return instance ;
    }
	public void operation(){
		System.out.println("EagerSignleton.operation() is executed");
	}
}
