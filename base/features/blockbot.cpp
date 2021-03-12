
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

    if (C::Get<int>(Vars.iBlockBotKey) == 0 || !IPT::IsKeyDown(C::Get<int>(Vars.iBlockBotKey))) //check for aimkey
    {
        return;
    }



    if (!pLocal->IsAlive())
        return;


    if (IPT::IsKeyDown(C::Get<int>(Vars.iBlockBotKey)))
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

        if (index == -1)
            return;

        CBaseEntity* target = I::ClientEntityList->Get<CBaseEntity>(index);

        if (!target)
            return;

        QAngle angles = M::CalcAngle(pLocal->GetOrigin(), target->GetOrigin());

        angles.y -= pCmd->angViewPoint.y;
        angles.Normalize();

        if (angles.y < 0.0f)
            pCmd->flSideMove = 450.f;
        else if (angles.y > 0.0f)
            pCmd->flSideMove = -450.f;
    }
}