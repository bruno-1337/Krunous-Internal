#include "backtrack.h"
// used: cheat variables
#include "../core/variables.h"
// used: main window open state
#include "../core/menu.h"
// used: key state
#include "../utilities/inputsystem.h"
// used: globals, cliententitylist interfaces
#include "../core/interfaces.h"
// used: backtracking
#include "lagcompensation.h"

#include "autowall.h"

#include "..\utilities\math.h"

#define TICK_INTERVAL			(I::Globals->flIntervalPerTick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

void CBacktrack::Run(CUserCmd* cmd, CBaseEntity* pLocal)
{
	int bestTargetIndex = -1;
	float bestFov = FLT_MAX;

	if (!pLocal->IsAlive())
		return;

	for (int i = 1; i < I::Globals->nMaxClients; i++)
	{
		CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(i);
		if (pEntity == nullptr || pEntity == pLocal || pEntity->IsDormant() || !pEntity->IsAlive() || i == pLocal->GetIndex())
			continue;

		float simtime = pEntity->GetSimulationTime();
		Vector hitboxPos = *pEntity->GetBonePosition(BONE_HEAD);

		auto EnemyAngle = M::CalcAngle(pLocal->GetEyePosition(), hitboxPos);
		auto CurrentAngle = *pLocal->GetViewAngles();
		if (pLocal->GetShotsFired() > 1)
		{
			QAngle aimPunch = pLocal->GetPunch();
			CurrentAngle.x += aimPunch.x * 2.0f;
			CurrentAngle.y += aimPunch.y * 2.0f;
		}

		TimeWarpData[i][cmd->iCommandNumber % (static_cast<int>(NUM_OF_TICKS) + 1)] = StoredData{ simtime, hitboxPos };
		Vector ViewDir;
		float tmp = BCalcFov(EnemyAngle, CurrentAngle);

		if (bestFov > tmp)
		{
			bestFov = tmp;
			bestTargetIndex = i;
		}
	}

	float bestTargetSimTime = -1;
	if (bestTargetIndex != -1)
	{
		float tempFloat = FLT_MAX;
		auto ViewDir = *pLocal->GetViewAngles();
		if (pLocal->GetShotsFired() > 1)
		{
			QAngle aimPunch = pLocal->GetPunch();
			ViewDir.x += aimPunch.x * 2.0f;
			ViewDir.y += aimPunch.y * 2.0f;
		}

		for (int t = 0; t < static_cast<int>(C::Get<int>(Vars.iMiscBacktrackTicks)); ++t)
		{
			float tempFOVDistance = BCalcFov(M::CalcAngle(pLocal->GetEyePosition(), TimeWarpData[bestTargetIndex][t].hitboxPos), cmd->angViewPoint);

			if (tempFloat > tempFOVDistance && TimeWarpData[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
			{
				CBaseEntity* besttarget = I::ClientEntityList->Get<CBaseEntity>(bestTargetIndex);
				
				if (pLocal->IsVisible(besttarget, TimeWarpData[bestTargetIndex][t].hitboxPos))
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = TimeWarpData[bestTargetIndex][t].simtime;
				}
			}
		}

		if (bestTargetSimTime >= 0 && cmd->iButtons & IN_ATTACK)
			cmd->iTickCount = TIME_TO_TICKS(bestTargetSimTime);
	}
}

float CBacktrack::BCalcFov(QAngle angle, QAngle playerAngle)
{


	QAngle delta = angle - playerAngle;
	delta.Normalize();

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}