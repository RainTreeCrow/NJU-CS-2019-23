package rl.huojing.dp.templatemethod;

public abstract class AbstractClass {
	
	/**
	 * 模板方法的声明和实现
	 */
	public final void templateMethod(){
		doOperation1();
		doOperation2();
		doOperation3();
		doHookMethod();
	}
	
	/**
	 * 基本方法的声明（由子类实现）
	 */
	protected abstract void doOperation1();
	
	/**
	 * 基本方法的声明（由子类实现）
	 */
	protected abstract void doOperation2();
	
	/**
	 * 基本方法（已经实现）
	 */
	private final void doOperation3(){
		System.out.println("doOpeartion3");
	}
	
	/**
	 * hook method，提供默认实现
	 */
	protected void doHookMethod(){} 
	
}
