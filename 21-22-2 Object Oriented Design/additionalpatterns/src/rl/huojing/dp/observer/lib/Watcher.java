package rl.huojing.dp.observer.lib;

import java.util.Observable;
import java.util.Observer;

public class Watcher implements Observer {

	public Watcher(Watched w){
		w.addObserver(this);
	}
	
	public void update(Observable obj, Object arg) {
		System.out.println("Data has been changed to "+((Watched)obj).retrieveData()+"");

	}

}
