package rl.huojing.dp.templatemethod;

public class ConcreteClass1 extends AbstractClass{

   /**
    * ����������ʵ��
    */
	public void doOperation1(){
		System.out.println("ConcreteClass1 doOpeartion1");
	}
	
	/**
	 * ����������ʵ��
	 */
	public void doOperation2(){
		//�����������ĵ��ò�Ӧ������
		//doOperation3();
		System.out.println("ConcreteClass1 doOpeartion2");
	}
	
	/**
	 * ����hook method��ʵ��
	 */
	public void doHookMethod(){
		System.out.println("ConcreteClass1 override hook method");
	}

}
