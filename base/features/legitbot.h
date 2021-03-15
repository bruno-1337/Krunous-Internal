#pragma once
// used: winapi includes, singleton
#include "../common.h"
// used: usercmd
#include "../sdk/datatypes/usercmd.h"
// used: baseentity
#include "../sdk/entity.h"

#include "../utilities/math.h"

// @note: FYI - https://www.unknowncheats.me/forum/counterstrike-global-offensive/137492-math-behind-hack-1-coding-better-aimbot-stop-using-calcangle.html

class CLegitBot : public CSingleton<CLegitBot>
{
public:
	// Get
	void Run(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket);
	void FindTarget(CBaseEntity* fLocal, CUserCmd* fCmd);
	bool IsValid(int i);
	void DropTarget();
	void GoToTarget(CUserCmd* pCmd, CBaseEntity* pLocal);
	int m_Target;
	float m_Best;
	void RCS(CUserCmd* pCmd, CBaseEntity* pLocal);
	void SmoothAngleSet(QAngle dest, QAngle orig, CUserCmd* pCmd);
	QAngle rcs_old_punch = { 0.0f, 0.0f, 0.0f };
	void GetWeaponConfig(CBaseEntity* pLocal);
	float fov;
	int smooth;
	bool NBone;
	bool oneshot;
	int R_Bone;
	int Aim_Bone;
	void SortBone();
	int weapontype;
	EBoneIndex GetBone();
	int get_best_bone(CBaseEntity* pLocal, CBaseEntity* pEntity, CUserCmd* pCmd);

	

	float CalcFov(QAngle angle, QAngle playerAngle);
private:
	// Main
	/* aimbot, smooth, etc */
	

	// Check
	/* is entity valid */
};
