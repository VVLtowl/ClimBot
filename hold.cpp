#include "texture.h"
#include "sprite.h"
#include "camera.h"

//#include "swinger.h"
//#include "clock_block.h"
#include "hold.h"
#include <vector>
#include "player.h"

using std::vector;

std::vector<Hold*> list_hold;
Hold *pHoldCheckpoint;

void InitHold()
{
	list_hold.clear();
}

void UninitHold()
{
}

void UpdateHold()
{
	for (int i = 0; i < list_hold.size(); i++)
	{
		Hold* pHold = list_hold[i];

		pHold->Update();
	}
}

void DrawHold()
{
	for (int i = 0; i < list_hold.size(); i++)
	{
		Hold* pHold = list_hold[i];

		pHold->Draw();
	}
}

void AddHold(Hold* pHold)
{
	list_hold.emplace_back(pHold);
	MyLog("new hold:%.1lf:%.1lf , %d\n",
		pHold->gameObject.transform.position.x,
		pHold->gameObject.transform.position.y,
		pHold->gameObject.p_displays[0].texNo);
}

void SetCheckpointHold(Hold* pHold)
{
	pHoldCheckpoint = pHold;
}

Hold *GetCheckpointHold()
{
	return pHoldCheckpoint;
}

vector<Hold*> GetHold()
{
	return list_hold;
}

//edit by fujita
void Hold_Collapse::Update()
{
	switch (state)
	{
	case collapse_use:
		//player‚ÅƒJƒEƒ“ƒg‚·‚é
		if (count > 40)//Œx‚É“ü‚é
		{
			this->state = collapse_warning;
			this->gameObject.p_displays->animeID = 1;
		}
		break;
	case collapse_warning:
		//player‚Å
		break;
	case collapse_break:
		count++;
		break;
	case collapse_wait:
		count++;
		break;
	}

	//isCatchedCount++;
	if (count > 40)//Œx‚É“ü‚é
	{
		this->gameObject.p_displays->animeID = 1;
	}
	if (count > 180) //•ö‚ê‚É“ü‚é
	{
		isCollapsing = true;
		this->gameObject.p_displays->animeID = 2;
		count++;
	}
	if (count > 20)
	{
		isCollapsing = false;
		isUse = false;
	}
	if (count > 160) {
		isUse = true;
		//isBreaking = false;
		isCatchedCount = 0;
		count = 0;
		this->gameObject.p_displays->animeID = 0;
	}
	gameObject.Update();
}

