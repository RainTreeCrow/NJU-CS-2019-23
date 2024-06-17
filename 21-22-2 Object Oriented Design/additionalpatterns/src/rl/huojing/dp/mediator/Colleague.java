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
	 * 行为方法，由子类实现
	 */
	public abstract void action();
	
	/**
	 * 示意性的业务方法，调用此方法可以改变对象的内部状态
	 */
	public void change(){
		mediator.colleagueChanged(this);
	}
}
