#pragma once
// used: define to add values to variables vector
#include "config.h"

#pragma region variables_array_entries
enum EVisualsInfoFlags : int
{
	INFO_FLAG_HELMET = 0,
	INFO_FLAG_KEVLAR,
	INFO_FLAG_KIT,
	INFO_FLAG_ZOOM,
	INFO_FLAG_MAX
};

enum EVisualsRemovals : int
{
	REMOVAL_POSTPROCESSING = 0,
	REMOVAL_PUNCH,
	REMOVAL_SMOKE,
	REMOVAL_SCOPE,
	REMOVAL_MAX
};
#pragma endregion

#pragma region variables_combo_entries
enum class EAntiAimPitchType : int
{
	NONE = 0,
	UP,
	DOWN,
	ZERO
};

enum class EAntiAimYawType : int
{
	NONE = 0,
	DESYNC
};

enum class EVisualsBoxType : int
{
	NONE = 0,
	FULL,
	CORNERS
};

enum class EVisualsGlowStyle : int
{
	OUTER = 0,
	COVER,
	INNER
};

enum class EVisualsPlayersChams : int
{
	COVERED = 0,
	FLAT,
	WIREFRAME,
	REFLECTIVE
};

enum class EVisualsViewModelChams : int
{
	NO_DRAW = 0,
	COVERED,
	FLAT,
	WIREFRAME,
	GLOW,
	SCROLL,
	CHROME
};
#pragma endregion

struct Variables_t
{
	#pragma region variables_rage
	// aimbot
	C_ADD_VARIABLE(bool, bRage, false);

	// antiaim
	C_ADD_VARIABLE(bool, bAntiAim, false);
	C_ADD_VARIABLE(int, iAntiAimPitch, 0);
	C_ADD_VARIABLE(int, iAntiAimYaw, 0);
	C_ADD_VARIABLE(int, iAntiAimDesyncKey, VK_XBUTTON1);
	#pragma endregion

	#pragma region variables_legit
	// aimbot
	C_ADD_VARIABLE(bool, bLegit, false);
	C_ADD_VARIABLE(int, iAimKey, 0);
	C_ADD_VARIABLE(int, iAimFov, 0);
	C_ADD_VARIABLE(int, iAimSmooth, 0);

	C_ADD_VARIABLE(int, iPAimFov, 0);//PISTOL
	C_ADD_VARIABLE(int, iPAimSmooth, 0);
	C_ADD_VARIABLE(int, iPBone, 1);
	C_ADD_VARIABLE(bool, bPOneShot, false);
	C_ADD_VARIABLE(bool, bPAimNBone, false);


	C_ADD_VARIABLE(int, iForceKey, 0);//forcekey


	C_ADD_VARIABLE(int, iRAimFov, 0);//RIFLE
	C_ADD_VARIABLE(int, iRAimSmooth, 0);
	C_ADD_VARIABLE(bool, bROneShot, false);
	C_ADD_VARIABLE(int, iRBone, 1);
	C_ADD_VARIABLE(bool, bRAimNBone, false);

	C_ADD_VARIABLE(int, iSAimFov, 0);//SNIPER
	C_ADD_VARIABLE(int, iSAimSmooth, 0);
	C_ADD_VARIABLE(bool, bSOneShot, false);
	C_ADD_VARIABLE(int, iSBone, 1);
	C_ADD_VARIABLE(bool, bSAimNBone, false);

	C_ADD_VARIABLE(int, iSHAimFov, 0);//SHOTGUN
	C_ADD_VARIABLE(int, iSHAimSmooth, 0);
	C_ADD_VARIABLE(bool, bSHOneShot, false);
	C_ADD_VARIABLE(int, iSHBone, 1);
	C_ADD_VARIABLE(bool, bSHAimNBone, false);

	C_ADD_VARIABLE(int, iAWPAimFov, 0);//AWP
	C_ADD_VARIABLE(int, iAWPAimSmooth, 0);
	C_ADD_VARIABLE(bool, bAWPOneShot, false);
	C_ADD_VARIABLE(int, iAWPBone, 1);
	C_ADD_VARIABLE(bool, bAWPAimNBone, false);

	C_ADD_VARIABLE(int, iSCOUTAimFov, 0);//SCOUT
	C_ADD_VARIABLE(int, iSCOUTAimSmooth, 0);
	C_ADD_VARIABLE(bool, bSCOUTOneShot, false);
	C_ADD_VARIABLE(int, iSCOUTBone, 1);
	C_ADD_VARIABLE(bool, bSCOUTAimNBone, false);

	C_ADD_VARIABLE(int, iAUTOAimFov, 0);//AUTO
	C_ADD_VARIABLE(int, iAUTOAimSmooth, 0);
	C_ADD_VARIABLE(bool, bAUTOOneShot, false);
	C_ADD_VARIABLE(int, iAUTOBone, 1);
	C_ADD_VARIABLE(bool, bAUTOAimNBone, false);

	C_ADD_VARIABLE(int, iMAimFov, 0);//MACHINEGUN
	C_ADD_VARIABLE(int, iMAimSmooth, 0);
	C_ADD_VARIABLE(bool, bMAOneShot, false);
	C_ADD_VARIABLE(int, iMABone, 1);
	C_ADD_VARIABLE(bool, bMAAimNBone, false);

	C_ADD_VARIABLE(int, iSMGAimFov, 0);//SMG
	C_ADD_VARIABLE(int, iSMGAimSmooth, 0);
	C_ADD_VARIABLE(bool, bSMGOneShot, false);
	C_ADD_VARIABLE(int, iSMGBone, 1);
	C_ADD_VARIABLE(bool, bSMGAimNBone, false);
	

	C_ADD_VARIABLE(bool, bOneShot, false);
	C_ADD_VARIABLE(bool, bAimHead, true);
	C_ADD_VARIABLE(bool, bAimChest, true);
	C_ADD_VARIABLE(bool, bAimStomach, true);
	C_ADD_VARIABLE(int, iBone, 1);
	C_ADD_VARIABLE(bool, bAimArms, false);
	C_ADD_VARIABLE(bool, bAimLegs, false);
	C_ADD_VARIABLE(bool, bAimAutoWall, false);
	C_ADD_VARIABLE(bool, iAimTeam, false);
	C_ADD_VARIABLE(bool, bAimNBone, false);

	// trigger
	C_ADD_VARIABLE(bool, bTrigger, false);
	C_ADD_VARIABLE(int, iTriggerKey, 0);
	C_ADD_VARIABLE(int, iTriggerDelay, 0);
	C_ADD_VARIABLE(bool, bTriggerAutoWall, false);
	C_ADD_VARIABLE(int, iTriggerMinimalDamage, 70);

	C_ADD_VARIABLE(bool, bTriggerHead, true);
	C_ADD_VARIABLE(bool, bTriggerChest, true);
	C_ADD_VARIABLE(bool, bTriggerStomach, true);
	C_ADD_VARIABLE(bool, bTriggerArms, false);
	C_ADD_VARIABLE(bool, bTriggerLegs, false);
	#pragma endregion

	#pragma region variables_visuals
	C_ADD_VARIABLE(bool, bEsp, false);

	// main
	C_ADD_VARIABLE(bool, bEspMain, false);
	C_ADD_VARIABLE(bool, bEspMainEnemies, false);
	C_ADD_VARIABLE(bool, bEspMainAllies, false);
	C_ADD_VARIABLE(bool, bEspMainWeapons, false);
	C_ADD_VARIABLE(bool, bEspMainGrenades, false);
	C_ADD_VARIABLE(bool, bEspMainBomb, false);

	// players
	C_ADD_VARIABLE(int, iEspMainPlayerBox, static_cast<int>(EVisualsBoxType::FULL));
	C_ADD_VARIABLE(Color, colEspMainBoxEnemies, Color(160, 60, 60, 255));
	C_ADD_VARIABLE(Color, colEspMainBoxEnemiesWall, Color(200, 185, 110, 255));
	C_ADD_VARIABLE(Color, colEspMainBoxAllies, Color(0, 200, 170, 255));
	C_ADD_VARIABLE(Color, colEspMainBoxAlliesWall, Color(170, 110, 200, 255));

	C_ADD_VARIABLE(bool, bEspMainPlayerFarRadar, false);
	C_ADD_VARIABLE(bool, bEspMainPlayerInfo, false);

	/* left */
	C_ADD_VARIABLE(bool, bEspMainPlayerHealth, true);
	C_ADD_VARIABLE(bool, bEspMainPlayerMoney, false);

	/* top */
	C_ADD_VARIABLE(bool, bEspMainPlayerName, true);
	C_ADD_VARIABLE(bool, bEspMainPlayerFlash, false);

	/* right */
	C_ADD_VARIABLE_VECTOR(bool, INFO_FLAG_MAX, vecEspMainPlayerFlags, true);

	/* bottom */
	C_ADD_VARIABLE(bool, bEspMainPlayerWeapons, true);
	C_ADD_VARIABLE(bool, bEspMainPlayerAmmo, true);
	C_ADD_VARIABLE(bool, bEspMainPlayerDistance, false);

	// weapons
	C_ADD_VARIABLE(int, iEspMainWeaponBox, static_cast<int>(EVisualsBoxType::NONE));
	C_ADD_VARIABLE(Color, colEspMainBoxWeapons, Color(255, 255, 255, 220));

	C_ADD_VARIABLE(bool, bEspMainWeaponInfo, false);

	C_ADD_VARIABLE(bool, bEspMainWeaponIcon, true);
	C_ADD_VARIABLE(bool, bEspMainWeaponAmmo, true);
	C_ADD_VARIABLE(bool, bEspMainWeaponDistance, false);

	// glow
	C_ADD_VARIABLE(bool, bEspGlow, false);
	C_ADD_VARIABLE(bool, bEspGlowEnemies, false);
	C_ADD_VARIABLE(bool, bEspGlowAllies, false);
	C_ADD_VARIABLE(bool, bEspGlowWeapons, false);
	C_ADD_VARIABLE(bool, bEspGlowGrenades, false);
	C_ADD_VARIABLE(bool, bEspGlowBomb, false);

	C_ADD_VARIABLE(bool, bEspGlowBloom, false);

	C_ADD_VARIABLE(Color, colEspGlowEnemies, Color(230, 20, 60, 128));
	C_ADD_VARIABLE(Color, colEspGlowEnemiesWall, Color(255, 235, 240, 128));
	C_ADD_VARIABLE(Color, colEspGlowAllies, Color(85, 140, 255, 128));
	C_ADD_VARIABLE(Color, colEspGlowAlliesWall, Color(240, 235, 255, 128));
	C_ADD_VARIABLE(Color, colEspGlowWeapons, Color(80, 0, 225, 128));
	C_ADD_VARIABLE(Color, colEspGlowGrenades, Color(180, 130, 30, 128));
	C_ADD_VARIABLE(Color, colEspGlowBomb, Color(140, 220, 80, 128));
	C_ADD_VARIABLE(Color, colEspGlowBombPlanted, Color(200, 210, 80, 128));

	// chams
	C_ADD_VARIABLE(bool, bEspChams, false);
	C_ADD_VARIABLE(bool, bEspChamsEnemies, false);
	C_ADD_VARIABLE(bool, bEspChamsAllies, false);
	C_ADD_VARIABLE(bool, bEspChamsViewModel, false);

	C_ADD_VARIABLE(bool, bEspChamsXQZ, false);
	C_ADD_VARIABLE(bool, bEspChamsDisableOcclusion, false);
	C_ADD_VARIABLE(int, iEspChamsPlayer, static_cast<int>(EVisualsPlayersChams::COVERED));
	C_ADD_VARIABLE(int, iEspChamsViewModel, static_cast<int>(EVisualsViewModelChams::WIREFRAME));
	C_ADD_VARIABLE(Color, colEspChamsEnemies, Color(180, 65, 65, 255));
	C_ADD_VARIABLE(Color, colEspChamsEnemiesWall, Color(180, 180, 40, 255));
	C_ADD_VARIABLE(Color, colEspChamsAllies, Color(70, 40, 190, 255));
	C_ADD_VARIABLE(Color, colEspChamsAlliesWall, Color(50, 150, 150, 255));
	C_ADD_VARIABLE(Color, colEspChamsViewModel, Color(80, 255, 45, 255));
	C_ADD_VARIABLE(Color, colEspChamsViewModelAdditional, Color(0, 0, 255, 255));

	// world
	C_ADD_VARIABLE(bool, bWorld, false);
	C_ADD_VARIABLE(bool, bWorldNightMode, false);
	C_ADD_VARIABLE(int, iWorldMaxFlash, 100);
	C_ADD_VARIABLE(int, iWorldThirdPersonKey, 0);
	C_ADD_VARIABLE(bool, bGrenadePred, false);
	C_ADD_VARIABLE(float, flWorldThirdPersonOffset, 150.f);
	C_ADD_VARIABLE_VECTOR(bool, REMOVAL_MAX, vecWorldRemovals, false);

	// on-screen
	C_ADD_VARIABLE(bool, bScreen, false);
	C_ADD_VARIABLE(float, flScreenCameraFOV, 0.f);
	C_ADD_VARIABLE(float, flScreenViewModelFOV, 0.f);
	C_ADD_VARIABLE(float, flScreenViewModelX, 1.f);
	C_ADD_VARIABLE(float, flScreenViewModelY, 1.f);
	C_ADD_VARIABLE(float, flScreenViewModelZ, -1.f);
	C_ADD_VARIABLE(bool, bScreenHitMarker, false);
	C_ADD_VARIABLE(bool, bScreenHitMarkerDamage, false);
	C_ADD_VARIABLE(bool, bScreenHitMarkerSound, false);
	C_ADD_VARIABLE(bool, bQuake, false);
	C_ADD_VARIABLE(int, iRagdollGravity, 2);
	C_ADD_VARIABLE(bool, bRagdollGravity, false);

	C_ADD_VARIABLE(bool, b180Camera, false);
	C_ADD_VARIABLE(int, i180camerakey, 0);

	C_ADD_VARIABLE(float, flScreenHitMarkerTime, 1.0f);
	C_ADD_VARIABLE(int, iScreenHitMarkerGap, 5);
	C_ADD_VARIABLE(int, iScreenHitMarkerLenght, 10);
	C_ADD_VARIABLE(Color, colScreenHitMarker, Color(255, 255, 255, 255));
	C_ADD_VARIABLE(Color, colScreenHitMarkerDamage, Color(200, 55, 20, 255));
	#pragma endregion

	#pragma region variables_misc
	// movement
	C_ADD_VARIABLE(bool, bMiscBunnyHop, false);
	C_ADD_VARIABLE(int, iMiscBunnyHopChance, 100);
	C_ADD_VARIABLE(bool, bMiscAutoStrafe, false);
	C_ADD_VARIABLE(bool, bMiscRCS, false);
	

	C_ADD_VARIABLE(bool, bMiscFakeLag, false); 
	
	C_ADD_VARIABLE(bool, bMiscAutoAccept, false);
	C_ADD_VARIABLE(bool, bMiscAutoPistol, false);
	C_ADD_VARIABLE(bool, bMiscNoCrouchCooldown, false);
	C_ADD_VARIABLE(int, iMiscBlockBot, 0);
	C_ADD_VARIABLE(int, iBlockBotKey, 0);
	

	//Config
	C_ADD_VARIABLE(bool, bMiscWeaponConfig, false);

	//SkinChanger
	C_ADD_VARIABLE(bool, bSkinChanger, false);
	C_ADD_VARIABLE(int, iSkinKnife, 1);
	C_ADD_VARIABLE(int, iSkinId, 1);
	C_ADD_VARIABLE(int, iSkinSeed, 1);
	

	// exploits
	C_ADD_VARIABLE(bool, bMiscPingSpike, false);
	C_ADD_VARIABLE(float, flMiscLatencyFactor, 0.4f);
	C_ADD_VARIABLE(bool, bMiscRevealRanks, false);
	C_ADD_VARIABLE(bool, bMiscUnlockInventory, false);
	C_ADD_VARIABLE(bool, bMiscAntiUntrusted, true);
	C_ADD_VARIABLE(bool, bMiscPureBypass, true);
	#pragma endregion

	#pragma region variables_menu
	C_ADD_VARIABLE(int, iMenuKey, VK_INSERT);
	C_ADD_VARIABLE(int, RestartKey, VK_HOME);
	C_ADD_VARIABLE(int, iPanicKey, VK_END);
	#pragma endregion
};

inline Variables_t Vars;
