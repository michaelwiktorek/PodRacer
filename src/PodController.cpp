#import "PodController.h"

PodController::PodController()
{
}

PodController::PodController(Racer *newRacer)
{
	SetRacer(newRacer);
}

Racer *PodController::GetRacer()
{
	return racer;
}

void PodController::SetRacer(Racer *newRacer)
{
	racer = newRacer;
}

void PodController::Update(float dt)
{
	super::Update(dt);
}

void PodController::Render()
{
	// Do nothing
}