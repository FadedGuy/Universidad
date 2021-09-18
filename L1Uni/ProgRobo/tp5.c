#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define dist 12
#define seuil 50

#define atras -1
#define adelante 1
#define der 1
#define izq 0
#define entrase 113
#define diamRoue 56

void avancePercute(int vit)
{
		motor[mDroit] = vit;
		motor[mGauche] = vit;
		while(SensorValue(tactileAv) != 1){}
		motor[mDroit] = 0;
		motor[mGauche] = 0;
}

void tourner(int dir, int angle, int vit)
{
		long deg = (2*(long)entrase*angle)/diamRoue; //Angle a degrees

		if(dir == der)
		{
			nMotorEncoder[mGauche] = 0;
			motor[mDroit] = vit*atras;
			motor[mGauche] = vit;
			while(nMotorEncoder[mGauche] <= deg){}
			motor[mDroit] = 0;
			motor[mGauche] = 0;
		}
		else
		{
			nMotorEncoder[mDroit] = 0;
			motor[mDroit] = vit;
			motor[mGauche] = vit*atras;
			while(nMotorEncoder[mDroit] <= deg){}
			motor[mDroit] = 0;
			motor[mGauche] = 0;
		}
}

void avancerLigneNoir(int vit, int sel, int temps)
{
	ClearTimer(T1);
	while(time1[T1] < temps*1000)
	{
		if(SensorValue(captLumi) <= sel)
		{
			ClearTimer(T1);
			motor[mGauche] = 0;
			motor[mDroit] = vit;
		}
		else
		{
			motor[mDroit] = 0;
			motor[mGauche] = vit;
		}
	}
	motor[mDroit] = 0;
	motor[mGauche] = vit*atras;
	wait1Msec(800);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
}

void avancerLigneNoirM2(int vit, int sel, int dis)
{
	while(SensorValue(ultrason) >= dis)
	{
		if(SensorValue(captLumi) <= sel)
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
	motor[mDroit] = 0;
	motor[mGauche] = 0;
}

void avanceSeuil(int vit, int sel)
{
	motor[mDroit] = vit;
	motor[mGauche] = vit;
	while(SensorValue(captLumi) >= sel){}
	motor[mDroit] = vit*2;
	motor[mGauche] = vit*2;
	wait1Msec(250); //Linea Negra Blanca usable; no implementado
	while(SensorValue(captLumi) >= sel){}
	wait1Msec(800);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
}

task main()
{
	int vit = 30;
	avancePercute(vit);
	motor[mDroit] = vit*-1;
	motor[mGauche] = vit*-1;
	wait1Msec(500);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	tourner(izq, 45, 20);

	motor[mDroit] = vit;
	motor[mGauche] = vit;
	wait1Msec(1000);
	motor[mDroit] = 0;
	motor[mGauche] = 0;

	//avancerLigneNoir(vit,seuil, 1);
	avancerLigneNoirM2(vit, seuil, dist);

	avancePercute(vit);
	motor[mDroit] = vit*-1;
	motor[mGauche] = vit*-1;
	wait1Msec(500);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	tourner(der, 45, 20);

	avancePercute(vit);
	tourner(der, 50, 20);


	avanceSeuil(vit, seuil);

}
