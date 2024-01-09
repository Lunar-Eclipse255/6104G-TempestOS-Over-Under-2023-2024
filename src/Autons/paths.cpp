#include "main.h"
#include "display.hpp"
#include "motors.h"
#include "paths.hpp"

void generateMotionProfile(std::shared_ptr<AsyncMotionProfileController> profileController) {
    profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {16.027_ft, 0.284_ft, 0_deg},
        {33.698_ft, -0.726_ft, 0_deg},
        {55.408_ft, 26.033_ft, 0_deg},
        {8.201_ft, 33.859_ft, 0_deg},
        {40.766_ft, 47.491_ft, 0_deg},
        {18.551_ft, 51.277_ft, 90_deg},
        {40.766_ft, 56.831_ft, 0_deg},
        {5.424_ft, 59.103_ft, 0_deg}}, // The next point in the profile, 3 feet forward
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