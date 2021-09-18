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
	int vit = 30, nbLignes = 0, colqui = 0; //colqui 0=noir; 1=blanche

	motor[mDroit] = vit;
	motor[mGauche] = vit;
	ClearTimer(T1);
	while(time1[T1] <= temps*1000)
	{
		//if(SensorValue(captLumi) <= seuil){nbLignes=nbLignes+1;wait1Msec(500);}
		if(SensorValue(captLumi) <= seuil && colqui == 1){
			colqui = 0;
			nbLignes = nbLignes + 1;
		}
		else if(SensorValue(captLumi) > seuil && colqui == 0){
			colqui = 1;
		}
	}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	eraseDisplay();
	nxtDisplayStringAt(1,10, "Lignes: %d", nbLignes);
	wait1Msec(5000);
}
