package rl.huojing.dp.prototype.deepclone;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class TestCloneBySer {
	public static void main(String[] args) throws Exception
    {
        BMW mycar = new BMW();
        ByteArrayOutputStream memoryOutputStream = new ByteArrayOutputStream();
        ObjectOutputStream serializer = new ObjectOutputStream(memoryOutputStream);
        serializer.writeObject(mycar);
        serializer.flush();
        
        ByteArrayInputStream memoryInputStream = new ByteArrayInputStream(memoryOutputStream.toByteArray( ));
        ObjectInputStream deserializer = new ObjectInputStream(memoryInputStream);
        BMW mycopycar = (BMW)deserializer.readObject();

        System.out.println(mycar.hashCode());
        System.out.println(mycopycar.hashCode());
        System.out.println(mycar.equals(mycopycar));
        
        mycar.add(new String("NB"));
        mycopycar.add(new String("NBNB"));
        System.out.println(mycar.hashCode());
        System.out.println(mycopycar.hashCode());
        System.out.println(mycar.equals(mycopycar));
    }

}
