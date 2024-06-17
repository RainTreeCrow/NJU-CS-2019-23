package rl.huojing.dp.templatemethod;

public abstract class AbstractClass {
	
	/**
	 * ģ�巽����������ʵ��
	 */
	public final void templateMethod(){
		doOperation1();
		doOperation2();
		doOperation3();
		doHookMethod();
	}
	
	/**
	 * ����������������������ʵ�֣�
	 */
	protected abstract void doOperation1();
	
	/**
	 * ����������������������ʵ�֣�
	 */
	protected abstract void doOperation2();
	
	/**
	 * �����������Ѿ�ʵ�֣�
	 */
	private final void doOperation3(){
		System.out.println("doOpeartion3");
	}
	
	/**
	 * hook method���ṩĬ��ʵ��
	 */
	protected void doHookMethod(){} 
	
}
