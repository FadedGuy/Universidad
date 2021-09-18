#pragma config(Sensor, S1,     tactileAv,      sensorTouch)
#pragma config(Sensor, S2,     tactileAr,      sensorTouch)
#pragma config(Sensor, S3,     captLumi,       sensorLightActive)
#pragma config(Sensor, S4,     ultrason,       sensorSONAR)
#pragma config(Motor,  motorA,          mPince,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mDroit,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mGauche,       tmotorNXT, PIDControl, encoder)


task main()
{
	int col, col2;
	while(SensorValue(tactileAv) != 1){}
	col = SensorValue(captLumi);
	eraseDisplay();
	nxtDisplayStringAt(1,3, "Col 1 %d", col);
	wait1Msec(1000);
	while(SensorValue(tactileAv) != 1){}
	col2 = SensorValue(captLumi);
	nxtDisplayStringAt(1,10, "Col 2 %d", col2);
	nxtDisplayStringAt(1,19, "Seuil %d", abs(col-col2));
	wait1Msec(5000);

}
