package rl.huojing.dp.decorator;

public class ConcreteDecorator2 extends Decorator {
	
	public ConcreteDecorator2(Work work){
		super(work);
	}
	
	public void insert(){
		System.out.println("ˢ�� ���ڽ���");
		work.insert();
	}

}
