#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define seuil 50

task main()
{
	//Le robot avance et doit s’arrêter dès qu’il rencontre une ligne noire. La valeur du seuilde détection du capteur photosensible est une constante: seuil
	motor[mDroit] = 30;
	motor[mGauche] = 30;
	while(SensorValue(captLumi) >= seuil){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;

}
