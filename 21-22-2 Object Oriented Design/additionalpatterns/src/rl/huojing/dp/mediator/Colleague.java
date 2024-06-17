package rl.huojing.dp.mediator;

public abstract class Colleague {
	private Mediator mediator;
	
	public Colleague(Mediator m){
		this.mediator = m;
	}
	
	public Mediator getMediator(){
		return mediator;
	}
	
	/**
	 * ��Ϊ������������ʵ��
	 */
	public abstract void action();
	
	/**
	 * ʾ���Ե�ҵ�񷽷������ô˷������Ըı������ڲ�״̬
	 */
	public void change(){
		mediator.colleagueChanged(this);
	}
}
