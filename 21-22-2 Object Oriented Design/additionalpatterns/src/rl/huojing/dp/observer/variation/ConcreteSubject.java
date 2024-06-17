package rl.huojing.dp.observer.variation;

public class ConcreteSubject extends Subject {
	private String state;
	
	public void changeState(String state){
		this.state = state;
		this.notifyObservers();
	}
	
	public String getState(){
		return state;
	}
}
