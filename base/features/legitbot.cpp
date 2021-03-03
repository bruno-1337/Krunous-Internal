#include "legitbot.h"

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


void CLegitBot::Run(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket)
{
	
	if (!pLocal->IsAlive())
		return;

	CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

	if (pWeapon == nullptr)
		return;

	// disable when in-menu for more legit (lol)
	if (W::bMainOpened)
		return;



	

	if (C::Get<int>(Vars.iAimKey) > 0 && !IPT::IsKeyDown(C::Get<int>(Vars.iAimKey))) //check for aimkey
	{
		return;
	}

	
	FindTarget(pLocal, pCmd);
	GoToTarget(pCmd, pLocal);

	

}
void CLegitBot::SmoothAngleSet(QAngle dest, QAngle orig)
{
	QAngle vecDelta = dest;

	vecDelta -= orig;

	vecDelta.Normalize();
	vecDelta.Clamp();
	orig+= vecDelta / (1.f * smooth);

	orig.Normalize();
	orig.Clamp();
	I::Engine->SetViewAngles(orig);
}

void CLegitBot::GoToTarget(CUserCmd* pCmd, CBaseEntity* pLocal)
{
	
	
	if (m_Target == -1)
		return;

	


	CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(m_Target);
	auto Local_Pos = pLocal->GetEyePosition();
	Vector EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
	auto EnemyAngle = M::CalcAngle(Local_Pos, EnemyBonePos);
	auto CurrentAngle = pCmd->angViewPoint;

	fov = C::Get<int>(Vars.iAimFov);
	smooth = C::Get<int>(Vars.iAimSmooth);

	if (C::Get<bool>(Vars.bMiscWeaponConfig))
		GetWeaponConfig(pLocal);

	if (CLegitBot::CalcFov(EnemyAngle, CurrentAngle) < fov)
	{
		if (pLocal->GetShotsFired() > 1)
		{
			QAngle aimPunch = pLocal->GetPunch();
			EnemyAngle.x -= aimPunch.x * 2.0f;
			EnemyAngle.y -= aimPunch.y * 2.0f;
		}

		if (smooth > 0)
		{
			SmoothAngleSet(EnemyAngle, CurrentAngle);
		}
		else
		{
			EnemyAngle.Normalize();
			EnemyAngle.Clamp();
			I::Engine->SetViewAngles(EnemyAngle);
		}
	}

}

void CLegitBot::DropTarget(void)
{
	m_Target = -1;
	m_Best = 9999.0f;
}

void CLegitBot::FindTarget(CBaseEntity* fLocal, CUserCmd* fCmd)
{
	DropTarget();
	float tmp;

	for (int i = 1; i <= I::Globals->nMaxClients; i++)
	{
		CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(i);

		if (pEntity == nullptr || !pEntity->IsPlayer() || pEntity->IsDormant() || !pEntity->IsAlive() || i == fLocal->GetIndex())
			continue;

		
		auto Local_Pos = fLocal->GetEyePosition();
		Vector EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
		auto EnemyAngle = M::CalcAngle(Local_Pos, EnemyBonePos);
		auto CurrentAngle = fCmd->angViewPoint;
		tmp = CalcFov(EnemyAngle, CurrentAngle);
		if (tmp < m_Best)
		{
			m_Best = tmp;
			m_Target = i;
		}
	}
}

float CLegitBot::CalcFov(QAngle angle, QAngle playerAngle)
{
	float fov = sqrt(pow(angle.x - playerAngle.x, 2) + pow(angle.y - playerAngle.y, 2));
	if (fov > 180)
	{
		return abs(360.f - fov);
	}
	return fov;
}


void CLegitBot::GetWeaponConfig(CBaseEntity* pLocal)
{
	CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

	if (pWeapon == nullptr)
		return;

	short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

	// check is weapon gun
	if (pWeaponData == nullptr || !pWeaponData->IsGun())
		return;

	

switch (pWeaponData->nWeaponType)
{
case WEAPONTYPE_PISTOL:
	fov = C::Get<int>(Vars.iPAimFov);
	smooth = C::Get<int>(Vars.iPAimSmooth);
	break;
case WEAPONTYPE_SUBMACHINEGUN:
	fov = C::Get<int>(Vars.iSMGAimFov);
	smooth = C::Get<int>(Vars.iSMGAimSmooth);
	break;
case WEAPONTYPE_RIFLE:
	fov = C::Get<int>(Vars.iRAimFov);
	smooth = C::Get<int>(Vars.iRAimSmooth);
	break;
case WEAPONTYPE_SHOTGUN:
	fov = C::Get<int>(Vars.iSHAimFov);
	smooth = C::Get<int>(Vars.iSHAimSmooth);
	break;
case WEAPONTYPE_SNIPER:
	fov = C::Get<int>(Vars.iSAimFov);
	smooth = C::Get<int>(Vars.iSAimSmooth);
	break;
case WEAPONTYPE_MACHINEGUN:
	fov = C::Get<int>(Vars.iMAimFov);
	smooth = C::Get<int>(Vars.iMAimSmooth);
	break;
default:
	fov = 0;
	smooth = 0;
	break;
}
}