package rl.huojing.dp.prototype.deepclone;

public class Teacher implements Cloneable{
	 String name;
	 int age;
	 Teacher(String name,int age)
	 {
	  this.name = name;
	  this.age = age;
	 }
	 
	 public Object clone()
	 {
	  try{
	   return super.clone();
	  }catch(CloneNotSupportedException e)
	  {
	   throw new Error("This should never happen!"); 
	  }
	 }
	 
	 public String toString()
	 {
	  return name + "  " + age;
	 }

}
