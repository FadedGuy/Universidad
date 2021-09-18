#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define temps 5
#define seuil 50

task main()
{
	int vit = 30;

	ClearTimer(T1);
	while(time1[T1] < temps*1000)
	{
		if(SensorValue(captLumi) <= seuil)
		{
			motor[mGauche] = 0;
			motor[mDroit] = vit;
		}
		else
		{
			motor[mDroit] = 0;
			motor[mGauche] = vit;
		}
	}
}
