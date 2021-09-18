#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define dist 20

task main()
{
	//Le robot avance et doit s’arrêter à une certaine distance d’un obstacle. La distance est une constante: dist
	nMotorEncoder[mDroit] = 0;
	motor[mDroit] = 30;
	motor[mGauche] = 30;
	while(SensorValue(ultrason) >= dist){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	eraseDisplay();
	int dg = nMotorEncoder[mDroit];
	nxtDisplayStringAt(1,15, "dg: %d ", dg);
	wait1Msec(3000);
}
