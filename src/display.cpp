#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"

#define DO_NOT_RUN 1982
//Adds Placeholder Script
void placeHolder(void){};
//Sets up Variables
int displayMode = 0;
int selectedProgram = DO_NOT_RUN;
int autoType = 0;
bool isLeft = false;
bool selected = false;
bool driverSkillsMode = false;
int selectedProfile = 0;

//Sets up the names for the checkboxes
const char* redTitles[] = {"Red Auton", "Disabled"};
const char* blueTitles[] = {"Blue Auton", "Disabled"};
const char* skillsTitles[] = {"Programming Skills","Driver Skills"};
const char* profileTitles[] = {"Gaston", "Patrick"};

//Sets up which programs to select from
void (*leftScripts[])() = {leftAuton, placeHolder};
void (*rightScripts[])() = {rightAuton, placeHolder};
void (*skillsScripts[])() = {pSkills,dSkills};



//Creates the Objects
//Creates Screens
lv_obj_t* mainMenuScreen;
lv_obj_t* autonScreen;
lv_obj_t* debugScreen;
lv_obj_t* profileScreen;
lv_obj_t* visualScreen;

// Creates Buttons
lv_obj_t* autonButton;
lv_obj_t* debugButton;
lv_obj_t* profileButton;
lv_obj_t* visualButton;
lv_obj_t* backButtonAuton;
lv_obj_t* backButtonDebug;
lv_obj_t* backButtonProfile;
lv_obj_t* backButtonVisual;

//Creates Red Auton Checkboxes
lv_obj_t* redOption1;
lv_obj_t* redOption2;

//Creates Blue Auton Checkboxes
lv_obj_t* blueOption1;
lv_obj_t* blueOption2;

//Creates Checkboxes for Skills
lv_obj_t* skillsOption1;
lv_obj_t* skillsOption2;

//Creates Checkboxes for Profiles
lv_obj_t* profile1;
lv_obj_t* profile2;

//test button for debug
lv_obj_t* driveButtonDebug;



//Creates used Functions
//Creates click event for Auton Button
static lv_res_t autonButton_click_event(lv_obj_t* button)
{
    // Switch to Screen 1
    lv_scr_load(autonScreen);
    return LV_RES_OK;
}

//Creates click event for Debug Button
static lv_res_t debugButton_click_event(lv_obj_t* button)
{
    // Switch to Screen 2
    lv_scr_load(debugScreen);
    return LV_RES_OK;
}

//Creates click event for Profile Button
static lv_res_t profileButton_click_event(lv_obj_t* button)
{
    // Switch to Screen 2
    lv_scr_load(profileScreen);
    return LV_RES_OK;
}

//Creates click event for Visual Button
static lv_res_t visualButton_click_event(lv_obj_t* button)
{
    // Switch to Screen 2
    lv_scr_load(visualScreen);
    return LV_RES_OK;
}

//Creates click event for back button
static lv_res_t backButton_click_event(lv_obj_t* button)
{
    // Switch to Screen 2
    lv_scr_load(mainMenuScreen);
    return LV_RES_OK;
}

//test button for debug


static lv_res_t driveButtonDebug_click_event(lv_obj_t* button)
{
    backRightDriveMotor.moveVoltage(12000);
    pros::delay(1000);
    backRightDriveMotor.moveVoltage(0);
    middleRightDriveMotor.moveVoltage(12000);
    pros::delay(1000);
    middleRightDriveMotor.moveVoltage(0);
    frontRightDriveMotor.moveVoltage(12000);
    pros::delay(1000);
    frontRightDriveMotor.moveVoltage(0);
    backLeftDriveMotor.moveVoltage(12000);
    pros::delay(1000);
    backLeftDriveMotor.moveVoltage(0);
    middleLeftDriveMotor.moveVoltage(12000);
    pros::delay(1000);
    middleLeftDriveMotor.moveVoltage(0);
    frontLeftDriveMotor.moveVoltage(12000);
    pros::delay(1000);
    frontLeftDriveMotor.moveVoltage(0);
    return LV_RES_OK;
}


//In Auton Selector Unchecks all other options in the other tabs
void uncheckColor(bool red, bool blue, bool skills) {
	if (red) {
		lv_cb_set_checked(redOption1, false);
		lv_cb_set_checked(redOption2, false);
	}
	if (blue) {
		lv_cb_set_checked(blueOption1, false);
		lv_cb_set_checked(blueOption2, false);
	}
	if (skills) {
		lv_cb_set_checked(skillsOption1, false);
		lv_cb_set_checked(skillsOption2, false);
	}
}


//Sets up the actions that happen when the checckboxes in the Red tab are checked
lv_action_t setRed(lv_obj_t* checkBox) {
	if (lv_cb_is_checked(redOption1) && redOption1 == checkBox) {
		lv_cb_set_checked(redOption2, false);
		uncheckColor(false, true, true);
		driverSkillsMode = false;
		selectedProgram = 0;
	} else if (lv_cb_is_checked(redOption2) && redOption2 == checkBox) {
		lv_cb_set_checked(redOption1, false);
		uncheckColor(false, true, true);
		driverSkillsMode = false;
		selectedProgram = 1;
	} 
	autoType = AUTONOMOUS_RED;
	selected = true;
	return (lv_action_t)LV_RES_OK;
}

//Sets up the actions that happen when the checckboxes in the Blue tab are checked
lv_action_t setBlue(lv_obj_t* checkBox) {
	if (lv_cb_is_checked(blueOption1) && blueOption1 == checkBox) {
		lv_cb_set_checked(blueOption2, false);
		uncheckColor(true, false, true);
		driverSkillsMode = false;
		selectedProgram = 0;
	} else if (lv_cb_is_checked(blueOption2) && blueOption2 == checkBox) {
		lv_cb_set_checked(blueOption1, false);
		uncheckColor(true, false, true);
		driverSkillsMode = false;
		selectedProgram = 1;
	} 
	autoType = AUTONOMOUS_BLUE;
	selected = true;
	return (lv_action_t)LV_RES_OK;
}

//Sets up the actions that happen when the checckboxes in the Skills tab are checked
lv_action_t setSkills(lv_obj_t* checkBox) {
	if (lv_cb_is_checked(skillsOption1) && skillsOption1 == checkBox) {
		lv_cb_set_checked(skillsOption2, false);
		uncheckColor(true, true, false);
		driverSkillsMode = false;
		selectedProgram = 0;
	} else if (lv_cb_is_checked(skillsOption2) && skillsOption2 == checkBox) {
		lv_cb_set_checked(skillsOption1, false);
		uncheckColor(true, true, false);
		driverSkillsMode = false;
		selectedProgram = 1;
	} 
	autoType = AUTONOMOUS_SKILLS;
	selected = true;
	return (lv_action_t)LV_RES_OK;
}

lv_action_t setProfile(lv_obj_t* checkBox) {
	if (lv_cb_is_checked(profile1) && profile1 == checkBox) {
		lv_cb_set_checked(profile2, false);
		selectedProfile = 0;
	} else if (lv_cb_is_checked(profile2) && profile2 == checkBox) {
		lv_cb_set_checked(profile1, false);
		selectedProfile = 1;
	} 
    return (lv_action_t)LV_RES_OK;
}

//Main Code
void MainLVGL(void)
{
    // Create the main menu screen
    mainMenuScreen = lv_obj_create(NULL, NULL);

    // Creates Auton Button and matches it to Auton click event
    autonButton = lv_btn_create(mainMenuScreen, NULL);
    lv_btn_set_action(autonButton, LV_BTN_ACTION_CLICK, autonButton_click_event);
    // Set the position and size of Auton Button
    lv_obj_align(autonButton, NULL, LV_ALIGN_IN_TOP_LEFT,40,40);
    lv_obj_set_size(autonButton, 150, 50);
    //Creates label for Auton Button
    lv_obj_t* autonButtonLabel = lv_label_create(autonButton, NULL);
    lv_label_set_text(autonButtonLabel, "Auton Screen");

    // Create Debug Button and matches it to Debug click event
    debugButton = lv_btn_create(mainMenuScreen, NULL);
    lv_btn_set_action(debugButton, LV_BTN_ACTION_CLICK, debugButton_click_event);
    // Set the position and size of Debug Button 
    lv_obj_align(debugButton, NULL, LV_ALIGN_IN_BOTTOM_LEFT,40,-10);
    lv_obj_set_size(debugButton, 150, 50);
     //Creates label for Debug Button
    lv_obj_t* debugButtonLabel = lv_label_create(debugButton, NULL);
    lv_label_set_text(debugButtonLabel, "Debug Screen");

    //Creates Profile Button and matches it to Profile click event
    profileButton= lv_btn_create(mainMenuScreen, NULL);
    lv_btn_set_action(profileButton, LV_BTN_ACTION_CLICK, profileButton_click_event);
    //Set position and size of Profile button
    lv_obj_align(profileButton, NULL, LV_ALIGN_IN_TOP_RIGHT,-60,40);
    lv_obj_set_size(profileButton,150,50);
    //Creates label for Profile button
    lv_obj_t* profileButtonLabel = lv_label_create(profileButton,NULL);
    lv_label_set_text(profileButtonLabel, "Profile Screen");

    //Creates Visual Button and matches it to Visual click event
    visualButton= lv_btn_create(mainMenuScreen, NULL);
    lv_btn_set_action(visualButton, LV_BTN_ACTION_CLICK, visualButton_click_event);
    //Set position and size of Visual button
    lv_obj_align(visualButton,NULL,LV_ALIGN_IN_BOTTOM_RIGHT,-60,-10);
    lv_obj_set_size(visualButton,150,50);
    //Creates label for Visual button
    lv_obj_t* visualButtonLabel = lv_label_create(visualButton,NULL);
    lv_label_set_text(visualButtonLabel, "Visual Screen");
    

    

    
    
    // Creates Auton Screen
    autonScreen = lv_obj_create(NULL, NULL);

    //Creates Auton Tabview Object
    lv_obj_t* autonTabview=lv_tabview_create(autonScreen, NULL);
    //Sizes tabs to the screen
    lv_obj_set_size(autonTabview, lv_obj_get_width(autonScreen),lv_obj_get_height(autonScreen));
    //Creates 3 tabs
    lv_obj_t* redTab = lv_tabview_add_tab(autonTabview, "Red Offensive");
    lv_obj_t* blueTab =lv_tabview_add_tab(autonTabview, "Blue Offensive");
    lv_obj_t* skillsTab =lv_tabview_add_tab(autonTabview, "Skills");

    //Creates Back button for Auton Screen and matches it to back button click event
    backButtonAuton = lv_btn_create(autonScreen, NULL);
    lv_btn_set_action(backButtonAuton, LV_BTN_ACTION_CLICK, backButton_click_event);
    //Aligns and changes the size of the button
    lv_obj_align(backButtonAuton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT,-30,10);
    lv_obj_set_size(backButtonAuton, 150, 50);
    //Gives the button a label
    lv_obj_t* backLabelAuton = lv_label_create(backButtonAuton, NULL);
    lv_label_set_text(backLabelAuton, "Back");

    //Creates first red checkbox
    if (sizeof(redTitles) / sizeof(redTitles[0]) > 0) {
    redOption1 = lv_cb_create(redTab, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(redOption1, redTitles[0]);
    //Sets up what happens when selected
    lv_cb_set_action(redOption1, (lv_action_t)setRed);
    //Aligns the checkbox
    lv_obj_align(redOption1, NULL, LV_ALIGN_IN_TOP_LEFT, 10,10);
    }

    //Creates second red checkbox
    if (sizeof(redTitles) / sizeof(redTitles[0]) > 1) {
    redOption2 = lv_cb_create(redTab, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(redOption2, redTitles[1]);
    //Sets up what happens when selected
    lv_cb_set_action(redOption2, (lv_action_t)setRed);
    //Aligns the checkbox
    lv_obj_align(redOption2, NULL, LV_ALIGN_OUT_BOTTOM_LEFT,10,20); 
}

    //Creates first blue checkbox
    if (sizeof(blueTitles) / sizeof(blueTitles[0]) > 0) {
    blueOption1 = lv_cb_create(blueTab, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(blueOption1, blueTitles[0]);
    //Sets up what happens when selected
    lv_cb_set_action(blueOption1, (lv_action_t)setBlue);
    //Aligns the checkbox
    lv_obj_align(blueOption1, NULL, LV_ALIGN_IN_TOP_LEFT, 10,10);
    }

    //Creates second blue checkbox
    if (sizeof(blueTitles) / sizeof(blueTitles[0]) > 1) {
    blueOption2 = lv_cb_create(blueTab, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(blueOption2, blueTitles[1]);
    //Sets up what happens when selected
    lv_cb_set_action(blueOption2, (lv_action_t)setBlue);
    //Aligns the checkbox
    lv_obj_align(blueOption2, NULL, LV_ALIGN_OUT_BOTTOM_LEFT,10,20);
    }

    //Creates first skills checkbox
    if (sizeof(skillsTitles) / sizeof(skillsTitles[0]) > 0) {
    skillsOption1 = lv_cb_create(skillsTab, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(skillsOption1, skillsTitles[0]);
    //Sets up what happens when selected
    lv_cb_set_action(skillsOption1, (lv_action_t)setSkills);
    //Aligns the checkbox
    lv_obj_align(skillsOption1, NULL, LV_ALIGN_IN_TOP_LEFT, 10,10);
    }

    //Creates second skills checkbox
    if (sizeof(skillsTitles) / sizeof(skillsTitles[0]) > 1) {
    skillsOption2 = lv_cb_create(skillsTab, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(skillsOption2, skillsTitles[1]);
    //Sets up what happens when selected
    lv_cb_set_action(skillsOption2, (lv_action_t)setSkills);
    //Aligns the checkbox
    lv_obj_align(skillsOption2, NULL, LV_ALIGN_OUT_BOTTOM_LEFT,10,20);
    }
    
    
    // Creates Debug Screen
    debugScreen = lv_obj_create(NULL, NULL);

    //Creates Back button for Debug Screen and matches it to back button click event
    backButtonDebug = lv_btn_create(debugScreen, NULL);
    lv_btn_set_action(backButtonDebug, LV_BTN_ACTION_CLICK, backButton_click_event);
    //Aligns and changes the size of the button
    lv_obj_align(backButtonDebug, NULL, LV_ALIGN_IN_BOTTOM_RIGHT,-30,10);
    lv_obj_set_size(backButtonDebug, 150, 50);
    //Gives the button a label
    lv_obj_t* backLabelDebug = lv_label_create(backButtonDebug, NULL);
    lv_label_set_text(backLabelDebug, "Back");


    //test button for debug
    
    driveButtonDebug = lv_btn_create(debugScreen, NULL);
    lv_btn_set_action(driveButtonDebug, LV_BTN_ACTION_CLICK, driveButtonDebug_click_event);
    lv_obj_align(driveButtonDebug, NULL, LV_ALIGN_CENTER,0,0);
    lv_obj_set_size(driveButtonDebug, 150,50);
    lv_obj_t* driveLabelDebug = lv_label_create(driveButtonDebug, NULL);
    lv_label_set_text(driveLabelDebug, "Drivetrain Test");
    


    //Creates Profile Screen
    profileScreen = lv_obj_create(NULL,NULL);

    backButtonProfile = lv_btn_create(profileScreen, NULL);
    lv_btn_set_action(backButtonProfile, LV_BTN_ACTION_CLICK, backButton_click_event);
    lv_obj_align(backButtonProfile, NULL, LV_ALIGN_IN_BOTTOM_RIGHT,-30,10);
    lv_obj_set_size(backButtonProfile, 150,50);
    lv_obj_t* backLabelProfile = lv_label_create(backButtonProfile, NULL);
    lv_label_set_text(backLabelProfile, "Back");

    //Creates first profile checkbox
    if (sizeof(profileTitles) / sizeof(profileTitles[0]) > 0) {
    profile1 = lv_cb_create(profileScreen, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(profile1, profileTitles[0]);
    //Sets up what happens when selected
    lv_cb_set_action(profile1, (lv_action_t)setProfile);
    //Aligns the checkbox
    lv_obj_align(profile1, NULL, LV_ALIGN_IN_TOP_LEFT, 30,85);
    }

    //Creates second profile checkbox
    if (sizeof(profileTitles) / sizeof(profileTitles[0]) > 1) {
    profile2 = lv_cb_create(profileScreen, NULL);
    //Adds label to the checkbox
    lv_cb_set_text(profile2, profileTitles[1]);
    //Sets up what happens when selected
    lv_cb_set_action(profile2, (lv_action_t)setProfile);
    //Aligns the checkbox
    lv_obj_align(profile2 , NULL, LV_ALIGN_IN_BOTTOM_LEFT,30,-105);
    }


    //Creates Visual Screen
    visualScreen = lv_obj_create(NULL,NULL);

    backButtonVisual = lv_btn_create(visualScreen, NULL);
    lv_btn_set_action(backButtonVisual, LV_BTN_ACTION_CLICK, backButton_click_event);
    lv_obj_align(backButtonVisual,NULL,LV_ALIGN_IN_BOTTOM_RIGHT,-30,10);
    lv_obj_set_size(backButtonVisual,150,50);
    lv_obj_t* backLabelVisual = lv_label_create(backButtonVisual,NULL);
    lv_label_set_text(backLabelVisual, "Back");


    // Load the main menu screen
    lv_scr_load(mainMenuScreen);
}
//Increments the timer
void display(void) {
	lv_task_handler();
	lv_tick_inc(5);
}
//Code to run the right auton based off the checkboxes
// DO NOT TOUCH
void runSelectedAuto(void) {
	printf("RAN\n");
	printf("%d\n", selectedProgram);
	printf("%d\n", autoType);
	printf("%d\n", AUTONOMOUS_RED);
	printf("%d\n", AUTONOMOUS_BLUE);
	if (selectedProgram == DO_NOT_RUN) {
		return;
	}
	switch (autoType) {
		case AUTONOMOUS_RED:
			printf("LEFT\n");
			leftScripts[selectedProgram]();
			break;
		case AUTONOMOUS_BLUE:
			printf("RIGHT\n");
			rightScripts[selectedProgram]();
			break;
		case AUTONOMOUS_SKILLS:
			printf("SKILLS\n");
			skillsScripts[selectedProgram]();
			break;
	}
}
/* SCreen Clear code
lv_init();

// Create a screen object
lv_obj_t *screen = lv_scr_act();

// Clear the screen
lv_obj_clean(screen);
*/		