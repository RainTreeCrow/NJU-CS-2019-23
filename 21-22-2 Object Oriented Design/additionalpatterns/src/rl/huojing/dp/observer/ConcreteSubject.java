package rl.huojing.dp.observer;

import java.util.Enumeration;
import java.util.Vector;

public class ConcreteSubject implements Subject {

	private Vector<Observer> observers = new java.util.Vector<Observer>();
	private String state;
	
	public void attach(Observer observer) {
		observers.addElement(observer);
	}

	public void detach(Observer observer) {
		observers.removeElement(observer);
	}

	public void notifyObservers() {
		Enumeration<Observer> enumeration = observers.elements(); 
		while(enumeration.hasMoreElements()){
			((Observer)enumeration.nextElement()).update(state);
		}
	}
	
	public void changeState(String newState){
		state = newState;
		this.notifyObservers();
	}
	
	public String getState(){
		return state;
	}

}
