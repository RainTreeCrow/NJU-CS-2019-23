package rl.huojing.dp.memento.blackbox;

public class Originator {
	private String state;
	
	public Originator(){}
	
	/**
	 * 返回一个新的备忘录对象,明显类型为MementoIF,真实类型为Memento
	 * @return
	 */
	public MementoIF createMemento(){
		return new Memento(this.state);
	}
	
	/**
	 * 将发起人恢复到备忘录对象记录的状态
	 * @param memento
	 */
	public void restoreMemento(MementoIF memento){
		Memento aMemento = (Memento)memento;
		this.setState(aMemento.getState());
	}
	
	public String getState(){
		return this.state;
	}
	
	public void setState(String state){
		this.state = state;
		System.out.println("State = "+state);
	}
	
	/**
	 * 内部成员类，备忘录
	 * 方法都是私有的，因此只有它自己和发起人类可以调用
	 *
	 */
	protected class Memento implements MementoIF{
		private String savedState;
		
		private Memento(String someState){
			savedState = someState;
		}
		
		private void setState(String someState){
			savedState = someState;
		}
		
		private String getState(){
			return savedState;
		}
	}
}
