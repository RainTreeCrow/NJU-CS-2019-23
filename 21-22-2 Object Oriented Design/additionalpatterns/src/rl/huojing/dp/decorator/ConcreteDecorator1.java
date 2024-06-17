package rl.huojing.dp.decorator;

import java.util.ArrayList;
import java.util.ListIterator;

public class ConcreteDecorator1 extends Decorator {

	//额外增加的功能被打包在这个List中
	private ArrayList<String> others = new ArrayList<String>(); 

	//在构造器中使用组合new方式,引入Work对象;
	public ConcreteDecorator1(Work work){
		super(work);
		others.add("挖坑");
		others.add("钉木板");
	}

	public void insert(){
		newMethod();
	} 

	//在新方法中,我们在insert之前增加其他方法,这里次序先后是用户灵活指定的 　　 
	public void newMethod(){
		otherMethod();
		work.insert();
	} 

	public void otherMethod(){
		ListIterator<String> listIterator = others.listIterator();
		while (listIterator.hasNext()){
			System.out.println((String)(listIterator.next())+" 正在进行");
		}
	}
}
