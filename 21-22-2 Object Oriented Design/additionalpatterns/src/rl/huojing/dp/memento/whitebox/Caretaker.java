package rl.huojing.dp.memento.whitebox;

public class Caretaker {
	private Memento memento;
	
	/**
	 * 备忘录的取值方法
	 * @return
	 */
	public Memento retrieveMemento(){
		return this.memento;
	}
	
	/**
	 * 备忘录的赋值方法
	 * Attention：由于用的白箱实现，可以篡改memento
	 * @param memento
	 */
	public void saveMemento(Memento memento){
		this.memento = memento;
		memento.setState("Juggled");
	}
}
