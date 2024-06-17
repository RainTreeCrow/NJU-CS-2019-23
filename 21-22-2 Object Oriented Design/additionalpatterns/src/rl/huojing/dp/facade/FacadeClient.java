package rl.huojing.dp.facade;

public class FacadeClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		SecurityFacade security = new SecurityFacade();
		System.out.println("ACTIVATING ALL EQUIPMENTS...");
		security.activate();
		System.out.println("DEACTIVATING ALL EQUIPMENTS...");
		security.deactivate();
	}

}
