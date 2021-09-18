#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)

#define atras -1
#define adelante 1
#define der 1
#define izq 0
#define entrase 113
#define diamRoue 56

#define vit 30
#define seuilNoire 50
#define seuilBleu 90
#define degPince 30

void avanceSeuil(int vel, int sel)
{
	motor[mDroit] = vel;
	motor[mGauche] = vel;
	while(SensorValue(captLumi) >= sel){}
	wait1Msec(400);
	motor[mDroit] = 0;
	motor[mGauche] = 0;
}

float avanceDist(int vel, int dist)
{
	float valD = PI *  diamRoue;
	valD = (dist*10)/valD;
	valD = valD*360;
	nMotorEncoder[mDroit] = 0;
	motor[mDroit] = vel;
	motor[mGauche] = vel;
	while(nMotorEncoder[mDroit] <= valD){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	return nMotorEncoder[mDroit];
}

void tourner(int dir, int angle, int vel)
{
		long deg = (2*(long)entrase*angle)/diamRoue; //Angle a degrees

		if(dir == der)
		{
			nMotorEncoder[mGauche] = 0;
			motor[mDroit] = vel*atras;
			motor[mGauche] = vel;
			while(nMotorEncoder[mGauche] <= deg){}
			motor[mDroit] = 0;
			motor[mGauche] = 0;
		}
		else
		{
			nMotorEncoder[mDroit] = 0;
			motor[mDroit] = vel;
			motor[mGauche] = vel*atras;
			while(nMotorEncoder[mDroit] <= deg){}
			motor[mDroit] = 0;
			motor[mGauche] = 0;
		}
}

void chercheLigne(int vel, int ligneC, int seuil)
{
		int nbLigne = 0, colqui = 1; //0 Noire, 1 Blanche

		motor[mDroit] = vel;
		motor[mGauche] = vel;

		while(nbLigne < ligneC)
		{
			if(SensorValue(captLumi) <= seuil && colqui == 1){
				colqui = 0;
				nbLigne = nbLigne + 1;
			}
			else if(SensorValue(captLumi) > seuil && colqui == 0){
				colqui = 1;
			}
		}

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

float chercheBalle(int vel, int degPin)
{
	ouvrirPince(degPin,vel);

	nMotorEncoder[mDroit] = 0;
	motor[mDroit] = vel;
	motor[mGauche] = vel;
	while(SensorValue(tactileAv) != 1){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;
	fermerPince(degPin, vel*-1);
	return nMotorEncoder[mDroit];
}

task main()
{
	int ligneBalle = 2, quelZ = 0;
	float distRec = 0, distLim = 3683.3;

	distRec += avanceSeuil(vit, seuilNoire);

	//Indiquer ligne du balle

	avanceDist(vit, 35);
	tourner(izq, 45, vit);

	chercheLigne(vit, ligneBalle, seuilNoire);

	tourner(der, 45, vit);

	//OuvrirPince et chercher balle

	distRec += chercheBalle(15, degPince);

	if(distRec <= 2000)
	{quelZ = 1;}
	else{ quelZ = -1;}

	nMotorEncoder[mDroit] = 0;
	motor[mDroit] = vel;
	motor[mGauche] = vel;
	while(nMotorEncoder[mDroit]+distRec <= distLim){}
	motor[mDroit] = 0;
	motor[mGauche] = 0;

	//Aller a Z
	if(quelZ == 1)
	{
		tourner(der, 45, vit);
	}
	else
	{
		tourner(izq, 45, vit);
	}

	avanceSeuil(vit, seuilBleu);
}
