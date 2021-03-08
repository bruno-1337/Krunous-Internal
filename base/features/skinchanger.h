#pragma once
// used: std:unordered_map
#include <unordered_map>

// used: winapi includes, singleton
#include "../common.h"
// used: itemdefinitionindex; baseentity, baseweapon classes
#include "../sdk/entity.h"
// used: listener event function
#include "../sdk/interfaces/igameeventmanager.h"

struct SkinObject_t
{
	SkinObject_t(const char* szName, const char* szModel, const char* szKillIcon = nullptr)
		: szName(szName), szModel(szModel), szKillIcon(szKillIcon) { }

	const char* szName = nullptr;
	const char* szModel = nullptr;
	const char* szKillIcon = nullptr;
};

// @note: u can find viewmodel indexes with "sv_precacheinfo"
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

const std::pair<std::size_t, std::string> arrItemQuality[] =
{
	{ 0, "Normal" },
	{ 1, "Genuine" },
	{ 2, "Vintage" },
	{ 3, "Unusual" },
	{ 5, "Community" },
	{ 6, "Developer" },
	{ 7, "Self-Made" },
	{ 8, "Customized" },
	{ 9, "Strange" },
	{ 10, "Completed" },
	{ 12, "Tournament" }
};

// @todo: add valve vdf/vpk parser and get skins, rarity things, etc with it
class CSkinChanger : public CSingleton<CSkinChanger>
{
public:
	// Get
	void Run();
	/* knife kill icons replace */
	void Event(IGameEvent* pEvent, const FNV1A_t uNameHash);
	/* dump stikers and paintkits */
	void Dump();

	bool apply_knife_model(CBaseCombatWeapon* weapon, const char* model);

	bool ApplyKnife(CBaseCombatWeapon* pWeapon, const char* vMdl);
private:
	/* ur values and main functionality */
};
