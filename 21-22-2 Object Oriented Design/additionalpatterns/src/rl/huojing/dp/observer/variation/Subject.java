package rl.huojing.dp.observer.variation;

import java.util.Vector;
import java.util.Enumeration;

public abstract class Subject {
	private Vector<Observer> observers = new Vector<Observer>();
	
	public void attach(Observer observer){
		observers.addElement(observer);
	}
	
	public void detach(Observer observer){
		observers.removeElement(observer);
	}
	
	public void notifyObservers(){
		Enumeration enumeration = getObservers();
		while(enumeration.hasMoreElements()){
			((Observer)enumeration.nextElement()).update();
		}
	}
	
	public Enumeration getObservers(){
		return ((Vector<Observer>)observers.clone()).elements();
	}
	
}
