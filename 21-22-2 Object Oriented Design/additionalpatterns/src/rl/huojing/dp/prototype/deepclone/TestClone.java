package rl.huojing.dp.prototype.deepclone;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

public class TestClone {
	public static void main(String[] args)
	 {
	  Teacher t = new Teacher("Mary",22);
	  Teacher m = (Teacher)t.clone();
	  System.out.println(m);
	  
	  Student stu = new Student();
	  stu.courses.put(new Integer(1),"Math");
	  Student deepcloneSTU = (Student)stu.clone();
	  deepcloneSTU.courses.put(new Integer(100),"Java");
	  System.out.println("stu's courses");
	  disp(stu.courses);
	  System.out.println("deepclones's courses");
	  disp(deepcloneSTU.courses);
	  System.out.println("stu's courses");
	  disp(stu.courses);
	 }
	 
	 static void disp(HashMap<Integer, String> h)
	 {
	  Set<Integer> keySet = h.keySet();
	  Iterator<Integer> it = keySet.iterator();
	  while(it.hasNext())
	  {
	   System.out.println(h.get(it.next()));
	  }
	 }

}
