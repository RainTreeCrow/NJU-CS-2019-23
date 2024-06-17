package rl.huojing.dp.decorator;

public abstract class Decorator implements Work {

	protected Work work;
	
	//�ڹ�������ʹ�����new��ʽ,����Work����;
	public Decorator(Work work){
		this.work=work;
	}

	public void insert(){
		work.insert();
	} 
	
}
