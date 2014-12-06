#pragma once

#include "stdafx.h"
#include "Checkpoint.h"
#include "racer/Racer.h"

class RacerData
{
public:
	RacerData()
	{
		lap = 0;
		checkpoint = 0;
	};
	int lap;
	int checkpoint;
};

class Race : public Actor
{
public:
	Race();
	void AddCheckpoint(Checkpoint *checkpoint);
	void AddRacer(Racer *racer);
	virtual void Update(float dt);
	virtual void Render();
protected:
	std::vector<Checkpoint *> checkpoints;
	std::vector<Racer *> racers;
	std::map<Racer *, RacerData> racerData;
};