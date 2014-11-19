#import "PodController.h"

PodController::PodController()
{
	super();
}

PodController::PodController(PodRacer *newPodRacer)
{
	super();
	SetPodRacer(newPodRacer);
}

PodRacer *PodController::GetPodRacer()
{
	return podRacer;
}

void PodController::SetPodRacer(PodRacer *newPodRacer)
{
	podRacer = newPodRacer;
}

void PodController::Update(float dt)
{
	super::Update(dt);
}

void PodController::Render()
{
	// Do nothing
}