#pragma once
// used: winapi includes, singleton
#include "../common.h"
// used: usercmd
#include "../sdk/datatypes/usercmd.h"
// used: baseentity
#include "../sdk/entity.h"

#include "../utilities/math.h"

// @note: FYI - https://www.unknowncheats.me/forum/counterstrike-global-offensive/137492-math-behind-hack-1-coding-better-aimbot-stop-using-calcangle.html

class CBlockBot : public CSingleton<CBlockBot>
{
public:
	// Get
	void Run(CUserCmd* pCmd, CBaseEntity* pLocal);
	bool IsValid(int i);
	void GoToTarget(CUserCmd* pCmd, CBaseEntity* pLocal);
	int b_Target;
	float b_Best;
	void FindBlockbot(CBaseEntity* pLocal, CUserCmd* pCmd);
	void DropBBOT();
	Vector BCalcAngle(QAngle src, Vector dst);

		float BCalcFov(Vector angle, Vector playerAngle);
private:
	// Main


	// Check
	//is entity valid
};
