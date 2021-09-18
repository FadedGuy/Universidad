#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define temps 7
#define angleRot 90
#define entrase 113
#define diamRoue 56

task main()
{
	int vit = 30;
	long deg = (2*(long)entrase*angleRot)/diamRoue;

	ClearTimer(T1);
	motor[mDroit] = vit;
	motor[mGauche] = vit;
	while((int)time1[T1]/1000 <= temps){}
	nMotorEncoder[mDroit] = 0;
	motor[mGauche] = 0;
	while(nMotorEncoder[mDroit] <= deg){}
	motor[mDroit] = 0;
}
