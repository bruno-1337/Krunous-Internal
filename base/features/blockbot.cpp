
#include "blockbot.h"

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

void CBlockBot::Run(CUserCmd* pCmd, CBaseEntity* pLocal)
{
	CBaseEntity* morone = nullptr;

	if (b_Target == -20)
	{
		b_Target = FindBlockbot(pLocal, pCmd);
	}

	morone = I::ClientEntityList->Get<CBaseEntity>(b_Target);

	if (!IPT::IsKeyDown(C::Get<int>(Vars.iBlockBotKey)) || morone == nullptr || !morone->IsAlive() || morone->IsDormant() || b_Target == pLocal->GetIndex())
	{
		b_Target = FindBlockbot(pLocal, pCmd);
	}
	else
	switch (C::Get<int>(Vars.iMiscBlockBot))
	{
	case 0:
		break;
	case 1:
		RunCrosshair(pCmd, pLocal);
		break;
	case 2:
		RunOldschool(pCmd, pLocal);
		break;
	}
}
void CBlockBot::RunCrosshair(CUserCmd* pCmd, CBaseEntity* pLocal)
{
	if (C::Get<int>(Vars.iBlockBotKey) == 0 || !IPT::IsKeyDown(C::Get<int>(Vars.iBlockBotKey))) //check for aimkey
	{
		return;
	}

	if (pCmd->flSideMove != 0 || pCmd->flForwardMove != 0)
		return;


	CBaseEntity* closest_teammate = nullptr;

	if (!pLocal || !pLocal->IsAlive())
		return;

	//Only target teammates within 245 units
	float dist = 245.f;
	for (int i = 0; i < I::Globals->nMaxClients; i++) 
	{
		CBaseEntity* current_ent = I::ClientEntityList->Get<CBaseEntity>(i);

		if (!current_ent || current_ent == pLocal)
			continue;

		if (!current_ent->IsAlive() || current_ent->IsDormant())
			continue;

		float current_dist = pLocal->GetOrigin().DistTo(current_ent->GetOrigin());
		if (current_dist < dist) 
		{
			dist = current_dist;
			closest_teammate = current_ent;
		}
	}

	//Do we have a teammate we can block?
	if (!closest_teammate)
		return;

	//Distance we want to keep from the player
	float radius = 45.f;

	static auto pi = std::atan(1) * 4;
	auto target_origin = closest_teammate->GetOrigin();
	auto target_view = closest_teammate->GetViewAngles()->Normalize().y;

	//Normalize the view to 0-360°
	if (target_view < 0.f)
		target_view += 360.f;

	//Get the sin of our view in radians (used for y position)
	auto sin_view = sin(target_view / 180.f * pi);

	//Get the lenght of the adjacent side
	auto delta_x = sqrt(1 - sin_view * sin_view) * radius;

	/*
		Because a square root can be +- something, we need to account for negative values
		Don't know why but we need to negate the distance between 90° and 270°
	*/
	if (target_view > 90.f && target_view < 270.f)
		delta_x = -delta_x;

	//This is our target position now
	target_origin.x += delta_x;
	target_origin.y += sin_view * radius;

	//"InTeRpOlAtE"
	target_origin += closest_teammate->GetVelocity().Length2D() * I::Globals->flIntervalPerTick;

	//Get our head position
	Vector head_pos = *pLocal->GetBonePosition(BONE_HEAD);

	//Null z pos
	auto teammate_origin = closest_teammate->GetOrigin();
	head_pos.z = teammate_origin.z = 0.f;

	//Return if we aren't close enough
	if (teammate_origin.DistTo(head_pos) > 245.f)
		return;

	//Move towards our point
	auto dist_x = head_pos.x - target_origin.x;
	auto dist_y = head_pos.y - target_origin.y;

	pCmd->flSideMove = dist_x > 0 ? 450.f : -450.f;
	pCmd->flForwardMove = dist_y > 0 ? 450.f : -450.f;

	//Fix our movement (we applied it from a y = -90 perspective-
	//				   Old angles, Current cmd
	MoveC(pCmd, QAngle(0, -90, 0));
}

void CBlockBot::RunOldschool(CUserCmd* pCmd, CBaseEntity* pLocal)
{

	if (C::Get<int>(Vars.iBlockBotKey) == 0 || !IPT::IsKeyDown(C::Get<int>(Vars.iBlockBotKey))) //check for aimkey
	{
		return;
	}


	if (!pLocal->IsAlive())
		return;


	if (IPT::IsKeyDown(C::Get<int>(Vars.iBlockBotKey)))
	{
		
		bool blocked = false;

		if (b_Target == -1)
			return;

		blocked = true;
		


		CBaseEntity* target = I::ClientEntityList->Get<CBaseEntity>(b_Target);

		if ((pLocal->GetOrigin() - *target->GetBonePosition(BONE_HEAD)).Length() < 43) // head position
		{
			Vector targetOrigin = target->GetOrigin() + (target->GetVelocity().Length2D() * I::Globals->flIntervalPerTick);// *0.45f; //m_vecOrigin

			targetOrigin.z = 0;



			Vector localOrigin = pLocal->GetOrigin();
			localOrigin.z = 0;

			float distance = (targetOrigin - localOrigin).Length();
			distance *= 2.f;

			if (distance > 10)
				distance = 10;

			float angle = pCmd->angViewPoint.y - M::CalcAngle(pLocal->GetOrigin(), target->GetOrigin()).y + 360.0f;

			pCmd->flSideMove = (float)sin(angle * 0.0174533) * 45 * distance;
			pCmd->flForwardMove = (float)cos(angle * 0.0174533) * 45 * distance;

		}
		else
		{
			if (IPT::IsKeyDown(0x57))
				pCmd->flForwardMove = 450;
			else
				pCmd->flForwardMove = 0;

			auto angle = M::CalcAngle(pLocal->GetEyePosition(), target->GetOrigin());
			angle.y -= pLocal->GetViewAngles()->y;
			angle.Normalize();

			
			float sidemove = -angle.y * 25;

			pCmd->flSideMove = sidemove > 450 ? 450 : sidemove < -450 ? -450 : sidemove;
		}

	}
}



void CBlockBot::MoveC(CUserCmd* pCmd, const QAngle& angOldViewPoint) const
{
	static CConVar* cl_forwardspeed = I::ConVar->FindVar(XorStr("cl_forwardspeed"));

	if (cl_forwardspeed == nullptr)
		return;

	static CConVar* cl_sidespeed = I::ConVar->FindVar(XorStr("cl_sidespeed"));

	if (cl_sidespeed == nullptr)
		return;

	static CConVar* cl_upspeed = I::ConVar->FindVar(XorStr("cl_upspeed"));

	if (cl_upspeed == nullptr)
		return;

	// get max speed limits by convars
	const float flMaxForwardSpeed = cl_forwardspeed->GetFloat();
	const float flMaxSideSpeed = cl_sidespeed->GetFloat();
	const float flMaxUpSpeed = cl_upspeed->GetFloat();

	Vector vecForward = { }, vecRight = { }, vecUp = { };
	M::AngleVectors(angOldViewPoint, &vecForward, &vecRight, &vecUp);

	// we don't attempt on forward/right roll, and on up pitch/yaw
	vecForward.z = vecRight.z = vecUp.x = vecUp.y = 0.f;

	vecForward.NormalizeInPlace();
	vecRight.NormalizeInPlace();
	vecUp.NormalizeInPlace();

	Vector vecOldForward = { }, vecOldRight = { }, vecOldUp = { };
	M::AngleVectors(pCmd->angViewPoint, &vecOldForward, &vecOldRight, &vecOldUp);

	// we don't attempt on forward/right roll, and on up pitch/yaw
	vecOldForward.z = vecOldRight.z = vecOldUp.x = vecOldUp.y = 0.f;

	vecOldForward.NormalizeInPlace();
	vecOldRight.NormalizeInPlace();
	vecOldUp.NormalizeInPlace();

	const float flPitchForward = vecForward.x * pCmd->flForwardMove;
	const float flYawForward = vecForward.y * pCmd->flForwardMove;
	const float flPitchSide = vecRight.x * pCmd->flSideMove;
	const float flYawSide = vecRight.y * pCmd->flSideMove;
	const float flRollUp = vecUp.z * pCmd->flUpMove;

	// solve corrected movement
	const float x = vecOldForward.x * flPitchSide + vecOldForward.y * flYawSide + vecOldForward.x * flPitchForward + vecOldForward.y * flYawForward + vecOldForward.z * flRollUp;
	const float y = vecOldRight.x * flPitchSide + vecOldRight.y * flYawSide + vecOldRight.x * flPitchForward + vecOldRight.y * flYawForward + vecOldRight.z * flRollUp;
	const float z = vecOldUp.x * flYawSide + vecOldUp.y * flPitchSide + vecOldUp.x * flYawForward + vecOldUp.y * flPitchForward + vecOldUp.z * flRollUp;

	// clamp and apply corrected movement
	pCmd->flForwardMove = std::clamp(x, -flMaxForwardSpeed, flMaxForwardSpeed);
	pCmd->flSideMove = std::clamp(y, -flMaxSideSpeed, flMaxSideSpeed);
	pCmd->flUpMove = std::clamp(z, -flMaxUpSpeed, flMaxUpSpeed);
}

int CBlockBot::FindBlockbot(CBaseEntity* pLocal, CUserCmd* pCmd)
{

	float bestdist = 250.f;
	int index = -1;

	for (int i = 0; i < I::Globals->nMaxClients; i++)
	{
		CBaseEntity* entity = I::ClientEntityList->Get<CBaseEntity>(i);

		if (!entity)
			continue;

		if (entity == nullptr || !entity->IsAlive() || entity->IsDormant() || i == pLocal->GetIndex())
			continue;

		float dist = pLocal->GetOrigin().DistTo(entity->GetOrigin());

		if (dist < bestdist)
		{
			bestdist = dist;
			index = i;
		}
	}

	return index;

}