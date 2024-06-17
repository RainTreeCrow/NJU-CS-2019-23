package rl.huojing.dp.memento.blackbox;

public class Caretaker {
	private MementoIF memento;
	
	/**
	 * 备忘录的取值方法
	 * @return
	 */
	public MementoIF retrieveMemento(){
		return this.memento;
	}
	
	/**
	 * 备忘录的赋值方法
	 * Attention：由于用的黑箱实现，无法篡改memnto
	 * @param memento
	 */
	public void saveMemento(MementoIF memento){
		this.memento = memento;
	}
}
