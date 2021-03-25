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
	int b_Target = -20;
	float b_Best;
	int FindBlockbot(CBaseEntity* pLocal, CUserCmd* pCmd);
	void DropBBOT();
	void RunCrosshair(CUserCmd* pCmd, CBaseEntity* pLocal);

	void RunOldschool(CUserCmd* pCmd, CBaseEntity* pLocal);

	Vector BCalcAngle(QAngle src, Vector dst);
	void MoveC(CUserCmd* pCmd, const QAngle& angOldViewPoint) const;

		float BCalcFov(Vector angle, Vector playerAngle);
private:
	// Main


	// Check
	//is entity valid
};
