#import "AIPodController.h"

AIPodController::AIPodController()
	: AIPodController(NULL) {}

AIPodController::AIPodController(Racer *racer)
	: AIPodController(racer, NULL) {}

AIPodController::AIPodController(Racer *racer, Race *race)
	: super(racer)
{
	this->race = race;
	difficulty = 1.0;
}

void AIPodController::SetDifficulty(float x)
{
	difficulty = x;
}

void AIPodController::Update(float dt)
{
	super::Update(dt);

	if (race != NULL)
	{
		Checkpoint *checkpoint = race->GetCheckpoint(racer);
		Checkpoint *checkpoint2 = race->GetCheckpoint(racer, 1);
		Vector2 checkpointDisplacement = checkpoint->GetPosition() - racer->GetPosition();
		float checkpointDistance = checkpointDisplacement.Length();

		Vector2 target;
		float speed = racer->GetVelocity().Length();
		float predictionDistance = speed * 0.005 * checkpoint->width + checkpoint->width;
		if (checkpointDistance < predictionDistance)
		{
			target = checkpoint->GetPosition() * (checkpointDistance / predictionDistance)
			         + checkpoint2->GetPosition() * (1 - checkpointDistance / predictionDistance);
		}
		else
		{
			target = checkpoint->GetPosition();
		}

		float currentDirection = racer->GetDirection();
		float targetDirection = MathUtil::ToDegrees(MathUtil::AngleFromVector(target - racer->GetPosition()));
		float turnAmount = angleDelta(currentDirection, targetDirection) / 180.0;
		turnAmount *= 5.0;
		turnAmount = 0.5 * (turnAmount * turnAmount * turnAmount) + 0.5 * turnAmount * (50.0 / checkpoint->width);
		turnAmount = MathUtil::Clamp(turnAmount, -1.0f, 1.0f);

		float maxThrottle = theTuning.GetFloat("AIDifficulty") * difficulty;
		racer->rightEngine->SetThrottle((1.0 +  turnAmount) * maxThrottle);
		racer->leftEngine->SetThrottle((1.0 - turnAmount) * maxThrottle);

		if (turnAmount > 0)
		{
			racer->SetLeftFlaps(turnAmount);
			racer->SetRightFlaps(0);
		}
		else
		{
			racer->SetLeftFlaps(0);
			racer->SetRightFlaps(-turnAmount);
		}
	}
}

void AIPodController::SetRace(Race *r)
{
	race = r;
}