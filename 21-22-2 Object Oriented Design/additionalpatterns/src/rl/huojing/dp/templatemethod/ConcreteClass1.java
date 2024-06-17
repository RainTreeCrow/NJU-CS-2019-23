package rl.huojing.dp.templatemethod;

public class ConcreteClass1 extends AbstractClass{

   /**
    * 基本方法的实现
    */
	public void doOperation1(){
		System.out.println("ConcreteClass1 doOpeartion1");
	}
	
	/**
	 * 基本方法的实现
	 */
	public void doOperation2(){
		//像下面这样的调用不应当发生
		//doOperation3();
		System.out.println("ConcreteClass1 doOpeartion2");
	}
	
	/**
	 * 重载hook method的实现
	 */
	public void doHookMethod(){
		System.out.println("ConcreteClass1 override hook method");
	}

}
