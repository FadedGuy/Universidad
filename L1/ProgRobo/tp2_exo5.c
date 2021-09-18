#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define nbRot1 2
#define nbRot2 1

task main()
{
	//Le robot avance durant un nombre de rotations nbRot1, puis recule durant nbRot 2 rotations. Les nombres de rotations nbRot1 et nbRot2sont des constantes.
	nMotorEncoder[mDroit] = 0;
	motor[mDroit] = 30;
	motor[mGauche] = 30;
	while(nMotorEncoder[mDroit] <= 360*nbRot1){}
	nMotorEncoder[mDroit] = 0;
	motor[mDroit] = -30;
	motor[mGauche] = -30;
	while(nMotorEncoder[mDroit] >= -360*nbRot2){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
}
