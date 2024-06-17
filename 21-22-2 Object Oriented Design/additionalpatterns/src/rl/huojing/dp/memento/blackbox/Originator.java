package rl.huojing.dp.memento.blackbox;

public class Originator {
	private String state;
	
	public Originator(){}
	
	/**
	 * ����һ���µı���¼����,��������ΪMementoIF,��ʵ����ΪMemento
	 * @return
	 */
	public MementoIF createMemento(){
		return new Memento(this.state);
	}
	
	/**
	 * �������˻ָ�������¼�����¼��״̬
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
	 * �ڲ���Ա�࣬����¼
	 * ��������˽�еģ����ֻ�����Լ��ͷ���������Ե���
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
