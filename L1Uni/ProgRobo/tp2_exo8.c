#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

void ouvrirPince(int deg, int puissance)
{
	nMotorEncoder[mPince] = 0;
	motor[mPince] = puissance;
	while(nMotorEncoder[mPince] < deg){}
	motor[mPince] = 0;
}

void fermerPince(int deg, int puissance)
{
	nMotorEncoder[mPince] = 0;
	motor[mPince] = puissance;
	while(nMotorEncoder[mPince] > deg*-1){}
	motor[mPince] = 0;
}

task main()
{
	ouvrirPince(30,30);
	motor[mDroit] = 30;
	motor[mGauche] = 30;
	while(SensorValue(captLumi) >= 50){}
	wait1Msec(500);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	fermerPince(30,-30);
}
