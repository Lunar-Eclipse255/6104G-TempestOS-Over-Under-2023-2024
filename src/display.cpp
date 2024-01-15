
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
int selectedProfile = 0;
int selectedGIF =0;

//Sets up which programs to select from
const char* GIFFilePaths[] = {"/usd/Sylvie.gif","/usd/Catapult.gif","/usd/Alliance.gif","/usd/Glitch.gif","/usd/Lightning.gif","/usd/Rumble.gif"};
void (*redScripts[])() = {leftRedOneAuton, rightRedOneAuton, placeHolder, leftRedTwoAuton, rightRedTwoAuton};
void (*blueScripts[])() = {leftBlueOneAuton, rightBlueOneAuton, placeHolder, leftBlueTwoAuton, rightBlueTwoAuton};
void (*skillsScripts[])() = {pSkills,dSkills};



//Creates the Objects
//Creates Screens
lv_obj_t* autonScreen = lv_obj_create(NULL, NULL); 
lv_obj_t* skillsScreen = lv_obj_create(NULL,NULL);
lv_obj_t* debugScreen = lv_obj_create(NULL, NULL);
lv_obj_t* profileScreen = lv_obj_create(NULL,NULL);
lv_obj_t* visualScreen = lv_obj_create(NULL,NULL);

// Creates Buttons

//Creates Checkboxes for Profiles
lv_obj_t* profile1;
lv_obj_t* profile2;

lv_obj_t* ddlColorSelection = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlAutonSelector = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlSkillsSelector = lv_ddlist_create(skillsScreen, NULL);
lv_obj_t* ddlProfileSelector = lv_ddlist_create(profileScreen, NULL);
lv_obj_t* ddlGIF = lv_ddlist_create(visualScreen,NULL);
lv_obj_t* ddlAuton = lv_ddlist_create(autonScreen, NULL);
lv_obj_t* ddlSkills = lv_ddlist_create(skillsScreen, NULL);
lv_obj_t* ddlProfile = lv_ddlist_create(profileScreen, NULL);
lv_obj_t* ddlDebug = lv_ddlist_create(debugScreen, NULL);
lv_obj_t* ddlVision = lv_ddlist_create(visualScreen, NULL);



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
        lv_ddlist_set_selected(ddlDebug, 3);
        break;
    case 4:
        lv_scr_load(visualScreen);
        lv_ddlist_set_selected(ddlVision,4);
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
    case 2:
        // Option 1 selected, load screen1
        selectedProgram = 1;
        break;
    case 3:
        // Option 2 selected, load screen2
        selectedProgram = 2;
        break;
    case 4:
        // Option 3 selected, load screen3
        selectedProgram = 3;
        break;
    case 5:
        selectedProgram = 4;
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
        selectedProgram=0;
        break;
    case 2:
        autoType = AUTONOMOUS_SKILLS;
        selectedProgram=1;
        break;
    default:
        break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistProfileSelectorAction(lv_obj_t* ddlist) {
    uint16_t selected_index = lv_ddlist_get_selected(ddlist);
    switch(selected_index)
    {
        case 0:
            break;
        case 1:
            selectedProfile = 0;
            break;
        case 2:
            selectedProfile=1;
            break;
        default:
            break;
    }
    return LV_RES_OK;
}

static lv_res_t ddlistGIFSelectorAction(lv_obj_t* ddlist){
    uint16_t selected_index =lv_ddlist_get_selected(ddlist);
    switch(selected_index){
        case 0:
            break;
        case 1:
            selectedGIF=0;
            break;
        case 2:
            selectedGIF=1;
            break;
        case 3:
            selectedGIF=2;
            break;
        case 4:
            selectedGIF=3;
            break;
        case 5:
            selectedGIF=4;
            break;
        case 6:
            selectedGIF=5;
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
    lv_obj_align(ddlAutonSelector, NULL, LV_ALIGN_IN_LEFT_MID, 95, -20);
    lv_ddlist_set_options(ddlColorSelection, " \n" "Blue\n" "Red\n");
    lv_ddlist_set_action(ddlColorSelection, ddlistColorSelectionAction);
    lv_obj_align(ddlColorSelection, NULL, LV_ALIGN_IN_LEFT_MID, 5, -20);
    lv_ddlist_set_options(ddlAuton, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    lv_ddlist_set_action(ddlAuton, ddlist_action);
    lv_ddlist_set_selected(ddlAuton, 0);
    lv_obj_align(ddlAuton, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    lv_obj_t* gifObjAuton = lv_obj_create(autonScreen, NULL);
    lv_obj_set_size(gifObjAuton, 480, 240);
    lv_obj_set_style(gifObjAuton, &lv_style_transp); // make the container invisible
    lv_obj_align(gifObjAuton, NULL, LV_ALIGN_IN_RIGHT_MID, 300,60);

    static Gif gifAuton("/usd/SPSIntro.gif", gifObjAuton);

    
    
    lv_obj_set_style(skillsScreen, &style);
    lv_ddlist_set_options(ddlSkills, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    lv_ddlist_set_action(ddlSkills, ddlist_action);
    lv_obj_align(ddlSkills, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    lv_ddlist_set_options(ddlSkillsSelector, " \n" "Programming Skills\n" "Driver Skills\n");
    lv_ddlist_set_action(ddlSkillsSelector, ddlistSkillSelectorAction);
    lv_obj_align(ddlSkillsSelector, NULL, LV_ALIGN_IN_LEFT_MID, 5,-20);

    lv_obj_set_style(profileScreen, &style);
    lv_ddlist_set_options(ddlProfile, "Auton\n" "Skills\n" "Profiles\n" "Debug\n" "GIFs");
    lv_ddlist_set_action(ddlProfile, ddlist_action);
    lv_obj_align(ddlProfile, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    lv_ddlist_set_options(ddlProfileSelector, " \n" "Gaston\n" "Patrick\n");
    lv_ddlist_set_action(ddlProfileSelector, ddlistProfileSelectorAction);
    lv_obj_align(ddlProfileSelector, NULL, LV_ALIGN_IN_LEFT_MID, 5, -20);

    // Creates Debug Screen
    //Creates Back button for Debug Screen and matches it to back button click event
    lv_obj_set_style(debugScreen, &style);
    lv_ddlist_set_options(ddlDebug, "Auton\n" "Skills\n" "Profile\n" "Debug\n" "GIFs\n");
    lv_ddlist_set_action(ddlDebug, ddlist_action);
    lv_obj_align(ddlDebug, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    
    
    lv_obj_set_style(visualScreen, &style);
    lv_ddlist_set_options(ddlVision, "Auton\n" "Skills\n" "Profile\n" "Debug\n" "GIFs\n");
    lv_ddlist_set_action(ddlVision, ddlist_action);

    lv_obj_align(ddlVision, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);
    lv_ddlist_set_options(ddlGIF, "Sylvie\n" "Catapult\n" "Alliance\n" "Glitch\n" "Lightning\n" "Rumble\n");
    lv_ddlist_set_action(ddlGIF, ddlistGIFSelectorAction);
    lv_ddlist_set_fix_height(ddlGIF, 150);
    lv_ddlist_set_sb_mode(ddlGIF, LV_SB_MODE_DRAG);
    lv_obj_align(ddlGIF, NULL, LV_ALIGN_IN_LEFT_MID, 5, -20);

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
void runSelectedGIF(void) {
    lv_obj_t* GIFScreen = lv_obj_create(NULL,NULL);
    lv_obj_t* gifObjMain = lv_obj_create(GIFScreen, NULL);
    lv_obj_set_size(gifObjMain, 480, 240);
    lv_obj_set_style(gifObjMain, &lv_style_transp); // make the container invisible
    lv_obj_align(gifObjMain, NULL, LV_ALIGN_IN_RIGHT_MID, 0,0);
    static Gif gifMain(GIFFilePaths[selectedGIF], gifObjMain);
    lv_scr_load(GIFScreen);
}
/* Screen Clear code
lv_init();

// Create a screen object
lv_obj_t *screen = lv_scr_act();

// Clear the screen
lv_obj_clean(screen);
*/		