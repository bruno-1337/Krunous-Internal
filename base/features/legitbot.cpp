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

#include "autowall.h"


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
void CLegitBot::SmoothAngleSet(QAngle dest, QAngle orig, CUserCmd* pCmd)
{
	QAngle vecDelta = dest;

	vecDelta -= orig;

	vecDelta.Normalize();
	vecDelta.Clamp();
	orig+= vecDelta / (1.f * smooth);

	orig.Normalize();
	orig.Clamp();
	pCmd->angViewPoint = orig;
	I::Engine->SetViewAngles(pCmd->angViewPoint);
}

void CLegitBot::GoToTarget(CUserCmd* pCmd, CBaseEntity* pLocal)
{
	
	
	if (m_Target == -1)
		return;

	


	CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(m_Target);
	auto Local_Pos = pLocal->GetEyePosition();
	Vector EnemyBonePos;
	switch (Aim_Bone)
	{
	case 1:
	{
		EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
		break;
	}
	case 2:
	{
		EnemyBonePos = *pEntity->GetBonePosition(BONE_NECK);
		break;
	}
	case 3:
	{
		EnemyBonePos = *pEntity->GetBonePosition(BONE_SPINE_3);
		break;
	}
	default:
	{
		EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
		break;
	}
	}
	
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
			if (oneshot)
			{
				return;
			}

			QAngle aimPunch = pLocal->GetPunch();
			EnemyAngle.x -= aimPunch.x * 2.0f;
			EnemyAngle.y -= aimPunch.y * 2.0f;
		}
		if (smooth > 0)
		{
			SmoothAngleSet(EnemyAngle, CurrentAngle, pCmd);
		}
		else
		{
			EnemyAngle.Normalize();
			EnemyAngle.Clamp();
			pCmd->angViewPoint = EnemyAngle;
			I::Engine->SetViewAngles(pCmd->angViewPoint);
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

		if (C::Get<bool>(Vars.iAimTeam))
		{
			if (!pEntity->IsEnemy(fLocal))
				continue;
		}

		
		auto Local_Pos = fLocal->GetEyePosition();
		Vector EnemyBonePos;
		switch (Aim_Bone)
		{
		case 1:
		{
			EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
			break;
		}
		case 2:
		{
			EnemyBonePos = *pEntity->GetBonePosition(BONE_NECK);
			break;
		}
		case 3:
		{
			EnemyBonePos = *pEntity->GetBonePosition(BONE_SPINE_3);
			break;
		}
		default:
		{
			EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
			break;
		}
		}

		auto EnemyAngle = M::CalcAngle(Local_Pos, EnemyBonePos);
		auto CurrentAngle = fCmd->angViewPoint;

		if (C::Get<bool>(Vars.bAimAutoWall))
		{
			static CConVar* weapon_recoil_scale = I::ConVar->FindVar(XorStr("weapon_recoil_scale"));

			if (weapon_recoil_scale == nullptr)
				continue;

			CBaseCombatWeapon* pWeapon = fLocal->GetWeapon();

			if (pWeapon == nullptr)
				continue;

			short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
			CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);
			QAngle angView = EnemyAngle;
			Vector vecStart, vecEnd, vecForward;
			M::AngleVectors(angView, &vecForward);
			vecStart = fLocal->GetEyePosition();
			vecForward *= pWeaponData->flRange;
			vecEnd = vecStart + vecForward;


			Trace_t trace = { };
			Ray_t ray(vecStart, vecEnd);
			CTraceFilter filter(fLocal);
			I::EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
			CBaseEntity* AEntity = trace.pHitEntity;
			if ((C::Get<bool>(Vars.bAimHead) && trace.iHitGroup == HITGROUP_HEAD) ||
				// chest
				(C::Get<bool>(Vars.bAimChest) && trace.iHitGroup == HITGROUP_CHEST) ||
				// stomach
				(C::Get<bool>(Vars.bAimStomach) && trace.iHitGroup == HITGROUP_STOMACH) ||
				// arms
				(C::Get<bool>(Vars.bAimArms) && (trace.iHitGroup == HITGROUP_LEFTARM || trace.iHitGroup == HITGROUP_RIGHTARM)) ||
				// legs
				(C::Get<bool>(Vars.bAimLegs) && (trace.iHitGroup == HITGROUP_LEFTLEG || trace.iHitGroup == HITGROUP_RIGHTLEG)))
			{
				//nice
			}
			else continue;


		}
		

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
	weapontype = 1;
	fov = C::Get<int>(Vars.iPAimFov);
	smooth = C::Get<int>(Vars.iPAimSmooth);
	oneshot = C::Get<bool>(Vars.bPOneShot);
	Aim_Bone = C::Get<int>(Vars.iPBone);
	break;
case WEAPONTYPE_SUBMACHINEGUN:
	weapontype = 2;
	fov = C::Get<int>(Vars.iSMGAimFov);
	smooth = C::Get<int>(Vars.iSMGAimSmooth);
	oneshot = C::Get<bool>(Vars.bSMGOneShot);
	Aim_Bone = C::Get<int>(Vars.iSMGBone);
	break;
case WEAPONTYPE_RIFLE:
	weapontype = 3;
	fov = C::Get<int>(Vars.iRAimFov);
	smooth = C::Get<int>(Vars.iRAimSmooth);
	oneshot = C::Get<bool>(Vars.bROneShot);
	Aim_Bone = C::Get<int>(Vars.iRBone);
	break;
case WEAPONTYPE_SHOTGUN:
	weapontype = 4;
	fov = C::Get<int>(Vars.iSHAimFov);
	smooth = C::Get<int>(Vars.iSHAimSmooth);
	oneshot = C::Get<bool>(Vars.bSHOneShot);
	Aim_Bone = C::Get<int>(Vars.iSHBone);
	break;
case WEAPONTYPE_SNIPER:
	weapontype = 5;
	fov = C::Get<int>(Vars.iSAimFov);
	smooth = C::Get<int>(Vars.iSAimSmooth);
	oneshot = C::Get<bool>(Vars.bSOneShot);
	Aim_Bone = C::Get<int>(Vars.iSBone);
	break;
case WEAPONTYPE_MACHINEGUN:
	weapontype = 6;
	fov = C::Get<int>(Vars.iMAimFov);
	smooth = C::Get<int>(Vars.iMAimSmooth);
	oneshot = C::Get<bool>(Vars.bMAOneShot);
	Aim_Bone = C::Get<int>(Vars.iMABone);
	break;
default:
	Aim_Bone = 7;
	weapontype = 7;
	fov = 0;
	smooth = 0;
	oneshot = 0;
	break;
}
}

