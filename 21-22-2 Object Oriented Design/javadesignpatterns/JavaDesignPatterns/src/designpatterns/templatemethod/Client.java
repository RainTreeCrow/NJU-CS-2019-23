//designpatterns.templatemethod.Client.java
package designpatterns.templatemethod;

public class Client {
	public static void main(String args[]) {
		Account account;
		account = (Account) XMLUtil.getBean();
		account.handle("张无忌","123456");
	}
}