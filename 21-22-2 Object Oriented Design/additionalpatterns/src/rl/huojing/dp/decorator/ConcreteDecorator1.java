package rl.huojing.dp.decorator;

import java.util.ArrayList;
import java.util.ListIterator;

public class ConcreteDecorator1 extends Decorator {

	//�������ӵĹ��ܱ���������List��
	private ArrayList<String> others = new ArrayList<String>(); 

	//�ڹ�������ʹ�����new��ʽ,����Work����;
	public ConcreteDecorator1(Work work){
		super(work);
		others.add("�ڿ�");
		others.add("��ľ��");
	}

	public void insert(){
		newMethod();
	} 

	//���·�����,������insert֮ǰ������������,��������Ⱥ����û����ָ���� ���� 
	public void newMethod(){
		otherMethod();
		work.insert();
	} 

	public void otherMethod(){
		ListIterator<String> listIterator = others.listIterator();
		while (listIterator.hasNext()){
			System.out.println((String)(listIterator.next())+" ���ڽ���");
		}
	}
}
