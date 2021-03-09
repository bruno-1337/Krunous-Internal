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
	bool apply_knife_skin(CBaseCombatWeapon* weapon, short item_definition_index, int paint_kit, int model_index, int entity_quality);
	void getSkinId(); int SkinId;
private:
	/* ur values and main functionality */
};
