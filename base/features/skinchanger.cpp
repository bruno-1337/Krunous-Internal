#include "skinchanger.h"

// used: create entity
#include "../utilities.h"
// used: client, engine interfaces
#include "../core/interfaces.h"
// used: cheat variables
#include "../core/variables.h"

#include "../utilities/inputsystem.h"

void CSkinChanger::Run()
{
	CBaseEntity* pLocal = I::ClientEntityList->Get<CBaseEntity>(I::Engine->GetLocalPlayer());

	getSkinId();
	


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

	auto model_bayonet = "models/weapons/v_knife_bayonet.mdl";
	auto model_m9 = "models/weapons/v_knife_m9_bay.mdl";
	auto model_karambit = "models/weapons/v_knife_karam.mdl";
	auto model_bowie = "models/weapons/v_knife_survival_bowie.mdl";
	auto model_butterfly = "models/weapons/v_knife_butterfly.mdl";
	auto model_falchion = "models/weapons/v_knife_falchion_advanced.mdl";
	auto model_flip = "models/weapons/v_knife_flip.mdl";
	auto model_gut = "models/weapons/v_knife_gut.mdl";
	auto model_huntsman = "models/weapons/v_knife_tactical.mdl";
	auto model_shadow_daggers = "models/weapons/v_knife_push.mdl";
	auto model_navaja = "models/weapons/v_knife_gypsy_jackknife.mdl";
	auto model_stiletto = "models/weapons/v_knife_stiletto.mdl";
	auto model_talon = "models/weapons/v_knife_widowmaker.mdl";
	auto model_ursus = "models/weapons/v_knife_ursus.mdl";

	auto index_bayonet = I::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	auto index_m9 = I::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	auto index_karambit = I::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
	auto index_bowie = I::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
	auto index_butterfly = I::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	auto index_falchion = I::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	auto index_flip = I::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
	auto index_gut = I::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
	auto index_huntsman = I::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	auto index_shadow_daggers = I::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
	auto index_navaja = I::ModelInfo->GetModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
	auto index_stiletto = I::ModelInfo->GetModelIndex("models/weapons/v_knife_stiletto.mdl");
	auto index_talon = I::ModelInfo->GetModelIndex("models/weapons/v_knife_widowmaker.mdl");
	auto index_ursus = I::ModelInfo->GetModelIndex("models/weapons/v_knife_ursus.mdl");

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
		short dDefinitionIndex = weapon->GetItemDefinitionIndex();
		CCSWeaponData* dWeaponData = I::WeaponSystem->GetWeaponData(dDefinitionIndex);
		if (dWeaponData->nWeaponType == WEAPONTYPE_KNIFE)
		{
			switch (C::Get<int>(Vars.iSkinKnife))
			{
			case 0:  
				break;
			case 1:
				apply_knife_skin(weapon, WEAPON_KNIFE_BAYONET, SkinId, index_bayonet, 3);
				break;
			case 2:
				apply_knife_skin(weapon, WEAPON_KNIFE_M9_BAYONET, SkinId, index_m9, 3);
				break;
			case 3:
				apply_knife_skin(weapon, WEAPON_KNIFE_KARAMBIT, SkinId, index_karambit, 3);
				break;
			case 4:
				apply_knife_skin(weapon, WEAPON_KNIFE_SURVIVAL_BOWIE, SkinId, index_bowie, 3);
				break;
			case 5:
				apply_knife_skin(weapon, WEAPON_KNIFE_BUTTERFLY, SkinId, index_butterfly, 3);
				break;
			case 6:
				apply_knife_skin(weapon, WEAPON_KNIFE_FALCHION, SkinId, index_falchion, 3);
				break;
			case 7:
				apply_knife_skin(weapon, WEAPON_KNIFE_FLIP, SkinId, index_flip, 3);
				break;
			case 8:
				apply_knife_skin(weapon, WEAPON_KNIFE_GUT, SkinId, index_gut, 3);
				break;
			case 9:
				apply_knife_skin(weapon, WEAPON_KNIFE_TACTICAL, SkinId, index_huntsman, 3);
				break;
			case 10:
				apply_knife_skin(weapon, WEAPON_KNIFE_PUSH, SkinId, index_shadow_daggers, 3);
				break;
			case 11:
				apply_knife_skin(weapon, WEAPON_KNIFE_GYPSY_JACKKNIFE, SkinId, index_navaja, 3);
				break;
			case 12:
				apply_knife_skin(weapon, WEAPON_KNIFE_STILETTO, SkinId, index_stiletto, 3);
				break;
			case 13:
				apply_knife_skin(weapon, WEAPON_KNIFE_WIDOWMAKER, SkinId, index_talon, 3);
				break;
			case 14:
				apply_knife_skin(weapon, WEAPON_KNIFE_URSUS, SkinId, index_ursus, 3);
				break;
			}

		}
	}


	if ((C::Get<int>(Vars.iForceKey) != 0 && IPT::IsKeyDown(C::Get<int>(Vars.iForceKey)))) //check for aimkey
	{
		I::ClientState->iDeltaTick = -1;
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

bool CSkinChanger::apply_knife_skin(CBaseCombatWeapon* weapon, short item_definition_index, int paint_kit, int model_index, int entity_quality)
{
	if (weapon->GetViewModelIndex() != model_index)
	{	
		I::ClientState->iDeltaTick = -1;
		weapon->SetModelIndex(model_index);
	}
	weapon->GetItemDefinitionIndex() = item_definition_index;
	weapon->GetViewModelIndex() = model_index;
	weapon->GetFallbackPaintKit() = paint_kit;
	weapon->GetEntityQuality() = entity_quality;
	weapon->GetFallbackSeed() = C::Get<int>(Vars.iSkinSeed);
	weapon->GetFallbackWear() = 0.001f;

	weapon->GetItemIDHigh() = -1;
	

	return true;
}


void CSkinChanger::getSkinId()
{
	switch (C::Get<int>(Vars.iSkinId))
	{
	case 0:
		SkinId = 0;
		break;
	case 1:
		SkinId = 44;
		break;
	case 2:
		SkinId = 12;
		break;
	case 3:
		SkinId = 38;
		break;
	case 4:
		SkinId = 40;
		break;
	case 5:
		SkinId = 59;
		break;
	case 6:
		SkinId = 409;
		break;
	case 7:
		SkinId = 413;
		break;
	case 8:
		SkinId = 415;
		break;
	case 9:
		SkinId = 416;
		break;
	case 10:
		SkinId = 419;
		break;
	case 11:
		SkinId = 98;
		break;
	case 12:
		SkinId = 143;
		break;
	case 13:
		SkinId = 421;
		break;
	case 14:
		SkinId = 420;
		break;
	case 15:
		SkinId = 418;
		break;
	}

}

	// Loop through weapons and run our skin function on them.


	// it will help you here my sweetest candy <3
	// https://www.unknowncheats.me/wiki/Counter_Strike_Global_Offensive:Skin_Changer



void CSkinChanger::Event(IGameEvent* pEvent, const FNV1A_t uNameHash)
{
	if (!I::Engine->IsInGame())
		return;

}
