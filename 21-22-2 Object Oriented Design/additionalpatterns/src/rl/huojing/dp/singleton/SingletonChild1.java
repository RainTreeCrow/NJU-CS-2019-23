package rl.huojing.dp.singleton;

public class SingletonChild1 extends Singleton {
	protected SingletonChild1(){}
    public  static  SingletonChild1 getInstance() {
           return (SingletonChild1)Singleton.getInstance("rl.huojing.dp.singleton.SingletonChild1");      
    }

    public void test()    {
       System.out.println("get SingletonChild1 class success!");
    }
}
