package rl.huojing.dp.prototype.prototypemanager;

public class ConcretePrototype implements Prototype {

	@SuppressWarnings("finally")
	public Object clone(){
		Prototype temp = null;
		try{
			temp = (Prototype)super.clone();
			return temp;

		}catch(CloneNotSupportedException e){
			System.out.println("Clone failed");
		}
		finally{
			return temp;
		}
	}

}
