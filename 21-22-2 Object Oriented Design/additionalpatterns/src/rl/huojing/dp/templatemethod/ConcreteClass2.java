package rl.huojing.dp.templatemethod;

public class ConcreteClass2 extends AbstractClass {

	@Override
	protected void doOperation1() {
		System.out.println("ConcreteClass2 doOpeartion1");
	}

	@Override
	protected void doOperation2() {
		System.out.println("ConcreteClass2 doOpeartion2");
	}

	/**
	 * ����hook method��ʵ��
	 */
	public void doHookMethod(){
		System.out.println("ConcreteClass2 override hook method");
	}
}
