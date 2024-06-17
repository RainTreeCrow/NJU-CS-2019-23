package rl.huojing.dp.prototype.deepclone;

import java.util.HashMap;

public class Student implements Cloneable {
	 HashMap<Integer, String> courses = new HashMap<Integer, String>();
	 Student(){} 
	 
	 @SuppressWarnings("unchecked")
	public Object clone()
	 {
	  try{
	   Student stu = (Student)super.clone();
	   HashMap<Integer, String> clone = (HashMap<Integer, String>)courses.clone();
	   stu.courses = clone;
	   return stu;
	  }catch(CloneNotSupportedException e)
	  {
	   throw new Error("This should never happen!"); 
	  }
	 }

}
