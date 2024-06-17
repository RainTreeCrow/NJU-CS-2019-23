package rl.huojing.dp.flyweight.simple;

public class ConcreteFlyweight extends Flyweight {
	
	private Character intrinsicState = null;
	/*
	 * 构造子，内部状态作为参量传入
	 */
	public ConcreteFlyweight(Character state){
		this.intrinsicState = state;
	}

	/*
	 * 外部状态作为参量传入方法中，改变方法的行为，但是不改变对象的内部状态
	 */
	public void operation(String state) {
		System.out.println("Intrinsic State = "+intrinsicState + 
				", Extrinsic State = "+state);
	}

}
