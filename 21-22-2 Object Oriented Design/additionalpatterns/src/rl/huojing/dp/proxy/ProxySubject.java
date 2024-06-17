package rl.huojing.dp.proxy;

public class ProxySubject extends Subject {
	private RealSubject realSubject;

	@Override
	public void request() {
		preRequest();
		if(realSubject == null){
			realSubject = new RealSubject();
		}
		realSubject.request();
		postRequest();
	}

	private void preRequest(){
		System.out.println("do something first!");
	}
	
	private void postRequest(){
		System.out.println("do something after!");
	}
}
