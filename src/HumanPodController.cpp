#import "HumanPodController.h"

void HumanPodController::Update(float dt)
{
	super::Update(dt);

	if (!theController.IsConnected())
	{
		return;
	}

	float leftTrigger = (theController.GetLeftTrigger() + 32768.0) / (2 * 32768.0);
	float rightTrigger = (theController.GetRightTrigger() + 32768.0) / (2 * 32768.0);
	float leftThrottle = theController.GetLeftThumbVec2().Y;
	float rightThrottle = theController.GetRightThumbVec2().Y;

	racer->leftEngine->SetLeftFlap(leftTrigger);
	racer->leftEngine->SetRightFlap(rightTrigger);
	racer->rightEngine->SetLeftFlap(leftTrigger);
	racer->rightEngine->SetRightFlap(rightTrigger);
	racer->pod->SetLeftFlap(leftTrigger);
	racer->pod->SetRightFlap(rightTrigger);

	racer->leftEngine->SetThrottle(leftThrottle);
	racer->rightEngine->SetThrottle(rightThrottle);
}
