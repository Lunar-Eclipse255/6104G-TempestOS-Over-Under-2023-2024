
#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"

#define DO_NOT_RUN 1982
//Adds placeHolder Script
void placeHolder(void){};
//Sets up Variables
int displayMode = 0;
int selectedProgram = DO_NOT_RUN;
int autoType = 0;
bool isLeft = false;
bool selected = false;
int selectedProfile = 0;

//Sets up the names for the checkboxes
const char* redTitles[] = {"Left Auton", "Right Auton", "Disabled", "Left Auton No Bar","Right Auton No Bar"};
const char* blueTitles[] = {"Left Auton", "Right Auton", "Disabled", "Left Auton No Bar","Right Auton No Bar"};
const char* skillsTitles[] = {"Programming Skills","Driver Skills"};
const char* profileTitles[] = {"Gaston", "Patrick"};

//Sets up which programs to select from
void (*redScripts[])() = {leftRedOneAuton, rightRedOneAuton, placeHolder, leftRedTwoAuton, rightRedTwoAuton};
void (*blueScripts[])() = {leftBlueOneAuton, rightBlueOneAuton, placeHolder, leftBlueTwoAuton, rightBlueTwoAuton};
void (*skillsScripts[])() = {pSkills,dSkills};



//Creates the Objects
//Creates Screens
lv_obj_t* autonScreen = lv_obj_create(NULL, NULL); 
lv_obj_t* skillsScreen = lv_obj_create(NULL,NULL);
lv_obj_t* debugScreen;
lv_obj_t* profileScreen = lv_obj_create(NULL,NULL);
lv_obj_t* visualScreen;

// Creates Buttons
lv_obj_t* backButtonDebug;
lv_obj_t* backButtonVisual;

//Creates Checkboxes for Profiles
lv_obj_t* profile1;
lv_obj_t* profile2;

lv_obj_t *ddlColorSelection = lv_ddlist_create(autonScreen, NULL);
lv_obj_t *ddlAutonSelector = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlSkillsSelector = lv_ddlist_create(skillsScreen, NULL);
lv_obj_t *ddlAuton = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlSkills = lv_ddlist_create(skillsScreen, NULL);
lv_obj_t *ddlProfile = lv_ddlist_create(profileScreen, NULL);
//lv_obj_t *ddlDebug = lv_ddlist_create(debugScreen, NULL);
//lv_obj_t *ddlVision = lv_ddlist_create(visualScreen, NULL);

//lv_obj_t *ddlSkills;



//Creates click event for back button
static lv_res_t backButton_click_event(lv_obj_t* button)
{
    // Switch to Screen 2
    lv_scr_load(autonScreen);
    return LV_RES_OK;
}


static lv_res_t ddlist_action(lv_obj_t *ddlist)
{
    // Get the selected option index in the current dropdown list
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch (selected_index)
    {
    case 0:
        // Option 1 selected, load screen1
        lv_scr_load(autonScreen);
        lv_ddlist_set_selected(ddlAuton, 0);
        break;
    case 1:
        // Option 2 selected, load screen2
        lv_scr_load(skillsScreen);
        lv_ddlist_set_selected(ddlSkills, 1);
        break;
    case 2:
        // Option 3 selected, load screen3
        lv_scr_load(profileScreen);
        lv_ddlist_set_selected(ddlProfile, 2);
        break;
    case 3:
        lv_scr_load(debugScreen);
        break;
    case 4:
        lv_scr_load(visualScreen);
        break;
    default:
        // Handle other cases or set a default screen
        break;
    }
    // Get the pointer to the other dropdown list from free_ptr

    return LV_RES_OK; /* Return OK if the dropdown list is not deleted */
}
static lv_res_t ddlistColorSelectionAction(lv_obj_t *ddlist)
{
    // Get the selected option index in the current dropdown list
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch (selected_index)
    {
    case 0:
        break;
    case 1:
        // Option 1 selected, load screen1
	    autoType = AUTONOMOUS_BLUE;
        break;
    case 2:
        // Option 2 selected, load screen2
	    autoType = AUTONOMOUS_RED;
        break;
    default:
        // Handle other cases or set a default screen
        break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistAutonSelectorAction(lv_obj_t *ddlist)
{
    // Get the selected option index in the current dropdown list
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch (selected_index)
    {
    case 0:
        break;
    case 1:
        selectedProgram = 0;
	    selected = true;
    case 2:
        // Option 1 selected, load screen1
        selectedProgram = 1;
	    selected = true;
        break;
    case 3:
        // Option 2 selected, load screen2
        selectedProgram = 2;
	    selected = true;
        break;
    case 4:
        // Option 3 selected, load screen3
        selectedProgram = 3;
	    selected = true;
        break;
    case 5:
        selectedProgram = 4;
	    selected = true;
        break;
    default:
        // Handle other cases or set a default screen
        break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistSkillSelectorAction(lv_obj_t* ddlist) {
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch(selected_index)
    {
    case 0:
        break;
    case 1:
        autoType = AUTONOMOUS_SKILLS;
	    selected = true;
        selectedProgram=0;
        break;
    case 2:
        autoType = AUTONOMOUS_SKILLS;
	    selected = true;
        selectedProgram=1;
        break;
    default:
        break;
    }
    return LV_RES_OK;
}


//Sets up the actions that happen when the checkboxes are checked
/*selected program is how far to index within their respective scripts
ie if void (*blueScripts[])() = {leftBlueAuton, rightBlueAuton, placeHolder};
and autoType=Blue an selectedProgram=1 it would run rightBlueAuton
*/


//If profile1 was selected thern profile 2 is set to false and vice versa
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
    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain);
    style.body.main_color = LV_COLOR_BLACK;
    style.body.grad_color = LV_COLOR_HEX(0x3A3B3C);
    
    // Create the main menu screen
    lv_obj_set_style(autonScreen,&style);
    lv_ddlist_set_options(ddlAutonSelector, " \n" "Right AWP\n" "Right No Bar\n" "Disabled\n" "Left AWP\n" "Left No Bar\n");
    lv_ddlist_set_action(ddlAutonSelector, ddlistAutonSelectorAction);
    lv_ddlist_set_fix_height(ddlAutonSelector, 150);
    lv_ddlist_set_sb_mode(ddlAutonSelector, LV_SB_MODE_DRAG);
    lv_obj_align(ddlAutonSelector, NULL, LV_ALIGN_IN_LEFT_MID, 100, -20);
    lv_ddlist_set_options(ddlColorSelection, " \n" "Blue\n" "Red\n");
    lv_ddlist_set_action(ddlColorSelection, ddlistColorSelectionAction);
    lv_obj_align(ddlColorSelection, NULL, LV_ALIGN_IN_LEFT_MID, 10, -20);
    lv_ddlist_set_options(ddlAuton, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    lv_ddlist_set_action(ddlAuton, ddlist_action);
    lv_ddlist_set_selected(ddlAuton, 0);
    lv_obj_align(ddlAuton, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    lv_obj_t* gifObjMain = lv_obj_create(autonScreen, NULL);
    lv_obj_set_size(gifObjMain, 480, 240);
    lv_obj_set_style(gifObjMain, &lv_style_transp); // make the container invisible
    lv_obj_align(gifObjMain, NULL, LV_ALIGN_IN_RIGHT_MID, 300,60);

    static Gif gifAuton("/usd/SPSIntro.gif", gifObjMain);

    
    
    lv_obj_set_style(skillsScreen, &style);
    lv_ddlist_set_options(ddlSkills, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    lv_ddlist_set_action(ddlSkills, ddlist_action);
    lv_obj_align(ddlSkills, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    lv_ddlist_set_options(ddlSkillsSelector, " \n" "Programming Skills\n" "Driver Skills\n");
    lv_ddlist_set_action(ddlSkillsSelector, ddlistSkillSelectorAction);
    lv_obj_align(ddlSkillsSelector, NULL, LV_ALIGN_IN_LEFT_MID, 10,-20);


    lv_ddlist_set_options(ddlProfile, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    lv_ddlist_set_action(ddlProfile, ddlist_action);
    lv_obj_align(ddlSkills, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);


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
    
    




    
    //Creates Visual Screen
    visualScreen = lv_obj_create(NULL,NULL);

    backButtonVisual = lv_btn_create(visualScreen, NULL);
    lv_btn_set_action(backButtonVisual, LV_BTN_ACTION_CLICK, backButton_click_event);
    lv_obj_align(backButtonVisual,NULL,LV_ALIGN_IN_BOTTOM_RIGHT,-30,10);
    lv_obj_set_size(backButtonVisual,150,50);
    lv_obj_t* backLabelVisual = lv_label_create(backButtonVisual,NULL);
    lv_label_set_text(backLabelVisual, "Back");
    lv_obj_t* gifObj = lv_obj_create(visualScreen, NULL);
    lv_obj_set_size(gifObj, 480, 240);
    lv_obj_set_style(gifObj, &lv_style_transp); // make the container invisible
    lv_obj_align(gifObj, NULL, LV_ALIGN_CENTER, 200, 50);

    static Gif gif("/usd/SPSIntro.gif", gifObj);
    // Load the main menu screen
    lv_scr_load(autonScreen);
}
//Increments the timer
void display(void) {
	lv_task_handler();
	lv_tick_inc(5);
}
//Code to run the right auton based off the checkboxes
// DO NOT TOUCH
void runSelectedAuto(void) {
    /*
	printf("RAN\n");
	printf("%d\n", selectedProgram);
	printf("%d\n", autoType);
	printf("%d\n", AUTONOMOUS_RED);
	printf("%d\n", AUTONOMOUS_BLUE);
    */
	if (selectedProgram == DO_NOT_RUN) {
		return;
	}
	switch (autoType) {
		case AUTONOMOUS_RED:
			printf("LEFT\n");
			redScripts[selectedProgram]();
			break;
		case AUTONOMOUS_BLUE:
			printf("RIGHT\n");
			blueScripts[selectedProgram]();
			break;
		case AUTONOMOUS_SKILLS:
			printf("SKILLS\n");
			skillsScripts[selectedProgram]();
			break;
	}
}
/* Screen Clear code
lv_init();

// Create a screen object
lv_obj_t *screen = lv_scr_act();

// Clear the screen
lv_obj_clean(screen);
*/		