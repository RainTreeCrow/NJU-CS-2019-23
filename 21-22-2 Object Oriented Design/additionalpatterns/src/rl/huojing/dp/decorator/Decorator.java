package rl.huojing.dp.decorator;

public abstract class Decorator implements Work {

	protected Work work;
	
	//在构造器中使用组合new方式,引入Work对象;
	public Decorator(Work work){
		this.work=work;
	}

	public void insert(){
		work.insert();
	} 
	
}
