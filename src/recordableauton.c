#include "main.h"

void recordcode(){ // simple record auton code
	for(int t = 0; t < 1020; t++){
		controller(); update();
		auton[t].m1 = motor[1]; auton[t].m2 = motor[2]; auton[t].m3 = motor[3];	auton[t].m4 = motor[4]; auton[t].m5 =	motor[5];
		auton[t].m6 = motor[6];	auton[t].m7 = motor[7];	auton[t].m8 = motor[8];	auton[t].m9 = motor[9];	auton[t].m10 = motor[10];
		wait(10);}}
void reruncode(){ // totally not a stall code ;) hopefully they dont read this again // ignore that <- // just a rerun code to run what we recorded
	for(int i = 0; i < 1020; i++){
		motor[1] = auton[i].m1;	motor[2] = auton[i].m2;	motor[3] = auton[i].m3;	motor[4] = auton[i].m4;	motor[5] = auton[i].m5;
		motor[6] = auton[i].m6;	motor[7] = auton[i].m7;	motor[8] = auton[i].m8;	motor[9] = auton[i].m9;	motor[10] = auton[i].m10;
		update(); wait(10);}}
void savecode(){  // just a program to print out the values to a screen so we can copy paste it into our code
	printf("\nint motor1[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m1);}printf("};");wait(1000);
	printf("\nint motor2[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m2);}printf("};");wait(1000);
	printf("\nint motor3[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m3);}printf("};");wait(1000);
	printf("\nint motor4[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m4);}printf("};");wait(1000);
	printf("\nint motor5[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m5);}printf("};");wait(1000);
	printf("\nint motor6[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m6);}printf("};");wait(1000);
	printf("\nint motor7[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m7);}printf("};");wait(1000);
	printf("\nint motor8[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m8);}printf("};");wait(1000);
	printf("\nint motor9[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m9);}printf("};");wait(1000);
	printf("\nint motor10[buffer] = {");for(int n = 0; n < buffer; n++){printf("%d,", auton[n].m10);}printf("};");wait(1000);}
