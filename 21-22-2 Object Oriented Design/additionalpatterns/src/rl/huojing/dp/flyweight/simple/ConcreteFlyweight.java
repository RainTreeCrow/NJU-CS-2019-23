package rl.huojing.dp.flyweight.simple;

public class ConcreteFlyweight extends Flyweight {
	
	private Character intrinsicState = null;
	/*
	 * �����ӣ��ڲ�״̬��Ϊ��������
	 */
	public ConcreteFlyweight(Character state){
		this.intrinsicState = state;
	}

	/*
	 * �ⲿ״̬��Ϊ�������뷽���У��ı䷽������Ϊ�����ǲ��ı������ڲ�״̬
	 */
	public void operation(String state) {
		System.out.println("Intrinsic State = "+intrinsicState + 
				", Extrinsic State = "+state);
	}

}
