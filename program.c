#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  claw,           sensorDigitalOut)
#pragma config(Sensor, dgtl2,  isStarted,      sensorTouch)
#pragma config(Sensor, I2C_1,  rightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  leftLiftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  rightLiftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_5,  swingEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftfront,     tmotorVex393_HBridge, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port2,           leftback,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           lefttoplift,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftbottomlift, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port5,           rightintake,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_5)
#pragma config(Motor,  port6,           swinger,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           righttoplift,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightbottomlift, tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port9,           rightback,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightfront,    tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

int count = 0;

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	if (SensorValue[isStarted] == 0) {  //auto check - IMPORTANT FOR DISCONNECTIONS
		while(nLCDButtons != centerButton)
		{
			//Switch case that allows the user to choose from 4 different options
			switch(count){
			case 0:
				//Display first choice
				displayLCDCenteredString(0, "Blue Skyrise");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count = 3;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count++;
				}
				break;
			case 1:
				//Display second choice
				displayLCDCenteredString(0, "nothg");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count--;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count++;
				}
				break;
			case 2:
				//Display third choice
				displayLCDCenteredString(0, "Blue Cube");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count--;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count++;
				}
				break;
			case 3:
				//Display fourth choice
				displayLCDCenteredString(0, "Red Cube");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count--;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count = 0;
				}
				break;
			default:
				count = 0;
				break;
			}
		}
	}  //corresponds for auto check
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

void skyrisePickup(int offset, int speed = 127, int skyriseHeight = 392) {
	int lEncoder = -SensorValue[leftLiftEncoder];
	int rEncoder = SensorValue[rightLiftEncoder];
	if (lEncoder < skyriseHeight - offset) {
		while (lEncoder < skyriseHeight - offset && rEncoder < skyriseHeight - offset) {
			if (lEncoder < skyriseHeight - offset) {
				motor[lefttoplift] = speed;
				motor[leftbottomlift] = speed;
			}
			if (rEncoder < skyriseHeight - offset) {
				motor[righttoplift] = speed;
				motor[rightbottomlift] = speed;
			}
			lEncoder = -SensorValue[leftLiftEncoder];
			rEncoder = SensorValue[rightLiftEncoder];
		}
		} else if (lEncoder > skyriseHeight + offset) {
		while (lEncoder > skyriseHeight + offset && rEncoder > skyriseHeight + offset) {
			if (lEncoder > skyriseHeight + offset) {
				motor[lefttoplift] = -speed;
				motor[leftbottomlift] = -speed;
			}
			if (rEncoder > skyriseHeight + offset) {
				motor[righttoplift] = -speed;
				motor[rightbottomlift] = -speed;
			}
			lEncoder = -SensorValue[leftLiftEncoder];
			rEncoder = SensorValue[rightLiftEncoder];
		}
	}
	motor[righttoplift] = 0;
	motor[rightbottomlift] = 0;
	motor[lefttoplift] = 0;
	motor[leftbottomlift] = 0;
}

void turnRight(int offset, float degrees = 90.00, int speed = 127) {
	float lEncoder = SensorValue[leftDriveEncoder];
	float rEncoder = SensorValue[rightDriveEncoder];
	int currentLeft = lEncoder;
	int currentRight = rEncoder;
	float leftPosToGet = currentLeft + (8 * degrees);
	float rightPosToGet = currentRight + (8 * degrees);
	while (lEncoder < leftPosToGet - offset && rEncoder <  rightPosToGet - offset) {
		if (lEncoder < leftPosToGet - offset) {
			motor[leftfront] = speed;
			motor[leftback] = speed;
		}
		if (rEncoder < rightPosToGet - offset) {
			motor[rightfront] = -speed;
			motor[rightback] = -speed;
		}
		lEncoder = SensorValue[leftDriveEncoder];
		rEncoder = SensorValue[rightDriveEncoder];
	}
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[leftfront] = 0;
	motor[rightfront] = 0;
}

void turnLeft(int offset, float degrees = 90.00, int speed = 127) {
	float lEncoder = -SensorValue[leftDriveEncoder];
	float rEncoder = -SensorValue[rightDriveEncoder];
	int currentLeft = lEncoder;
	int currentRight = rEncoder;
	float leftPosToGet = currentLeft + (8 * degrees);
	float rightPosToGet = currentRight + (8 * degrees);
	while (lEncoder < leftPosToGet - offset && rEncoder <  rightPosToGet - offset) {
		if (lEncoder < leftPosToGet - offset) {
			motor[leftfront] = -speed;
			motor[leftback] = -speed;
		}
		if (rEncoder < rightPosToGet - offset) {
			motor[rightfront] = speed;
			motor[rightback] = speed;
		}
		lEncoder = -SensorValue[leftDriveEncoder];
		rEncoder = -SensorValue[rightDriveEncoder];
	}
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[leftfront] = 0;
	motor[rightfront] = 0;
}

void drive (float inches, bool intake, int speed = 127, int offset = 5) {
	//28.65 * inches = encoder ticks
	int lEncoder = SensorValue[leftDriveEncoder];
	int rEncoder = -SensorValue[rightDriveEncoder];
	int lCurrentDrive = lEncoder;
	int rCurrentDrive = rEncoder;
	int eGoal = 28.65 * inches;
	if (intake) {
		motor[rightintake] = 127;
	}
	while (lEncoder < lCurrentDrive + eGoal - offset && rEncoder < rCurrentDrive + eGoal - offset) {
		if (lEncoder < lCurrentDrive + eGoal - offset) {
			motor[leftback] = speed;
			motor[leftfront] = speed;
		}
		if (rEncoder < rCurrentDrive + eGoal - offset) {
			motor[rightback] = speed;
			motor[rightfront] = speed;
		}
		lEncoder = SensorValue[leftDriveEncoder];
		rEncoder = -SensorValue[rightDriveEncoder];
	}
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[leftfront] = 0;
	motor[rightfront] = 0;
	motor[rightintake] = 0;
}

void driveTime(int ms, int speed = 127, bool forward = true) {
	if (forward) {
		motor[leftback] = speed;
		motor[rightback] = speed;
		motor[leftfront] = speed;
		motor[rightfront] = speed;
	} else {
		motor[leftback] = -speed;
		motor[rightback] = -speed;
		motor[leftfront] = -speed;
		motor[rightfront] = -speed;
	}
	wait1Msec(ms);
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[leftfront] = 0;
	motor[rightfront] = 0;
};

void driveBack(float inches, bool intake, int speed = 127, int offset = 5) {
	//28.65 * inches = encoder ticks
	int lEncoder = -SensorValue[leftDriveEncoder];
	int rEncoder = SensorValue[rightDriveEncoder];
	int lCurrentDrive = lEncoder;
	int rCurrentDrive = rEncoder;
	int eGoal = 28.65 * inches;
	if (intake) {
		motor[rightintake] = -127;
	}
	while (lEncoder < lCurrentDrive + eGoal - offset && rEncoder < rCurrentDrive + eGoal - offset) {
		if (lEncoder < lCurrentDrive + eGoal - offset) {
			motor[leftback] = -speed;
			motor[leftfront] = -speed;
		}
		if (rEncoder < rCurrentDrive + eGoal - offset) {
			motor[rightback] = -speed;
			motor[rightfront] = -speed;
		}
		lEncoder = -SensorValue[leftDriveEncoder];
		rEncoder = SensorValue[rightDriveEncoder];
	}
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[leftfront] = 0;
	motor[rightfront] = 0;
	motor[rightintake] = 0;
}

void intake (int time = 1000, int speed = 127) {
	motor[rightintake] = speed;
	wait1Msec(time);
	motor[rightintake] = 0;
}

void outtake(int time = 250, int speed = 127) {
	motor[rightintake] = -speed;
	wait1Msec(time);
	motor[rightintake] = 0;
}

void strafeLeft(float inches, int offset = 5) {
	int currentLeft = -SensorValue[leftDriveEncoder];
	int currentRight = SensorValue[rightDriveEncoder];
	int startLeft = currentLeft;
	int startRight = currentRight;
	float eGoal = 57.3 * inches;
	while (currentLeft < startLeft + eGoal && currentRight < startRight + eGoal) {
		if (currentLeft < startLeft + eGoal) {
			motor[leftfront] = -127;
			motor[leftback] = 127;
		}
		if (currentRight < startRight + eGoal) {
			motor[rightfront] = 127;
			motor[rightback] = -127;
		}
		currentLeft = -SensorValue[leftDriveEncoder];
		currentRight = SensorValue[rightDriveEncoder];
	}
	motor[leftfront] = 0;
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[rightfront] = 0;
}

void strafeRight(float inches, int offset = 5) {
	int currentLeft = SensorValue[leftDriveEncoder];
	int currentRight = -SensorValue[rightDriveEncoder];
	int startLeft = currentLeft;
	int startRight = currentRight;
	float eGoal = 57.3 * inches;
	while (currentLeft < startLeft + eGoal && currentRight < startRight + eGoal) {
		if (currentLeft < startLeft + eGoal) {
			motor[leftfront] = 127;
			motor[leftback] = -127;
		}
		if (currentRight < startRight + eGoal) {
			motor[rightfront] = -127;
			motor[rightback] = 127;
		}
		currentLeft = SensorValue[leftDriveEncoder];
		currentRight = -SensorValue[rightDriveEncoder];
	}
	motor[leftfront] = 0;
	motor[leftback] = 0;
	motor[rightback] = 0;
	motor[rightfront] = 0;
}

void beginBlue() {
	int time = 250;
	motor[rightfront] = 0;
	motor[rightback] = 0;
	wait1Msec(time);
	motor[rightfront] = 0;
	motor[rightback] = 0;
	wait1Msec(time);
	motor[rightfront] = 0;
	motor[rightback] = 0;
}

void beginRed() {
	int time = 250;
	motor[leftback] = 0;
	wait1Msec(time);
	motor[leftfront] = 0;
	motor[leftback] = 0;
	wait1Msec(time);
	motor[leftfront] = 0;
	motor[leftback] = 0;
}

void goToHeight(int height, int speed = 127) {
	int offset = 10;
	int lEncoder = -SensorValue[leftLiftEncoder];
	int rEncoder = SensorValue[rightLiftEncoder];
	if (lEncoder < height - offset) {
		while (lEncoder < height - offset && rEncoder < height - offset) {
			if (lEncoder < height - offset) {
				motor[leftbottomlift] = speed;
				motor[lefttoplift] = speed;
			}
			if (rEncoder < height - offset) {
				motor[rightbottomlift] = speed;
				motor[righttoplift] = speed;
			}
			lEncoder = -SensorValue[leftLiftEncoder];
			rEncoder = SensorValue[rightLiftEncoder];
		}
		} else if (lEncoder > height + offset) {
		while (lEncoder > height + offset && rEncoder > height + offset) {
			if (lEncoder > height + offset) {
				motor[leftbottomlift] = -speed;
				motor[lefttoplift] = -speed;
			}
			if (rEncoder > height + offset) {
				motor[rightbottomlift] = -speed;
				motor[righttoplift] = -speed;
			}
			lEncoder = -SensorValue[leftLiftEncoder];
			rEncoder = SensorValue[rightLiftEncoder];
		}
	}
	motor[righttoplift] = 0;
	motor[rightbottomlift] = 0;
	motor[lefttoplift] = 0;
	motor[leftbottomlift] = 0;
}

void stopDrive() {
	motor[leftback] = 0;
	motor[leftfront] = 0;
	motor[rightfront] = 0;
	motor[rightback] = 0;
}

/*
	Left pos is 2189
	Right pos is 1213
	Rest pos is 0
*/

void leftSwing(float factor = 0.5) {
	int swingPos = -SensorValue[swingEncoder];
	int target = 2290;//2250;//2225;//2150;  //2215 for unskewed
	while (swingPos < target) {
		float dist = swingPos - target;
		motor[swinger] = dist * factor;
		swingPos = -SensorValue[swingEncoder];
	}
	motor[swinger] = 0;
}

void rightSwing(float factor = 0.35) {
	int swingPos = -SensorValue[swingEncoder];
	int target = 1300;//1260;//1295;//1130;  //1250 for not skewed
	//int target = trueTarget + 70;
	int minSpeed = 25;
	if (swingPos > target) {  //claw is too much to the left
		while (swingPos > target) {
			float dist = swingPos - target;
			if (dist * factor >= minSpeed) {
				motor[swinger] = dist * factor;
			} else {
				motor[swinger] = minSpeed;
			}
			swingPos = -SensorValue[swingEncoder];
		}
	} else {  //claw is too much to the right
		while (swingPos < target) {
			float dist = target - swingPos;
			motor[swinger] = dist * factor;
			swingPos = -SensorValue[swingEncoder];
		}
	}
	motor[swinger] = 0;
}

void grab() {
	SensorValue[claw] = 0;
}

void release() {
	SensorValue[claw] = 1;
}

void unlock() {
	motor[rightintake] = -127;
	wait1Msec(75);
	motor[rightintake] = 0;
}

void holdLift() {
	motor[righttoplift] = -127;
	motor[rightbottomlift] = -127;
	motor[lefttoplift] = -127;
	motor[leftbottomlift] = -127;
}

void releaseLift() {
	motor[righttoplift] = 0;
	motor[rightbottomlift] = 0;
	motor[lefttoplift] = 0;
	motor[leftbottomlift] = 0;
}


//-------------------------------------------------------------------------------
//----------------------AUTONOMOUS-----------------------------------------------
//-------------------------------------------------------------------------------


task autonomous() {
	if (SensorValue[isStarted] == 1) {  //auto check
	//Declare count variable to keep track of our choice

	int speed = 95;

	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	switch(count){  //blue skyrise, red skyrise, blue cube, red cube
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "Blue Skyrise");
		displayLCDCenteredString(1, "is running!");

		unlock();

		//Height list
		int hoverHeights[] = {5, 170, 355, 480, 750};  //to be over the skyrise - NOT INSIDE YET
		int hoverDiff = 5;  //hoverHeights[x] +- hoverDiff
		int pickupSkyriseHeight = 70;
		int skyriseHeightDiff = 250;  //+pickupSkyriseHeight to swing out

		//goToHeight(pickupSkyriseHeight + 100);  //lift enough to swing out and be above skyrise

		int skyriseNum = 0;
		int arrLength = sizeof(hoverHeights)/sizeof(int);  //length of hoverHeights array

		while (skyriseNum < arrLength) {  //do all skyrises
			//stack with skyriseNum as hoverHeights
			leftSwing();  //go to pos
			if (skyriseNum == 0) {
				release();
			}
			goToHeight(pickupSkyriseHeight);  //go down
			holdLift();
			wait1Msec(500);
			grab();
			wait1Msec(500);
			releaseLift();
			if (skyriseNum == 0) {  //Lift up and then lower back down
				goToHeight(pickupSkyriseHeight + skyriseHeightDiff, 68);
				wait1Msec(500);
				rightSwing();
				wait1Msec(2000);  //orig 3500
				goToHeight(hoverHeights[skyriseNum] - hoverDiff, 75);
				wait1Msec(1500);  //let it wiggle out - orig 4500
				release();
				wait1Msec(500);
			} else {
				goToHeight(hoverHeights[skyriseNum]);  //lift to above Xth skyrise
				wait1Msec(500);
				rightSwing();  //go to above it
				wait1Msec(1000);
				if (skyriseNum == 3) {
					driveTime(75);
				}
				if (skyriseNum == 4) {
					driveTime(150);
				}
				goToHeight(hoverHeights[skyriseNum] - hoverDiff);  //lower
				wait1Msec(1500); //let it wiggle out
				release();
				goToHeight(hoverHeights[skyriseNum]);  //raise enough to clear current skyrise
			}
			skyriseNum++;
		}

		break;
	case 1:
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "Red Skyrise");
		displayLCDCenteredString(1, "is running!");

		break;
	case 2:
		//If count = 2, run the code correspoinding with choice 3
		displayLCDCenteredString(0, "Blue Cube");
		displayLCDCenteredString(1, "is running!");
		drive(12, false, speed);
		intake();
		strafeLeft(28.00, speed);
		turnLeft(5, 170.00, speed);
		drive(37, false, speed);
		outtake();
		driveBack(18, true);
		break;
	case 3:
		//If count = 3, run the code correspoinding with choice 4
		displayLCDCenteredString(0, "Red Cube");
		displayLCDCenteredString(1, "is running!");
		drive(12, false, speed);
		intake();
		strafeRight(28.00, speed);
		turnRight(5, 170.00, speed);
		drive(37, false, speed);
		outtake();
		driveBack(18, true);
		break;
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}  //corresponds to auto check - TBR
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol() {
	int offset = 17;
	int encoderOffset = 50;

	//reset encoders?

	int pos = 0;

	int leftLift = 0;
	int rightLift = 0;

	float speedFactor = 1;

	float highSpeed = 1;
	float lowSpeed = 0.5;

	float liftFactor = 1;
	float highLift = 1;
	float lowLift = 0.85;
	float togglePoint = 600;

	bool holding = false;

	while (true) {
		//JOYSTICK VARIABLES
		float joyY = vexRT[Ch3];
		float joyX = vexRT[Ch4];
		int liftControl = vexRT[Ch2];

		//ENCODER
		leftLift = -SensorValue[leftLiftEncoder];
		rightLift = SensorValue[rightLiftEncoder];

		//MOVEMENT
		//Linear/swing turning
		if (abs(joyY) > offset) {
			motor[leftback]  = (joyY + joyX)*speedFactor;
			motor[leftfront]  = (joyY + joyX)*speedFactor;
			motor[rightfront] = (joyY - joyX)*speedFactor;
			motor[rightback] = (joyY - joyX)*speedFactor;
		}
		//point turn
		else if (abs(joyX) > offset && abs(joyY) < offset) {
			motor[leftback] = joyX*speedFactor;
			motor[leftfront] = joyX*speedFactor;
			motor[rightfront] = -joyX*speedFactor;
			motor[rightback] = -joyX*speedFactor;
		}  //STRAFE LEFT - MOVEMENT OVERRIDES ALL STRAFING!
		else if (vexRT[Btn5U] == 1) {
			motor[leftback] = 127*speedFactor;
			motor[leftfront] = -127*speedFactor;
			motor[rightfront] = 127*speedFactor;
			motor[rightback] = -127*speedFactor;
		}  //STRAFE RIGHT
		else if (vexRT[Btn5D] == 1) {
			motor[leftback] = -127*speedFactor;
			motor[leftfront] = 127*speedFactor;
			motor[rightfront] = -127*speedFactor;
			motor[rightback] = 127*speedFactor;
		}
		else {
			motor[leftback] = 0;
			motor[leftfront] = 0;
			motor[rightfront] = 0;
			motor[rightback] = 0;
		}

		//LIFT
		if (abs(liftControl) > offset) {
			//I2C SETTING
			if (liftControl < -offset) {  //going down
				if (leftLift < rightLift - encoderOffset) {  //left's lower, so push right down
					motor[righttoplift] = -127;
					motor[rightbottomlift] = -127;
					motor[lefttoplift] = 0;
					motor[lefttoplift] = 0;
					} else if (rightLift < leftLift - encoderOffset) {  //right's lower so push left down
					motor[lefttoplift] = -127;
					motor[leftbottomlift] = -127;
					motor[righttoplift] = 0;
					motor[rightbottomlift] = 0;
					} else {
					motor[lefttoplift] = liftControl * liftFactor;
					motor[righttoplift] = liftControl * liftFactor;
					motor[leftbottomlift] = liftControl * liftFactor;
					motor[rightbottomlift] = liftControl * liftFactor;
				}
				holding = false;
				} else {  //going up
				if (leftLift > rightLift + encoderOffset) {  //left's higher, so push right up
					motor[righttoplift] = 127;
					motor[rightbottomlift] = 127;
					motor[lefttoplift] = 0;
					motor[lefttoplift] = 0;
					} else if (rightLift > leftLift + encoderOffset) {  //right's higher, so push left up
					motor[lefttoplift] = 127;
					motor[leftbottomlift] = 127;
					motor[righttoplift] = 0;
					motor[rightbottomlift] = 0;
					} else {
					motor[lefttoplift] = liftControl;
					motor[righttoplift] = liftControl;
					motor[leftbottomlift] = liftControl;
					motor[rightbottomlift] = liftControl;
				}
				holding = true;
			}
			pos = (leftLift + rightLift)/2;
			} else if (vexRT[Btn8DXmtr2] == 1) {  //Ground
			stopDrive();
			goToHeight(0);
			} else if (vexRT[Btn8UXmtr2] == 1) {  //Skyrise pickup/2nd skyrise set/1st skyrise block
			stopDrive();
			goToHeight(392);
		} //add more else/if
		else {
			motor[lefttoplift] = 0;
			motor[righttoplift] = 0;
			motor[leftbottomlift] = 0;
			motor[rightbottomlift] = 0;
		}

		//LIFT SPEED SWITCH
		if (pos < togglePoint) {
			liftFactor = highLift;
			} else {
			liftFactor = lowLift;
		}


		//INTAKE
		if (vexRT[Btn6U] == 1) {
			motor[rightintake] = -127;
			} else if (vexRT[Btn6D] == 1) {
			motor[rightintake] = 127;
			} else {
			motor[rightintake] = 0;
		}

		//SWINGER
		if (vexRT[Btn7U] == 1) {
			motor[swinger] = -127;
			} else if (vexRT[Btn7D] == 1) {
			motor[swinger] = 127;
			} else {
			motor[swinger] = 0;
		}

		//SWITCH SPEED MODE
		if (vexRT[Btn6UXmtr2] == 1) {
			if (speedFactor == highSpeed) {
				speedFactor = lowSpeed;
				} else if (speedFactor == lowSpeed) {
				speedFactor = highSpeed;
			}
			while (vexRT[Btn6UXmtr2] == 1) {}
		}

		//CLAW
		if (vexRT[Btn7L] == 1) {
			SensorValue[claw] = abs(SensorValue[claw] - 1);
			while (vexRT[Btn7L] == 1) {}
		}
	}
}
