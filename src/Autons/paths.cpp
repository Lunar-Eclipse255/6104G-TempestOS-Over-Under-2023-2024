#include "main.h"
#include "display.hpp"
#include "motors.h"
#include "paths.hpp"

void generateMotionProfile(std::shared_ptr<AsyncMotionProfileController> profileController) {
    profileController->generatePath({
        {0_ft, 0_ft, 0_deg},  // Profile starting position
        {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
        "Left AWP" // Profile name
    );
    profileController->generatePath({
        {0_ft, 0_ft, 0_deg},  // Profile starting position
        {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
        "Right AWP" // Profile name
    );
    profileController->generatePath({
        {0_ft, 0_ft, 0_deg},  // Profile starting position
        {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
        "Left Points" // Profile name
    );
    profileController->generatePath({
        {0_ft, 0_ft, 0_deg},  // Profile starting position
        {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
        "Right Points" // Profile name
    );
}