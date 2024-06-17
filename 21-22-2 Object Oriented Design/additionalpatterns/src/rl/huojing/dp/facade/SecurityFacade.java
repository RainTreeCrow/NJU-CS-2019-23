package rl.huojing.dp.facade;

public class SecurityFacade {
	private Camera camera1,camera2;
	private Light light1,light2;
	private Sensor sensor;
	private Alarm alarm;
	
	public SecurityFacade(){
		camera1 = new Camera();
		camera2 = new Camera();
		light1 = new Light();
		light2 = new Light();
		sensor = new Sensor();
		alarm = new Alarm();
	}
	
	public void activate(){
		camera1.turnOn();
		camera2.turnOn();
		light1.turnOn();
		light2.turnOn();
		sensor.activate();
		alarm.activate();
	}
	
	public void deactivate(){
		camera1.turnOff();
		camera2.turnOff();
		light1.turnOff();
		light2.turnOff();
		sensor.deactivate();
		alarm.deactivate();
	}
}
