package rl.huojing.dp.memento.whitebox;

public class Caretaker {
	private Memento memento;
	
	/**
	 * ����¼��ȡֵ����
	 * @return
	 */
	public Memento retrieveMemento(){
		return this.memento;
	}
	
	/**
	 * ����¼�ĸ�ֵ����
	 * Attention�������õİ���ʵ�֣����Դ۸�memento
	 * @param memento
	 */
	public void saveMemento(Memento memento){
		this.memento = memento;
		memento.setState("Juggled");
	}
}
