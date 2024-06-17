package rl.huojing.dp.memento.whitebox;

public class Originator {
	private String state;
	
	/**
	 * ����һ���µı���¼����
	 * @return
	 */
	public Memento createMemento(){
		return new Memento(state);
	}
	
	/**
	 * �������˻ָ�������¼������ص�״̬
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
