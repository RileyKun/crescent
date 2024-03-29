#pragma once

class IClientEntity;
class ClientClass;
class IClientNetworkable;
class IClientUnknown;

enum struct classid_t {
	CAI_BaseNPC,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseObject,
	CBaseObjectUpgrade,
	CBaseParticleEntity,
	CBasePlayer,
	CBaseProjectile,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseViewModel,
	CBeam,
	CBoneFollower,
	CBonusDuckPickup,
	CBonusPack,
	CBonusRoundLogic,
	CBreakableProp,
	CBreakableSurface,
	CCaptureFlag,
	CCaptureFlagReturnIcon,
	CCaptureZone,
	CColorCorrection,
	CColorCorrectionVolume,
	CCurrencyPack,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityParticleTrail,
	CEnvDetailController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CEyeballBoss,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFogController,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncConveyor,
	CFuncForceField,
	CFuncLadder,
	CFuncMonitor,
	CFuncOccluder,
	CFuncPasstimeGoal,
	CFuncReflectiveGlass,
	CFuncRespawnRoom,
	CFuncRespawnRoomVisualizer,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHalloweenGiftPickup,
	CHalloweenPickup,
	CHalloweenSoulPack,
	CHandleTest,
	CHeadlessHatman,
	CHightower_TeleportVortex,
	CInfoLadderDismount,
	CInfoLightingRelative,
	CInfoOverlayAccessor,
	CLaserDot,
	CLightGlow,
	CMannVsMachineStats,
	CMaterialModifyControl,
	CMerasmus,
	CMerasmusDancer,
	CMonsterResource,
	CObjectCartDispenser,
	CObjectDispenser,
	CObjectSapper,
	CObjectSentrygun,
	CObjectTeleporter,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPasstimeBall,
	CPasstimeGun,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlasma,
	CPlayerDestructionDispenser,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPrecipitation,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRobotDispenser,
	CRopeKeyframe,
	CSceneEntity,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeStack,
	CSniperDot,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CSteamJet,
	CSun,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTeamRoundTimer,
	CTeamTrainWatcher,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTeleportVortex,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTETFBlood,
	CTETFExplosion,
	CTETFParticleEffect,
	CTEWorldDecal,
	CTFAmmoPack,
	CTFBall_Ornament,
	CTFBaseBoss,
	CTFBaseProjectile,
	CTFBaseRocket,
	CTFBat,
	CTFBat_Fish,
	CTFBat_Giftwrap,
	CTFBat_Wood,
	CTFBonesaw,
	CTFBotHintEngineerNest,
	CTFBottle,
	CTFBreakableMelee,
	CTFBreakableSign,
	CTFBuffItem,
	CTFCannon,
	CTFChargedSMG,
	CTFCleaver,
	CTFClub,
	CTFCompoundBow,
	CTFCrossbow,
	CTFDRGPomson,
	CTFDroppedWeapon,
	CTFFireAxe,
	CTFFists,
	CTFFlameManager,
	CTFFlameRocket,
	CTFFlameThrower,
	CTFFlareGun,
	CTFFlareGun_Revenge,
	CTFGameRulesProxy,
	CTFGasManager,
	CTFGenericBomb,
	CTFGlow,
	CTFGrapplingHook,
	CTFGrenadeLauncher,
	CTFGrenadePipebombProjectile,
	CTFHalloweenMinigame,
	CTFHalloweenMinigame_FallingPlatforms,
	CTFHellZap,
	CTFItem,
	CTFJar,
	CTFJarGas,
	CTFJarMilk,
	CTFKatana,
	CTFKnife,
	CTFLaserPointer,
	CTFLunchBox,
	CTFLunchBox_Drink,
	CTFMechanicalArm,
	CTFMedigunShield,
	CTFMiniGame,
	CTFMinigameLogic,
	CTFMinigun,
	CTFObjectiveResource,
	CTFParachute,
	CTFParachute_Primary,
	CTFParachute_Secondary,
	CTFParticleCannon,
	CTFPasstimeLogic,
	CTFPEPBrawlerBlaster,
	CTFPipebombLauncher,
	CTFPistol,
	CTFPistol_Scout,
	CTFPistol_ScoutPrimary,
	CTFPistol_ScoutSecondary,
	CTFPlayer,
	CTFPlayerDestructionLogic,
	CTFPlayerResource,
	CTFPointManager,
	CTFPowerupBottle,
	CTFProjectile_Arrow,
	CTFProjectile_BallOfFire,
	CTFProjectile_Cleaver,
	CTFProjectile_EnergyBall,
	CTFProjectile_EnergyRing,
	CTFProjectile_Flare,
	CTFProjectile_GrapplingHook,
	CTFProjectile_HealingBolt,
	CTFProjectile_Jar,
	CTFProjectile_JarGas,
	CTFProjectile_JarMilk,
	CTFProjectile_MechanicalArmOrb,
	CTFProjectile_Rocket,
	CTFProjectile_SentryRocket,
	CTFProjectile_SpellBats,
	CTFProjectile_SpellFireball,
	CTFProjectile_SpellKartBats,
	CTFProjectile_SpellKartOrb,
	CTFProjectile_SpellLightningOrb,
	CTFProjectile_SpellMeteorShower,
	CTFProjectile_SpellMirv,
	CTFProjectile_SpellPumpkin,
	CTFProjectile_SpellSpawnBoss,
	CTFProjectile_SpellSpawnHorde,
	CTFProjectile_SpellSpawnZombie,
	CTFProjectile_SpellTransposeTeleport,
	CTFProjectile_Throwable,
	CTFProjectile_ThrowableBreadMonster,
	CTFProjectile_ThrowableBrick,
	CTFProjectile_ThrowableRepel,
	CTFPumpkinBomb,
	CTFRagdoll,
	CTFRaygun,
	CTFReviveMarker,
	CTFRevolver,
	CTFRobotArm,
	CTFRobotDestruction_Robot,
	CTFRobotDestruction_RobotGroup,
	CTFRobotDestruction_RobotSpawn,
	CTFRobotDestructionLogic,
	CTFRocketLauncher,
	CTFRocketLauncher_AirStrike,
	CTFRocketLauncher_DirectHit,
	CTFRocketLauncher_Mortar,
	CTFRocketPack,
	CTFScatterGun,
	CTFShotgun,
	CTFShotgun_HWG,
	CTFShotgun_Pyro,
	CTFShotgun_Revenge,
	CTFShotgun_Soldier,
	CTFShotgunBuildingRescue,
	CTFShovel,
	CTFSlap,
	CTFSMG,
	CTFSniperRifle,
	CTFSniperRifleClassic,
	CTFSniperRifleDecap,
	CTFSodaPopper,
	CTFSpellBook,
	CTFStickBomb,
	CTFStunBall,
	CTFSword,
	CTFSyringeGun,
	CTFTankBoss,
	CTFTauntProp,
	CTFTeam,
	CTFThrowable,
	CTFViewModel,
	weapon_t,
	weapon_tGrenadeProj,
	weapon_tGun,
	weapon_tMelee,
	weapon_tMerasmusGrenade,
	CTFWeaponBuilder,
	CTFWeaponFlameBall,
	CTFWeaponInvis,
	CTFWeaponPDA,
	CTFWeaponPDA_Engineer_Build,
	CTFWeaponPDA_Engineer_Destroy,
	CTFWeaponPDA_Spy,
	CTFWeaponPDAExpansion_Dispenser,
	CTFWeaponPDAExpansion_Teleporter,
	CTFWeaponSapper,
	CTFWearable,
	CTFWearableCampaignItem,
	CTFWearableDemoShield,
	CTFWearableItem,
	CTFWearableLevelableItem,
	CTFWearableRazorback,
	CTFWearableRobotArm,
	CTFWearableVM,
	CTFWrench,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponIFMBase,
	CWeaponIFMBaseCamera,
	CWeaponIFMSteadyCam,
	CWeaponMedigun,
	CWorld,
	CZombie,
	DustTrail,
	MovieExplosion,
	NextBotCombatCharacter,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

//-----------------------------------------------------------------------------
// Purpose: Exposes IClientEntity's to engine
//-----------------------------------------------------------------------------
class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual IClientNetworkable * GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(int hEnt) = 0;
	virtual IClientUnknown* GetClientUnknownFromHandle(int hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual IClientEntity* GetClientEntity(int entnum) = 0;
	virtual IClientEntity* GetClientEntityFromHandle(int hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};