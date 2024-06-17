package rl.huojing.dp.memento.whitebox;

public class Originator {
	private String state;
	
	/**
	 * 返回一个新的备忘录对象
	 * @return
	 */
	public Memento createMemento(){
		return new Memento(state);
	}
	
	/**
	 * 将发起人恢复到备忘录对象记载的状态
	 * @param mementor
	 */
	public void restoreMemento(Memento mementor){
		this.state = mementor.getState();
	}
	
	public String getState(){
		return this.state;
	}
	
	public void setState(String state){
		this.state = state;
		System.out.println("State = "+this.state);
	}
}
