package rl.huojing.dp.memento.blackbox;

public class Caretaker {
	private MementoIF memento;
	
	/**
	 * ����¼��ȡֵ����
	 * @return
	 */
	public MementoIF retrieveMemento(){
		return this.memento;
	}
	
	/**
	 * ����¼�ĸ�ֵ����
	 * Attention�������õĺ���ʵ�֣��޷��۸�memnto
	 * @param memento
	 */
	public void saveMemento(MementoIF memento){
		this.memento = memento;
	}
}
