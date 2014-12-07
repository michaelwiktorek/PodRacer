#include "Race.h"


Race::Race()
{
	totalLaps = 3;
	AddCheckpoint(new Checkpoint(0, 0, 50));
	AddCheckpoint(new Checkpoint(-100, 200, 50));
	AddCheckpoint(new Checkpoint(350, 350, 50));
	AddCheckpoint(new Checkpoint(500, -100, 50));
}

void Race::AddCheckpoint(Checkpoint *checkpoint)
{
	checkpoints.push_back(checkpoint);
	theWorld.Add(checkpoint);
}

void Race::AddRacer(Racer *racer)
{
	racers.push_back(racer);
	racerData[racer] = RacerData();
	theWorld.Add(racer);
}

int Race::GetLap(Racer *racer)
{
	return racerData.at(racer).lap;
}

int Race::GetCheckpointNum(Racer *racer)
{
	return racerData.at(racer).checkpoint;
}


Checkpoint *Race::GetCheckpoint(int i)
{
	return checkpoints.at(i % checkpoints.size());
}

Checkpoint *Race::GetCheckpoint(Racer *racer)
{
	return GetCheckpoint(racer, 0);
}

Checkpoint *Race::GetCheckpoint(Racer *racer, int i)
{
	return GetCheckpoint(GetCheckpointNum(racer) + i);
}

int Race::GetPlace(Racer *racer)
{
	for (int i = 0; i < racers.size(); i++)
	{
		if (racers.at(i) == racer)
		{
			return i;
		}
	}
	return -1;
}

int Race::GetNumRacers()
{
	return racers.size();
}

int Race::GetNumCheckpoints()
{
	return checkpoints.size();
}

int Race::GetNumLaps()
{
	return totalLaps;
}

void Race::Update(float dt)
{
	for (Racer *racer : racers)
	{
		RacerData &data = racerData.at(racer);
		Checkpoint *checkpoint = checkpoints[data.checkpoint];
		float distance = (checkpoint->GetPosition() - racer->pod->GetPosition()).Length();
		if (distance < checkpoint->width / 2)
		{
			std::cout << racer->GetName() << " reached checkpoint: " << data.checkpoint << "\n";
			data.checkpoint++;
			if (data.checkpoint >= checkpoints.size())
			{
				std::cout << racer->GetName() << " completed lap: " << data.lap << "\n";
				data.lap++;
				data.checkpoint = 0;
			}
		}
	}
}

void Race::Render()
{
	Color c = Color(0, 0, 1, 0.5);
	for (int i = 0; i < checkpoints.size(); i++)
	{
		drawLine(checkpoints[i]->GetPosition(), checkpoints[(i + 1) % checkpoints.size()]->GetPosition() , c, 2.0);
	}
}