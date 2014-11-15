#pragma once

#include "stdafx.h"
#include <string>

#define theGameManager PodGameManager::GetInstance()

class PodGameManager : public GameManager
{
public:
	static PodGameManager &GetInstance();
	virtual void Render();
	virtual void Update(float dt);
	virtual void ReceiveMessage(Message *message);
protected:
	PodGameManager();
	static PodGameManager *instance;
};
