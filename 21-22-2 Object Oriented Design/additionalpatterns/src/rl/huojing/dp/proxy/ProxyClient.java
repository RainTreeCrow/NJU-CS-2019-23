package rl.huojing.dp.proxy;

public class ProxyClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Subject subject = new ProxySubject();
		subject.request();
	}

}
