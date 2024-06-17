package rl.huojing.dp.state;

public class Context {
	
	private State currentState;
	
	public void request(){
		if(currentState!=null){
			currentState.handle();
		}
		else{
			System.out.println("current state is null");
		}
	}
	
	public void setState(State state){
		this.currentState = state;
	}
}
