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

	
	
	GetWeaponConfig(pLocal);

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

	if (!C::Get<bool>(Vars.bAimSilent))
		I::Engine->SetViewAngles(pCmd->angViewPoint);
	
}

void CLegitBot::GoToTarget(CUserCmd* pCmd, CBaseEntity* pLocal)
{
	
	auto weapont = pLocal->GetWeapon();
	if (m_Target == -1 || weapont->GetAmmo() == 0 || !pLocal->IsAlive())
		return;

	if (pLocal->GetShotsFired() != 0 && oneshot == 1)
		return;

	CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(m_Target);
	auto Local_Pos = pLocal->GetEyePosition();
	Vector EnemyBonePos;

	if (NBone)
	{
		R_Bone = get_best_bone(pLocal, pEntity, pCmd);
	}

	EnemyBonePos = *pEntity->GetBonePosition(R_Bone);
	auto EnemyAngle = M::CalcAngle(Local_Pos, EnemyBonePos);
	
	auto CurrentAngle = pCmd->angViewPoint;

		if (pLocal->GetShotsFired() > 1)
		{
			QAngle aimPunch = pLocal->GetPunch();
			EnemyAngle.x -= aimPunch.x * 2.0f;
			EnemyAngle.y -= aimPunch.y * 2.0f;
		}
	

	if (CLegitBot::CalcFov(EnemyAngle, CurrentAngle) < fov)
	{
		
		if (smooth > 0)
		{
			SmoothAngleSet(EnemyAngle, CurrentAngle, pCmd);
		}
		else
		{
			EnemyAngle.Normalize();
			EnemyAngle.Clamp();
			pCmd->angViewPoint = EnemyAngle;
			if (!C::Get<bool>(Vars.bAimSilent))
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

		if (pEntity == nullptr || pEntity == fLocal || pEntity->IsDormant() || !pEntity->IsAlive() || i == fLocal->GetIndex())
			continue;

		if (C::Get<bool>(Vars.iAimTeam))
		{
			if (!fLocal->IsEnemy(pEntity))
				continue;
		}
		
		auto Local_Pos = fLocal->GetEyePosition();
		Vector EnemyBonePos;
		if (NBone)
		{
			R_Bone = get_best_bone(fLocal, pEntity, fCmd);
		}

		EnemyBonePos = *pEntity->GetBonePosition(R_Bone);
		auto EnemyAngle = M::CalcAngle(Local_Pos, EnemyBonePos);
		auto CurrentAngle = fCmd->angViewPoint;

			if (fLocal->GetShotsFired() > 1)
			{
				QAngle aimPunch = fLocal->GetPunch();
				CurrentAngle.x += aimPunch.x * 2.0f;
				CurrentAngle.y += aimPunch.y * 2.0f;
			}


		if (C::Get<bool>(Vars.bAimAutoWall) && !fLocal->IsVisible(pEntity, pEntity->GetBonePosition(R_Bone).value_or(pEntity->GetEyePosition(false))))
		{
			continue;
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

	QAngle delta = angle - playerAngle;
	delta.Normalize();

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}



int CLegitBot::get_best_bone(CBaseEntity* pLocal, CBaseEntity* pEntity, CUserCmd* pCmd)
{

	auto Local_Pos = pLocal->GetEyePosition();
	Vector EnemyBonePos;

	int bestbone = 0;
	float bestfov = 9999.0f;

	for (int i = 1; i <= 6; i++)
	{
		
		switch (i)
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
			case 4:
			{
				EnemyBonePos = *pEntity->GetBonePosition(BONE_SPINE_2);
				break;
			}
			case 5:
			{
				EnemyBonePos = *pEntity->GetBonePosition(BONE_SPINE_1);
				break;
			}
			case 6:
			{
				EnemyBonePos = *pEntity->GetBonePosition(BONE_PELVIS);
				break;
			}
			default:
			{
				EnemyBonePos = *pEntity->GetBonePosition(BONE_HEAD);
				break;
			}
		}


		auto EnemyAngle = M::CalcAngle(Local_Pos, EnemyBonePos);

		if (pLocal->GetShotsFired() > 1)
		{
			QAngle aimPunch = pLocal->GetPunch();
			EnemyAngle.x -= aimPunch.x * 2.0f;
			EnemyAngle.y -= aimPunch.y * 2.0f;
		}
		auto CurrentAngle = pCmd->angViewPoint;

		float tmp = CLegitBot::CalcFov(EnemyAngle, CurrentAngle);
		
		if (tmp < fov)
		{
			if (tmp < bestfov)
			{
				bestfov = tmp;
				bestbone = i;
			}
		}

	}
	//printf("\nbest bone %d", bestbone);
	switch (bestbone)
	{
	case 1:
	{

		return BONE_HEAD;
		break;
	}
	case 2:
	{
		return BONE_NECK;
		break;
	}
	case 3:
	{
		return BONE_SPINE_3;
		break;
	}
	case 4:
	{
		return BONE_SPINE_2;
		break;
	}
	case 5:
	{
		return BONE_SPINE_1;
		break;
	}
	case 6:
	{
		return BONE_PELVIS;
		break;
	}
	default:
	{
		return BONE_HEAD;
		break;
	}
	}

}

void CLegitBot::GetWeaponConfig(CBaseEntity* pLocal)
{
	CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

	if (pWeapon == nullptr)
		return;

	short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

	// check is weapon gun
	if (pWeaponData == nullptr)
		return;

	

switch (pWeaponData->nWeaponType)
{
case WEAPONTYPE_PISTOL:
	weapontype = 1;
	fov = C::Get<float>(Vars.iPAimFov);
	smooth = C::Get<int>(Vars.iPAimSmooth);
	oneshot = C::Get<bool>(Vars.bPOneShot);
	Aim_Bone = C::Get<int>(Vars.iPBone);
	NBone = C::Get<bool>(Vars.bPAimNBone);

	break;
case WEAPONTYPE_SUBMACHINEGUN:
	weapontype = 2;
	fov = C::Get<float>(Vars.iSMGAimFov);
	smooth = C::Get<int>(Vars.iSMGAimSmooth);
	oneshot = C::Get<bool>(Vars.bSMGOneShot);
	Aim_Bone = C::Get<int>(Vars.iSMGBone);
	NBone = C::Get<bool>(Vars.bSMGAimNBone);
	break;
case WEAPONTYPE_RIFLE:
	weapontype = 3;
	fov = C::Get<float>(Vars.iRAimFov);
	smooth = C::Get<int>(Vars.iRAimSmooth);
	oneshot = C::Get<bool>(Vars.bROneShot);
	Aim_Bone = C::Get<int>(Vars.iRBone);
	NBone = C::Get<bool>(Vars.bRAimNBone);
	break;
case WEAPONTYPE_SHOTGUN:
	weapontype = 4;
	fov = C::Get<float>(Vars.iSHAimFov);
	smooth = C::Get<int>(Vars.iSHAimSmooth);
	oneshot = C::Get<bool>(Vars.bSHOneShot);
	Aim_Bone = C::Get<int>(Vars.iSHBone);
	NBone = C::Get<bool>(Vars.bSHAimNBone);
	break;
case WEAPONTYPE_SNIPER:
	switch (nDefinitionIndex)
	{
	case 9:
	{
		weapontype = 5;
		fov = C::Get<float>(Vars.iAWPAimFov);
		smooth = C::Get<int>(Vars.iAWPAimSmooth);
		oneshot = C::Get<bool>(Vars.bAWPOneShot);
		Aim_Bone = C::Get<int>(Vars.iAWPBone);
		NBone = C::Get<bool>(Vars.bAWPAimNBone);
		break;
	}
	case 40:
	{
		weapontype = 5;
		fov = C::Get<float>(Vars.iSCOUTAimFov);
		smooth = C::Get<int>(Vars.iSCOUTAimSmooth);
		oneshot = C::Get<bool>(Vars.bSCOUTOneShot);
		Aim_Bone = C::Get<int>(Vars.iSCOUTBone);
		NBone = C::Get<bool>(Vars.bSCOUTAimNBone);
		break;
	}
	case (11 || 38):
	{
		weapontype = 5;
		fov = C::Get<float>(Vars.iAUTOAimFov);
		smooth = C::Get<int>(Vars.iAUTOAimSmooth);
		oneshot = C::Get<bool>(Vars.bAUTOOneShot);
		Aim_Bone = C::Get<int>(Vars.iAUTOBone);
		NBone = C::Get<bool>(Vars.bAUTOAimNBone);
		break;
	}
	default:
	{
		weapontype = 5;
		fov = C::Get<float>(Vars.iSAimFov);
		smooth = C::Get<int>(Vars.iSAimSmooth);
		oneshot = C::Get<bool>(Vars.bSOneShot);
		Aim_Bone = C::Get<int>(Vars.iSBone);
		NBone = C::Get<bool>(Vars.bSAimNBone);
		break;
	}
	}
	break;
case WEAPONTYPE_MACHINEGUN:
	weapontype = 6;
	fov = C::Get<float>(Vars.iMAimFov);
	smooth = C::Get<int>(Vars.iMAimSmooth);
	oneshot = C::Get<bool>(Vars.bMAOneShot);
	Aim_Bone = C::Get<int>(Vars.iMABone);
	NBone = C::Get<bool>(Vars.bMAAimNBone);
	break;

default:
	weapontype = 7;
	fov = C::Get<float>(Vars.iAimFov);
	smooth = C::Get<int>(Vars.iAimSmooth);
	oneshot = C::Get<bool>(Vars.bOneShot);
	Aim_Bone = C::Get<int>(Vars.iBone);
	NBone = C::Get<bool>(Vars.bAimNBone);
	break;
}
SortBone();


}

void CLegitBot::SortBone()
{
	switch (Aim_Bone)
	{
	case 0:
	{
		R_Bone = BONE_HEAD;
		break;
	}
	case 1:
	{
		R_Bone = BONE_NECK;
		break;
	}
	case 2:
	{
		R_Bone = BONE_SPINE_3;
		break;
	}
	default:
	{
		R_Bone = BONE_HEAD;
		break;
	}
	}
}

