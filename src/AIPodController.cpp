#import "AIPodController.h"

void AIPodController::Update(float dt)
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

	podRacer->leftEngine->SetLeftFlap(leftTrigger);
	podRacer->leftEngine->SetRightFlap(rightTrigger);
	podRacer->rightEngine->SetLeftFlap(leftTrigger);
	podRacer->rightEngine->SetRightFlap(rightTrigger);
	podRacer->pod->SetLeftFlap(leftTrigger);
	podRacer->pod->SetRightFlap(rightTrigger);

	podRacer->leftEngine->throttle = leftThrottle;
	podRacer->rightEngine->throttle = rightThrottle;
}
