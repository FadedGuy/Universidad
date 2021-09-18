#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

//sens ; adelante 1, atras -1. 				dir ; izq 0, der 1

#define adelante 1
#define atras -1
#define izq 0
#define der 1
#define entrase 113
#define diamRoue 56

#define temps 7
#define angleRot 90

#define seuil 50

void tournerUneRoue(int dir, int sens, int angle, int vit)
{
	long deg = (2*(long)entrase*angle)/diamRoue; //Angle a degrees

	if((dir == izq && sens == adelante) || (dir == der && sens == atras))
	{
		nMotorEncoder[mDroit] = 0;
		motor[mDroit] = vit*sens;
		motor[mGauche] = 0;
		while(nMotorEncoder[mDroit]*sens <= deg){}
		motor[mDroit] = 0;
	}
	else
	{
		nMotorEncoder[mGauche] = 0;
		motor[mDroit] = 0;
		motor[mGauche] = vit*sens;
		while(nMotorEncoder[mGauche]*sens <= deg){}
		motor[mGauche] = 0;
	}
}

void tournerDeuxRoue(int dir, int angle, int vit)
{
	long deg = ((long)entrase*angle)/diamRoue; //Angle a degrees

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

void avancerDistVit(int dist, int vit)
{
		float val = PI *  diamRoue;
		val = (dist*10)/val;
		val = val*360;
		nMotorEncoder[mDroit] = 0;
		motor[mDroit] = vit;
		motor[mGauche] = vit;
		while(nMotorEncoder[mDroit] <= val){}
		motor[mDroit] = 0;
		motor[mGauche] = 0;
}

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
	int ret;

	while(SensorValue(ultrason) >= 20){}

	ouvrirPince(30,30);
	nMotorEncoder(mDroit) = 0;
	motor[mDroit] = 30;
	motor[mGauche] = 30;
	while(SensorValue(tactileAv) != 1){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	fermerPince(30,-30);
	wait1Msec(1000);

	ret = nMotorEncoder(mDroit);

	tournerDeuxRoue(der, 180,15);
	nMotorEncoder(mDroit) = 0;
	motor[mDroit] = 30;
	motor[mGauche] = 30;
	while(nMotorEncoder(mDroit) <= ret){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
}
/*
	CODE EXO 1
	int vit = 30;
	motor[mDroit] = vit;
	motor[mGauche] = vit;
	ClearTimer(T1);
	//atendre 5s
	while(time1[T1] < 7*1000){}
	//wait1Msec(temps*1000);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	tournerUneRoue(izq, adelante, angleRot, vit);

	CODE EXO 2
	for(int i = 0; i<=4; i++)
	{
		avancerDistVit(50, 30);
		tournerDeuxRoue(der, 85, 20);
	}

	CODE EXO 3
	int vit = 30;

	motor[mDroit] = vit;
	motor[mGauche] = vit;
	while(SensorValue(captLumi) >= seuil){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;

	PlaySound(soundBeepBeep);
	tournerUneRoue(izq, atras, 85, 15);

	motor[mDroit] = vit*-1;
	motor[mGauche] = vit*-1;
	while(SensorValue(captLumi) >= seuil){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
*/
