package rl.huojing.dp.singleton;

public class SingletonClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		EagerSingleton eager = EagerSingleton.getInstance();
		eager.operation();
		
		LazySingleton theSingleton1 = LazySingleton.getInstance();
		LazySingleton theSingleton2 = LazySingleton.getInstance();
		if(theSingleton1 == theSingleton2){
			System.out.println("These two objects are the same.");
		}
		else{
			System.out.println("These two objects are not the same.");
		}
		theSingleton1.operation();
		theSingleton2.operation();
		
		LazyInitHolderSingleton theSingleton = LazyInitHolderSingleton.getInstance();
		theSingleton.operation();
		
		EnumSingleton uniqueInstance = EnumSingleton.uniqueInstance;
		uniqueInstance.operation();
		
		Singleton parent = Singleton.getInstance("rl.huojing.dp.singleton.Singleton");
		parent.test();
		SingletonChild1 child1 = SingletonChild1.getInstance();
		child1.test();
		Singleton child11 = SingletonChild1.getInstance("rl.huojing.dp.singleton.SingletonChild1");
		child11.test();
		if(parent == child1) {
			System.out.println("Parent and Child11 are the same.");
		}
		else {
			System.out.println("Parent and Child11 are not the same.");
		}
				
		if(child1==child11){
			System.out.println("Child1 and Child11 are the same.");
		}
		else{
			System.out.println("Child1 and Child11 are not the same.");
		}
	}

}
