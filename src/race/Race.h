#pragma once

#include "stdafx.h"
#include "Checkpoint.h"
#include "racer/Racer.h"

/**
 * Data the race stores about each racer.
 */
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

/**
 * Manages
 */
class Race : public Actor
{
public:
	Race();
	virtual void Update(float dt);
	virtual void Render();
	/**
	 * Add a checkpoint to the race.
	 * @param checkpoint
	 */
	virtual void AddCheckpoint(Checkpoint *checkpoint);
	/**
	 * Add a racer to the race, and to the world.
	 * @param racer
	 */
	virtual void AddRacer(Racer *racer);
	/**
	 * Get the lap a racer is on.
	 * @param  racer
	 * @return
	 */
	virtual int GetLap(Racer *racer);
	/**
	 * Get the number of a checkpoint a racer is on.
	 * @param  racer
	 * @return checkpoint number
	 */
	virtual int GetCheckpointNum(Racer *racer);
	/**
	 * Get the place the racer is. (0 = 1st, 1 = 2nd)
	 * @param  racer
	 * @return place
	 */
	virtual int GetPlace(Racer *racer);
	/**
	 * Get the target checkpoint for this racer.
	 * @param  racer
	 * @return checkpoint
	 */
	virtual Checkpoint *GetCheckpoint(Racer *racer);
	/**
	 * Get the target + i checkpoint for this racer.
	 * @param  racer
	 * @param  i number of checkpoints ahead
	 * @return checkpoint
	 */
	virtual Checkpoint *GetCheckpoint(Racer *racer, int i);
	/**
	 * Get the ith checkpoint.
	 * @param  i index of the checkpoint
	 * @return checkpoint
	 */
	virtual Checkpoint *GetCheckpoint(int i);
	/**
	 * @return total number of racers
	 */
	virtual int GetNumRacers();
	/**
	 * @return total number of laps
	 */
	virtual int GetNumLaps();
	/**
	 * @return total number of checkpoints
	 */
	virtual int GetNumCheckpoints();
protected:
	/**
	 * Number of laps required to finish.
	 */
	int totalLaps;
	/**
	 * The checkpoints, in race order.
	 */
	std::vector<Checkpoint *> checkpoints;
	/**
	 * All the racers.
	 */
	std::vector<Racer *> racers;
	/**
	 * Stores data about racers.
	 */
	std::map<Racer *, RacerData> racerData;
};