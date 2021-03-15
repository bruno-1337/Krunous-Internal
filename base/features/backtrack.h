#pragma once
// used: winapi includes, singleton
#include "../common.h"
// used: usercmd
#include "../sdk/datatypes/usercmd.h"
// used: baseentity
#include "../sdk/entity.h"

#include "../utilities/math.h"


#include <deque>
#define NUM_OF_TICKS 13

struct stored_records
{
	Vector head;
	float simulation_time;
	matrix3x3_t matrix[128];
};
struct StoredData
{
	float simtime;
	Vector hitboxPos;
};

class CBacktrack : public CSingleton<CBacktrack>
{
	int nLatestTick;
public:
	// Get
	StoredData TimeWarpData[64][NUM_OF_TICKS];
	void Run(CUserCmd* pCmd, CBaseEntity* pLocal);
	bool valid_tick(float simtime);

	float get_lerp_time();
	bool IsValid(int i);
	void GoToTarget(CUserCmd* pCmd, CBaseEntity* pLocal);
	int b_Target;
	float b_Best;
	void FindBlockbot(CBaseEntity* pLocal, CUserCmd* pCmd);
	void DropBBOT();
	void RunCrosshair(CUserCmd* pCmd, CBaseEntity* pLocal);
	float BCalcFov(QAngle angle, QAngle playerAngle);

	void RunOldschool(CUserCmd* pCmd, CBaseEntity* pLocal);

	Vector BCalcAngle(QAngle src, Vector dst);
	void MoveC(CUserCmd* pCmd, const QAngle& angOldViewPoint) const;

	float BCalcFov(Vector angle, Vector playerAngle);
private:
	// Main


	// Check
	//is entity valid
};