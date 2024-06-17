package rl.huojing.dp.decorator;

public class ConcreteDecorator2 extends Decorator {
	
	public ConcreteDecorator2(Work work){
		super(work);
	}
	
	public void insert(){
		System.out.println("刷漆 正在进行");
		work.insert();
	}

}
