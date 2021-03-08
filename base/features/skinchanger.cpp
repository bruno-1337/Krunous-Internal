#include "skinchanger.h"

// used: create entity
#include "../utilities.h"
// used: client, engine interfaces
#include "../core/interfaces.h"
// used: cheat variables
#include "../core/variables.h"

void CSkinChanger::Run()
{
	CBaseEntity* pLocal = I::ClientEntityList->Get<CBaseEntity>(I::Engine->GetLocalPlayer());
	


	// Don't change anything if we're not alive.
	if (!pLocal || pLocal->GetLifeState() != LIFE_ALIVE)
		return;
	// Get handles to weapons we're carrying.
	 UINT* hWeapons = reinterpret_cast<UINT*>(pLocal->GetWeaponsHandle());

	if (!hWeapons)
		return;

	// Retrieve our player information which will be used for ownership checking.
	
	PlayerInfo_t LocalPlayerInfo;
	I::Engine->GetPlayerInfo(pLocal->GetIndex(), &LocalPlayerInfo);

	auto active_weapon = pLocal->GetWeapon();

	if (!active_weapon)
		return;



	auto my_weapons = pLocal->GetWeaponsHandle();
	
	for (int i = 0; my_weapons[i] != 0xFFFFFFFF; i++)
	{
		auto weapon = (CBaseCombatWeapon*)(I::ClientEntityList->GetClientEntityFromHandle(my_weapons[i]));
		short nDefinitionIndex = active_weapon->GetItemDefinitionIndex();
		CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

		if (!weapon)
			return;
		if (pWeaponData->nWeaponType == WEAPONTYPE_KNIFE)
		{

			switch (C::Get<int>(Vars.iSkinKnife))
			{
			case 0:
				break;
			case 1:
				apply_knife_model(weapon, model_bayonet);
				break;
			case 2:
				apply_knife_model(weapon, model_m9);
				break;
			case 3:
				apply_knife_model(weapon, model_karambit);
				break;
			case 4:
				apply_knife_model(weapon, model_bowie);
				break;
			case 5:
				apply_knife_model(weapon, model_butterfly);
				break;
			case 6:
				apply_knife_model(weapon, model_falchion);
				break;
			case 7:
				apply_knife_model(weapon, model_flip);
				break;
			case 8:
				apply_knife_model(weapon, model_gut);
				break;
			case 9:
				apply_knife_model(weapon, model_huntsman);
				break;
			case 10:
				apply_knife_model(weapon, model_shadow_daggers);
				break;
			case 11:
				apply_knife_model(weapon, model_navaja);
				break;
			case 12:
				apply_knife_model(weapon, model_stiletto);
				break;
			case 13:
				apply_knife_model(weapon, model_talon);
				break;
			case 14:
				apply_knife_model(weapon, model_ursus);
				break;
			}

		}
	}
}
bool CSkinChanger::apply_knife_model(CBaseCombatWeapon* weapon, const char* model)
{

	CBaseEntity* local_player = I::ClientEntityList->Get<CBaseEntity>(I::Engine->GetLocalPlayer());
	if (!local_player)
		return false;

	auto viewmodel = (CBaseViewModel*)(I::ClientEntityList->GetClientEntityFromHandle(local_player->GetViewModelHandle()));
	if (!viewmodel)
		return false;

	auto h_view_model_weapon = viewmodel->GetWeaponHandle();
	if (!h_view_model_weapon)
		return false;

	auto view_model_weapon = (CBaseCombatWeapon*)(I::ClientEntityList->GetClientEntityFromHandle(h_view_model_weapon));
	if (view_model_weapon != weapon)
		return false;

	viewmodel->GetModelIndex() = I::ModelInfo->GetModelIndex(model);

	return true;
}

	// Loop through weapons and run our skin function on them.


	// it will help you here my sweetest candy <3
	// https://www.unknowncheats.me/wiki/Counter_Strike_Global_Offensive:Skin_Changer



void CSkinChanger::Event(IGameEvent* pEvent, const FNV1A_t uNameHash)
{
	if (!I::Engine->IsInGame())
		return;

}
