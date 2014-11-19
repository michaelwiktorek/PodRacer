#import "PodController.h"

PodController::PodController()
{
	super();
}

PodController::PodController(Racer *newRacer)
{
	super();
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