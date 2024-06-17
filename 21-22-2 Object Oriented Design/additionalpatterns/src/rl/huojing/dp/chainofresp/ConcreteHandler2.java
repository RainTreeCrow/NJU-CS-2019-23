package rl.huojing.dp.chainofresp;

public class ConcreteHandler2 extends Handler {

	@Override
	public void handleRequest() {
		if(getSuccessor()!=null){
			System.out.println("The request is passed to "+getSuccessor());
			getSuccessor().handleRequest();
		}
		else{
			System.out.println("The request is handled here by ConcreteHandler2");
		}
	}

}
