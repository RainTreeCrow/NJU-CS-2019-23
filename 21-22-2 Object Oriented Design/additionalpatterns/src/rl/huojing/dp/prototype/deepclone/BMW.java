package rl.huojing.dp.prototype.deepclone;

import java.io.Serializable;
import java.util.ArrayList;

public class BMW implements Serializable{
	 /**
	 * 
	 */
	private static final long serialVersionUID = 6027338246212868325L;
	private int wheels;
	  private String model;
	  private ArrayList<Object> forTest;
	  
	  BMW()
	  {
	      wheels = 4;
	      model = "530i";
	      forTest = new ArrayList<Object>();
	  }
	  
	  public void add(Object o)
	  {
	      forTest.add(o);
	  }
	  
	  public String toString()
	  {
	      return "WHEEL:" + wheels + "MODEL:" + model + forTest.toString();    
	  }
	  
	  public int hashCode()
	  {
	      return wheels + model.hashCode() + forTest.hashCode();    
	  }
	  
	  public boolean equals(Object o)
	  {
	      if(o == this)
	          return true;
	      if(o == null)
	          return false;
	      if(!(o instanceof BMW))
	        return false;
	      BMW bmw = (BMW)o;
	      if(bmw.wheels == wheels&&bmw.model.equals(model)&&bmw.forTest.equals(forTest))
	          return true;
	      else return false;
	  }  

}
