#include "main.h"

const int ground = 70, armthing[10] = {70,70,200,500,630,810,7,8,9,10};  // for 0 then make it either 49 or 75
const int cbposition[5] = {1310};
const int cbendpos = 100, cbstartpos = 0, cb_pwm = 127, arm_const = 127;
// leftback 1
// leftmiddle 2
// bigarm 8
// mogodp 4
// smallarm 7
// rightmiddle 9
// rightback 10
int FrontLeft = 10, FrontRight = 3, FrontMidLeft = 1, FrontMidRight = 2, BackMidLeft = 4, BackMidRight = 7,
BackLeft = 5, BackRight = 6, Lockr = 8, lockl = 9;

int inver[]= {-999, -1, 1, 1, 1, 0, 0,-1,-1,-1,-1};

const int stop = 0, maxmenus = 25, bound = 100;
int stack = 0, menu = 0, lastV = 0, armspeed = 10, armheight = 70, cbhieght = 1000, cbspeed = 10, selectedauton = 0;
bool overrided = false;
                      //M1 M2 M3 M4 M5 M6 M7 M8 M9 M10
//struct motor{char m1, m2, m3, m4, m5, m6, m7, m8, m9, m10;}motor; // structure to hold the motor pwm because its smaller
struct last{int arm, override, su, sd, co, cc, mo, mc; int lj;}last; // a structure for the last values
void lcd(const char *line1, const char *line2)
{
	lcdPrint(uart1, 1, line1);
	lcdPrint(uart1, 2, line2);
}
void lcdmenu(){
	int runtime = millis();
	int currV = joystickGetAnalog(1, 4);
	if(bound <= abs(currV) && bound > abs(lastV)){menu = (menu + maxmenus + currV/abs(currV)) % maxmenus;}
	lastV = currV;
	switch(menu){
		case  0: // Battery Level
    lcdPrint(uart1, 1, "   Main Bat %d", powerLevelMain());
    lcdPrint(uart1, 2, "Back-up Bat %d", powerLevelMain());
    break;
    case  1: // Auton Viewer, needs number and name
    lcdPrint(uart1, 1, "Running Auton %d", selectedauton);
    lcdPrint(uart1, 2, "Name of Auton");
    break;
    case  2: // Phone Number Meme
    lcdPrint(uart1, 1, "   r8 my code   ");
    lcdPrint(uart1, 2, "  954-849-1442  ");
    break;
    case  3: // Bot Timer, will use millis if the test on case 17 works
    lcdPrint(uart1, 1, "The bot has been");
    lcdPrint(uart1, 2, "running:  %dm%ds", runtime/60000, runtime%60000/1000);
    break;
    case  4: // Credits
    lcdPrint(uart1, 1, "Steve Coded This");
    lcdPrint(uart1, 2, "Kevin Coded This");
    break;
	  case  5    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "Motor Vals");break;
    case  6    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "S.B.S. Auton");break;
    case  7    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "something");break;
    case  8    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "something");break;
	  case  9: // Map 1
    lcdPrint(uart1, 1, "Ba|PA|P#|TS|Cre ");
    lcdPrint(uart1, 2, "M1|SA|??|??|Ma1 ");
    break;
	  case 10    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "Motor Vals 2");break;
  	case 11    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "RecAut Viewer");break;
    case 12    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "PID Viewer");break;
    case 13    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "something");break;
    case 14: // Map 2
    lcdPrint(uart1, 1, "M2|RA|PD|??|Ma2 ");
    lcdPrint(uart1, 2, "J1|S1|S3|??|Ma3 ");
    break;
    case 15: // Joystick 1, needs formatting for analog input
    lcdPrint(uart1, 1, "1%d 2%d5U%dD%d", joystickGetAnalog(1, 1), joystickGetAnalog(1, 2), joystickGetDigital(1,5,JOY_UP), joystickGetDigital(1,5,JOY_DOWN));
    lcdPrint(uart1, 2, "3%d 4%d6U%dD%d", joystickGetAnalog(1, 3), joystickGetAnalog(1, 4), joystickGetDigital(1,6,JOY_UP), joystickGetDigital(1,6,JOY_DOWN));
    break;
    case 16: // Sensors 1
    //lcdPrint(uart1, 1, "leftdenc %d", encoderGet(leftD));
    //lcdPrint(uart1, 2, "rightdenc %d", encoderGet(rightD));
    break;
	    // these don't currently fit anywhere, need to rewrite for space efficiency and move them to appropriate spaces
    //case 17  :lcdPrint(uart1, 1, "sarmenc %d", encoderGet(smallarmenc));lcdPrint(uart1, 2, "run time ");break;
    case 18  :lcdPrint(uart1, 1, "Stack %d", stack); lcdPrint(uart1, 2, "Steve Didn't Code this");break;
    case 19: // Map 3
    lcdPrint(uart1, 1, "J2|S2|S4|??|Ma3 ");
    lcdPrint(uart1, 2, "??|??|??|??|??? ");
    break;
    case 20: // Joystick 2, missing accelerometer code & it wont fit on just one screen but i dont feel like making another :)
    lcdPrint(uart1, 1, "7U%dD%dL%dR%d Ax%d", joystickGetDigital(1,7,JOY_UP), joystickGetDigital(1,7,JOY_DOWN), joystickGetDigital(1,7,JOY_LEFT), joystickGetDigital(1,7,JOY_RIGHT), joystickGetAnalog(1, ACCEL_X));
    lcdPrint(uart1, 2, "8U%dD%dL%dR%d Ay%d", joystickGetDigital(1,8,JOY_UP), joystickGetDigital(1,8,JOY_DOWN), joystickGetDigital(1,8,JOY_LEFT), joystickGetDigital(1,8,JOY_RIGHT), joystickGetAnalog(1, ACCEL_Y));
    break;
    case 21    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "Sensr Vals 2");break;
    case 22    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "Sensr Vals 4");break;
    case 23    :lcdPrint(uart1, 1, "Placeholder for ");lcdPrint(uart1, 2, "something");break;
		case 24    :lcd("heyyyyyy","d000d"); break; // testing a lcd function to make this stuff smaller
//		case 25    :lcdPrint(uart1, 1, "");lcdPrint(uart1, 2, "something");break;
		default:
    lcdPrint(uart1, 1,"      Error     ");
    lcdPrint(uart1, 2, "    No Screen   ");
    break;
  }
}
void drive(int left, int right) // drive func
{
	motor[FrontLeft] = left * inver[FrontLeft];
	motor[BackMidLeft] = left * inver[BackMidLeft];
	motor[BackLeft] = left * inver[BackLeft];
	motor[FrontMidLeft] = left * inver[FrontMidLeft];

	motor[FrontRight] = right * inver[FrontRight];
	motor[BackMidRight] = right * inver[BackMidRight];
	motor[BackRight] = right * inver[BackRight];
	motor[FrontMidRight] = right * inver[FrontMidRight];
}

void lockingthing(int pwm){motor[lockl] = pwm; motor[Lockr] = pwm;} // simple arm func

void halt(bool broke)
{
	if(broke)
	{
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
	}
	else if(!broke)
	{
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
	}
}

void update(){ // updates the motors and hopefully the digital ports soon
	motorSet(1, motor[1]); motorSet(2, motor[2]); motorSet(3, motor[3]); motorSet(4, motor[4]); motorSet(5, motor[5]);    /*Current error with my digital ports not working in the update*/
	motorSet(6, motor[6]); motorSet(7, motor[7]); motorSet(8, motor[8]); motorSet(9, motor[9]); motorSet(10, motor[10]);
	delay(20);}
int previous;

void controller(){ // controller function for making it easier for recordable auton
	int LeftJoyStick = joystickGetAnalog(1, 2), RightJoyStick = joystickGetAnalog(1, 3);
	bool Lock = joystickGetDigital(1, 5, JOY_UP), Unlock = joystickGetDigital(1, 5, JOY_DOWN);
	bool Break = joystickGetDigital(1, 6, JOY_UP), Unbreak = joystickGetDigital(1, 6, JOY_DOWN);
	drive(LeftJoyStick, RightJoyStick);
	if(Break){halt(true);} else if(Unbreak){halt(false);}
	lockingthing(127 * (Lock - Unlock));
delay(20);}
void operatorControl(){
  TaskHandle LCDMENU = taskRunLoop(lcdmenu, 12);
	TaskHandle UPDATE = taskRunLoop(update, 10);
	TaskHandle CONTROLLER = taskRunLoop(controller, 14);
	taskPrioritySet(LCDMENU, 1);
	taskPrioritySet(CONTROLLER, 2);
	taskPrioritySet(UPDATE, 3);
	while (1){
		bool record = joystickGetDigital(2, 7, JOY_UP), rerun = joystickGetDigital(2, 7, JOY_DOWN), save = joystickGetDigital(2, 7, JOY_LEFT);
		if(record){taskSuspend(CONTROLLER);recordcode();taskResume(CONTROLLER);}
		else if(rerun){taskSuspend(CONTROLLER);reruncode();taskResume(CONTROLLER);}
		else if(save){taskSuspend(CONTROLLER);savecode();taskResume(CONTROLLER);}
		delay(10);}
	taskDelete(CONTROLLER);
	taskDelete(UPDATE);
	taskDelete(LCDMENU);}
/*Tetris:d=4,o=5,b=160:d6,32p,c.6,32p,8a,8c6,8a#,16a,16g,f,c,8a,8c6,8g,8a,f,c,d,8d,8e,8g,8f,8e,8d,c,c,c*/ // tetris theme song for if we want any sound on a speaker because pros doesnt have  wav support
/* USSR_National_Anthem:d=4,o=5,b=250:f6, 2a#6, f.6, 8g6, 2a6, d6, d6, 2g6, f.6, 8d#6, 2f6, a#., 8a#, 2c6, c.6, 8d6, 2d#6, d#6, f6, 2g6, a.6, 8a#6, 2c.6, f6, 2d6, c.6, 8a#6, 2c6, a6, f6, 2a#6, a.6, 8g6, 2a6, d6, d6, 2g6, f.6, 8d#6, 2f6, a#., 8a#, 2a#6, a.6, 8g6, 1f6, 1d6, c6, a#6, a6, a#6, 2c.6, f6, 2f.6, 1a#6, a6, g6, f6, g6, 2a.6, d6, 2d6"*/
