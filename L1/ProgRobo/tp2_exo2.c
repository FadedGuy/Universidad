#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

task main()
{
	//Le robot recule et doit s’arrêter lorsqu’il percute un obstacle
	motor[mDroit] = -30;
	motor[mGauche] = -30;
	while(SensorValue(tactileAr) != 1){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;

}
