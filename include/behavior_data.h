#ifndef BEHAVIOR_DATA_H
#define BEHAVIOR_DATA_H

#include "types.h"

#include "rm2c.h"

// List of commands as enum for ifdefs
// Vanilla ones are left unnamed, custom ones are named
enum BehaviorCommandsIDList
{
    BHV_CMD_BEGIN,
    BHV_SCRIPT_CMD_01,
    BHV_SCRIPT_CMD_02,
    BHV_SCRIPT_CMD_03,
    BHV_SCRIPT_CMD_04,
    BHV_SCRIPT_CMD_05,
    BHV_SCRIPT_CMD_06,
    BHV_SCRIPT_CMD_07,
    BHV_SCRIPT_CMD_08,
    BHV_SCRIPT_CMD_09,
    BHV_SCRIPT_CMD_0A,
    BHV_SCRIPT_CMD_0B,
    BHV_SCRIPT_CMD_0C,
    BHV_SCRIPT_CMD_0D,
    BHV_SCRIPT_CMD_0E,
    BHV_SCRIPT_CMD_0F,
    BHV_SCRIPT_CMD_10,
    BHV_SCRIPT_CMD_11,
    BHV_SCRIPT_CMD_12,
    BHV_SCRIPT_CMD_13,
    BHV_SCRIPT_CMD_14,
    BHV_SCRIPT_CMD_15,
    BHV_SCRIPT_CMD_16,
    BHV_SCRIPT_CMD_17,
    BHV_SCRIPT_CMD_18,
    BHV_SCRIPT_CMD_19,
    BHV_SCRIPT_CMD_1A,
    BHV_SCRIPT_CMD_1B,
    BHV_SCRIPT_CMD_1C,
    BHV_SCRIPT_CMD_1D,
    BHV_SCRIPT_CMD_1E,
    BHV_SCRIPT_CMD_1F,
    BHV_SCRIPT_CMD_20,
    BHV_SCRIPT_CMD_21,
    BHV_SCRIPT_CMD_22,
    BHV_SCRIPT_CMD_23,
    BHV_SCRIPT_CMD_24,
    BHV_SCRIPT_CMD_25,
    BHV_SCRIPT_CMD_26,
    BHV_SCRIPT_CMD_27,
    BHV_SCRIPT_CMD_28,
    BHV_SCRIPT_CMD_29,
    BHV_SCRIPT_CMD_2A,
    BHV_SCRIPT_CMD_2B,
    BHV_SCRIPT_CMD_2C,
    BHV_SCRIPT_CMD_2D,
    BHV_SCRIPT_CMD_2E,
    BHV_SCRIPT_CMD_2F,
    BHV_SCRIPT_CMD_30,
    BHV_SCRIPT_CMD_31,
    BHV_SCRIPT_CMD_32,
    BHV_SCRIPT_CMD_33,
    BHV_SCRIPT_CMD_34,
    BHV_SCRIPT_CMD_35,
    BHV_SCRIPT_CMD_36,
    BHV_SCRIPT_CMD_37,
    BHV_SCRIPT_CMD_CYLBOARD,
};

#define BPARAM1(param) (((param) & 0xFF) << 24)
#define BPARAM2(param) (((param) & 0xFF) << 16)
#define BPARAM3(param) (((param) & 0xFF) << 8)
#define BPARAM4(param) (((param) & 0xFF) << 0)

extern const BehaviorScript bhvStarDoor[];
extern const BehaviorScript bhvMrI[];
extern const BehaviorScript bhvMrIBody[];
extern const BehaviorScript bhvMrIParticle[];
extern const BehaviorScript bhvPurpleParticle[];
extern const BehaviorScript bhvGiantPole[];
extern const BehaviorScript bhvPoleGrabbing[];
extern const BehaviorScript bhvTHIHugeIslandTop[];
extern const BehaviorScript bhvTHITinyIslandTop[];
extern const BehaviorScript bhvCapSwitchBase[];
extern const BehaviorScript bhvCapSwitch[];
extern const BehaviorScript bhvKingBobomb[];
extern const BehaviorScript bhvBobombAnchorMario[];
extern const BehaviorScript bhvBetaChestBottom[];
extern const BehaviorScript bhvBetaChestLid[];
extern const BehaviorScript bhvBubbleParticleSpawner[];
extern const BehaviorScript bhvBubbleMaybe[];
extern const BehaviorScript bhvSmallWaterWave[];
extern const BehaviorScript bhvSmallWaterWave398[];
extern const BehaviorScript bhvWaterAirBubble[];
extern const BehaviorScript bhvSmallParticle[];
extern const BehaviorScript bhvPlungeBubble[];
extern const BehaviorScript bhvSmallParticleSnow[];
extern const BehaviorScript bhvSmallParticleBubbles[];
extern const BehaviorScript bhvFishGroup[];
extern const BehaviorScript bhvCannon[];
extern const BehaviorScript bhvCannonBarrel[];
extern const BehaviorScript bhvCannonBaseUnused[];
extern const BehaviorScript bhvChuckya[];
extern const BehaviorScript bhvChuckyaAnchorMario[];
extern const BehaviorScript bhvUnused05A8[];
extern const BehaviorScript bhvRotatingPlatform[];
extern const BehaviorScript bhvTower[];
extern const BehaviorScript bhvBulletBillCannon[];
extern const BehaviorScript bhvWFBreakableWallRight[];
extern const BehaviorScript bhvWFBreakableWallLeft[];
extern const BehaviorScript bhvKickableBoard[];
extern const BehaviorScript bhvTowerDoor[];
extern const BehaviorScript bhvRotatingCounterClockwise[];
extern const BehaviorScript bhvWFRotatingWoodenPlatform[];
extern const BehaviorScript bhvKoopaShellUnderwater[];
extern const BehaviorScript bhvExitPodiumWarp[];
extern const BehaviorScript bhvFadingWarp[];
extern const BehaviorScript bhvWarp[];
extern const BehaviorScript bhvWarpPipe[];
extern const BehaviorScript bhvWhitePuffExplosion[];
extern const BehaviorScript bhvSpawnedStar[];
extern const BehaviorScript bhvSpawnedStarNoLevelExit[];
extern const BehaviorScript bhvSpawnedBlueCoin[];
extern const BehaviorScript bhvCoinInsideBoo[];
extern const BehaviorScript bhvCoinFormationSpawn[];
extern const BehaviorScript bhvCoinFormation[];
extern const BehaviorScript bhvOneCoin[];
extern const BehaviorScript bhvYellowCoin[];
extern const BehaviorScript bhvTemporaryYellowCoin[];
extern const BehaviorScript bhvThreeCoinsSpawn[];
extern const BehaviorScript bhvTenCoinsSpawn[];
extern const BehaviorScript bhvSingleCoinGetsSpawned[];
extern const BehaviorScript bhvCoinSparkles[];
extern const BehaviorScript bhvGoldenCoinSparkles[];
extern const BehaviorScript bhvWallTinyStarParticle[];
extern const BehaviorScript bhvVertStarParticleSpawner[];
extern const BehaviorScript bhvPoundTinyStarParticle[];
extern const BehaviorScript bhvHorStarParticleSpawner[];
extern const BehaviorScript bhvPunchTinyTriangle[];
extern const BehaviorScript bhvTriangleParticleSpawner[];
extern const BehaviorScript bhvDoorWarp[];
extern const BehaviorScript bhvDoor[];
extern const BehaviorScript bhvGrindel[];
extern const BehaviorScript bhvThwomp[];
extern const BehaviorScript bhvThwomp2[];
extern const BehaviorScript bhvTumblingBridgePlatform[];
extern const BehaviorScript bhvTumblingBridge[];
extern const BehaviorScript bhvBBHTumblingBridge[];
extern const BehaviorScript bhvLLLTumblingBridge[];
extern const BehaviorScript bhvFlame[];
extern const BehaviorScript bhvAnotherElavator[];
extern const BehaviorScript bhvRRElevatorPlatform[];
extern const BehaviorScript bhvHMCElevatorPlatform[];
extern const BehaviorScript bhvWaterMist[];
extern const BehaviorScript bhvBreathParticleSpawner[];
extern const BehaviorScript bhvBreakBoxTriangle[];
extern const BehaviorScript bhvWaterMist2[];
extern const BehaviorScript bhvUnused0DFC[];
extern const BehaviorScript bhvMistCircParticleSpawner[];
extern const BehaviorScript bhvDirtParticleSpawner[];
extern const BehaviorScript bhvUnused0E40[];
extern const BehaviorScript bhvSnowParticleSpawner[];
extern const BehaviorScript bhvWind[];
extern const BehaviorScript bhvEndToad[];
extern const BehaviorScript bhvEndPeach[];
extern const BehaviorScript bhvUnusedParticleSpawn[];
extern const BehaviorScript bhvUkiki[];
extern const BehaviorScript bhvUkikiCageChild[];
extern const BehaviorScript bhvUkikiCageStar[];
extern const BehaviorScript bhvUkikiCage[];
extern const BehaviorScript bhvBitFSSinkingPlatforms[];
extern const BehaviorScript bhvBitFSSinkingCagePlatform[];
extern const BehaviorScript bhvDDDMovingPole[];
extern const BehaviorScript bhvBitFSTiltingInvertedPyramid[];
extern const BehaviorScript bhvSquishablePlatform[];
extern const BehaviorScript bhvCutOutObject[];
extern const BehaviorScript bhvBetaMovingFlamesSpawn[];
extern const BehaviorScript bhvBetaMovingFlames[];
extern const BehaviorScript bhvRRRotatingBridgePlatform[];
extern const BehaviorScript bhvFlamethrower[];
extern const BehaviorScript bhvFlamethrowerFlame[];
extern const BehaviorScript bhvBouncingFireball[];
extern const BehaviorScript bhvBouncingFireballFlame[];
extern const BehaviorScript bhvBowserShockWave[];
extern const BehaviorScript bhvFireParticleSpawner[];
extern const BehaviorScript bhvBlackSmokeMario[];
extern const BehaviorScript bhvBlackSmokeBowser[];
extern const BehaviorScript bhvBlackSmokeUpward[];
extern const BehaviorScript bhvBetaFishSplashSpawner[];
extern const BehaviorScript bhvSpindrift[];
extern const BehaviorScript bhvTowerPlatformGroup[];
extern const BehaviorScript bhvWFSlidingTowerPlatform[];
extern const BehaviorScript bhvWFElevatorTowerPlatform[];
extern const BehaviorScript bhvWFSolidTowerPlatform[];
extern const BehaviorScript bhvLeafParticleSpawner[];
extern const BehaviorScript bhvTreeSnow[];
extern const BehaviorScript bhvTreeLeaf[];
extern const BehaviorScript bhvAnotherTiltingPlatform[];
extern const BehaviorScript bhvSquarishPathMoving[];
extern const BehaviorScript bhvPiranhaPlantBubble[];
extern const BehaviorScript bhvPiranhaPlantWakingBubbles[];
extern const BehaviorScript bhvFloorSwitchAnimatesObject[];
extern const BehaviorScript bhvFloorSwitchGrills[];
extern const BehaviorScript bhvFloorSwitchHardcodedModel[];
extern const BehaviorScript bhvFloorSwitchHiddenObjects[];
extern const BehaviorScript bhvHiddenObject[];
extern const BehaviorScript bhvBreakableBox[];
extern const BehaviorScript bhvPushableMetalBox[];
extern const BehaviorScript bhvHeaveHo[];
extern const BehaviorScript bhvHeaveHoThrowMario[];
extern const BehaviorScript bhvCCMTouchedStarSpawn[];
extern const BehaviorScript bhvUnusedPoundablePlatform[];
extern const BehaviorScript bhvBetaTrampolineTop[];
extern const BehaviorScript bhvBetaTrampolineSpring[];
extern const BehaviorScript bhvJumpingBox[];
extern const BehaviorScript bhvBooCage[];
extern const BehaviorScript bhvStub[];
extern const BehaviorScript bhvIgloo[];
extern const BehaviorScript bhvBowserKey[];
extern const BehaviorScript bhvGrandStar[];
extern const BehaviorScript bhvBetaBooKey[];
extern const BehaviorScript bhvAlphaBooKey[];
extern const BehaviorScript bhvBulletBill[];
extern const BehaviorScript bhvWhitePuffSmoke[];
extern const BehaviorScript bhvUnused1820[];
extern const BehaviorScript bhvBowserTailAnchor[];
extern const BehaviorScript bhvBowser[];
extern const BehaviorScript bhvBowserBodyAnchor[];
extern const BehaviorScript bhvBowserFlameSpawn[];
extern const BehaviorScript bhvTiltingBowserLavaPlatform[];
extern const BehaviorScript bhvFallingBowserPlatform[];
extern const BehaviorScript bhvBlueBowserFlame[];
extern const BehaviorScript bhvFlameFloatingLanding[];
extern const BehaviorScript bhvBlueFlamesGroup[];
extern const BehaviorScript bhvFlameBouncing[];
extern const BehaviorScript bhvFlameMovingForwardGrowing[];
extern const BehaviorScript bhvFlameBowser[];
extern const BehaviorScript bhvFlameLargeBurningOut[];
extern const BehaviorScript bhvBlueFish[];
extern const BehaviorScript bhvTankFishGroup[];
extern const BehaviorScript bhvCheckerboardElevatorGroup[];
extern const BehaviorScript bhvCheckerboardPlatformSub[];
extern const BehaviorScript bhvBowserKeyUnlockDoor[];
extern const BehaviorScript bhvBowserKeyCourseExit[];
extern const BehaviorScript bhvInvisibleObjectsUnderBridge[];
extern const BehaviorScript bhvWaterLevelPillar[];
extern const BehaviorScript bhvDDDWarp[];
extern const BehaviorScript bhvMoatGrills[];
extern const BehaviorScript bhvClockMinuteHand[];
extern const BehaviorScript bhvClockHourHand[];
extern const BehaviorScript bhvMacroUkiki[];
extern const BehaviorScript bhvStub1D0C[];
extern const BehaviorScript bhvLLLRotatingHexagonalPlatform[];
extern const BehaviorScript bhvLLLSinkingRockBlock[];
extern const BehaviorScript bhvStub1D70[];
extern const BehaviorScript bhvLLLMovingOctagonalMeshPlatform[];
extern const BehaviorScript bhvSnowBall[];
extern const BehaviorScript bhvLLLRotatingBlockWithFireBars[];
extern const BehaviorScript bhvLLLRotatingHexFlame[];
extern const BehaviorScript bhvLLLWoodPiece[];
extern const BehaviorScript bhvLLLFloatingWoodBridge[];
extern const BehaviorScript bhvVolcanoFlames[];
extern const BehaviorScript bhvLLLRotatingHexagonalRing[];
extern const BehaviorScript bhvLLLSinkingRectangularPlatform[];
extern const BehaviorScript bhvLLLSinkingSquarePlatforms[];
extern const BehaviorScript bhvLLLTiltingInvertedPyramid[];
extern const BehaviorScript bhvUnused1F30[];
extern const BehaviorScript bhvKoopaShell[];
extern const BehaviorScript bhvKoopaShellFlame[];
extern const BehaviorScript bhvToxBox[];
extern const BehaviorScript bhvPiranhaPlant[];
extern const BehaviorScript bhvLLLHexagonalMesh[];
extern const BehaviorScript bhvLLLBowserPuzzlePiece[];
extern const BehaviorScript bhvLLLBowserPuzzle[];
extern const BehaviorScript bhvTuxiesMother[];
extern const BehaviorScript bhvPenguinBaby[];
extern const BehaviorScript bhvUnused20E0[];
extern const BehaviorScript bhvSmallPenguin[];
extern const BehaviorScript bhvManyBlueFishSpawner[];
extern const BehaviorScript bhvFewBlueFishSpawner[];
extern const BehaviorScript bhvFishSpawner[];
extern const BehaviorScript bhvFishCommon[];
extern const BehaviorScript bhvFish[];
extern const BehaviorScript bhvWDWExpressElevator[];
extern const BehaviorScript bhvWDWExpressElevatorPlatform[];
extern const BehaviorScript bhvChirpChirp[];
extern const BehaviorScript bhvChirpChirpUnused[];
extern const BehaviorScript bhvBub[];
extern const BehaviorScript bhvCheepCheep[];
extern const BehaviorScript bhvExclamationBox[];
extern const BehaviorScript bhvRotatingExclamationMark[];
extern const BehaviorScript bhvPlaysSound[];
extern const BehaviorScript bhvSoundSpawner[];
extern const BehaviorScript bhvRockSolid[];
extern const BehaviorScript bhvBowserSubDoor[];
extern const BehaviorScript bhvBowsersSub[];
extern const BehaviorScript bhvSushiShark[];
extern const BehaviorScript bhvSushiSharkCollisionChild[];
extern const BehaviorScript bhvJRBSlidingBox[];
extern const BehaviorScript bhvShipPart3[];
extern const BehaviorScript bhvInSunkenShip3[];
extern const BehaviorScript bhvSunkenShipPart[];
extern const BehaviorScript bhvUnused243C[];
extern const BehaviorScript bhvSunkenShipPart2[];
extern const BehaviorScript bhvInSunkenShip[];
extern const BehaviorScript bhvInSunkenShip2[];
extern const BehaviorScript bhvMistParticleSpawner[];
extern const BehaviorScript bhvWhitePuff1[];
extern const BehaviorScript bhvWhitePuff2[];
extern const BehaviorScript bhvWhitePuffSmoke2[];
extern const BehaviorScript bhvPurpleSwitchHiddenBoxes[];
extern const BehaviorScript bhvBlueCoinSwitch[];
extern const BehaviorScript bhvHiddenBlueCoin[];
extern const BehaviorScript bhvOpenableCageDoor[];
extern const BehaviorScript bhvOpenableGrill[];
extern const BehaviorScript bhvWaterLevelDiamond[];
extern const BehaviorScript bhvInitializeChangingWaterLevel[];
extern const BehaviorScript bhvTweesterSandParticle[];
extern const BehaviorScript bhvTweester[];
extern const BehaviorScript bhvMerryGoRoundBooManager[];
extern const BehaviorScript bhvPlaysMusicTrackWhenTouched[];
extern const BehaviorScript bhvAnimatedTexture[];
extern const BehaviorScript bhvBooInCastle[];
extern const BehaviorScript bhvBooWithCage[];
extern const BehaviorScript bhvBalconyBigBoo[];
extern const BehaviorScript bhvMerryGoRoundBigBoo[];
extern const BehaviorScript bhvGhostHuntBigBoo[];
extern const BehaviorScript bhvCourtyardBooTriplet[];
extern const BehaviorScript bhvBoo[];
extern const BehaviorScript bhvMerryGoRoundBoo[];
extern const BehaviorScript bhvGhostHuntBoo[];
extern const BehaviorScript bhvHiddenStaircaseStep[];
extern const BehaviorScript bhvBooStaircase[];
extern const BehaviorScript bhvBBHTiltingTrapPlatform[];
extern const BehaviorScript bhvHauntedBookshelf[];
extern const BehaviorScript bhvMeshElevator[];
extern const BehaviorScript bhvMerryGoRound[];
extern const BehaviorScript bhvInsideCannon[];
extern const BehaviorScript bhvBetaBowserAnchor[];
extern const BehaviorScript bhvStaticCheckeredPlatform[];
extern const BehaviorScript bhvUnused2A10[];
extern const BehaviorScript bhvStar[];
extern const BehaviorScript bhvStaticObject[];
extern const BehaviorScript bhvUnused2A54[];
extern const BehaviorScript bhvCastleFloorTrap[];
extern const BehaviorScript bhvFloorTrapInCastle[];
extern const BehaviorScript bhvTree[];
extern const BehaviorScript bhvSparkle[];
extern const BehaviorScript bhvSparkleSpawn[];
extern const BehaviorScript bhvSparkleParticleSpawner[];
extern const BehaviorScript bhvSomeGfx[];
extern const BehaviorScript bhvScuttlebug[];
extern const BehaviorScript bhvScuttlebugSpawn[];
extern const BehaviorScript bhvWhompKingBoss[];
extern const BehaviorScript bhvSmallWhomp[];
extern const BehaviorScript bhvWaterSplash[];
extern const BehaviorScript bhvWaterDroplet[];
extern const BehaviorScript bhvWaterDropletSplash[];
extern const BehaviorScript bhvBubbleSplash[];
extern const BehaviorScript bhvIdleWaterWave[];
extern const BehaviorScript bhvObjectWaterSplash[];
extern const BehaviorScript bhvShallowWaterWave[];
extern const BehaviorScript bhvShallowWaterSplash[];
extern const BehaviorScript bhvObjectWaveTrail[];
extern const BehaviorScript bhvWaveTrail[];
extern const BehaviorScript bhvTinyStrongWindParticle[];
extern const BehaviorScript bhvStrongWindParticle[];
extern const BehaviorScript bhvSLSnowmanWind[];
extern const BehaviorScript bhvSLWalkingPenguin[];
extern const BehaviorScript bhvYellowBall[];
extern const BehaviorScript bhvMario[];
extern const BehaviorScript bhvToadMessage[];
extern const BehaviorScript bhvUnlockDoorStar[];
extern const BehaviorScript bhvInstantActiveWarp[];
extern const BehaviorScript bhvAirborneWarp[];
extern const BehaviorScript bhvHardAirKnockBackWarp[];
extern const BehaviorScript bhvSpinAirborneCircleWarp[];
extern const BehaviorScript bhvDeathWarp[];
extern const BehaviorScript bhvSpinAirborneWarp[];
extern const BehaviorScript bhvFlyingWarp[];
extern const BehaviorScript bhvPaintingStarCollectWarp[];
extern const BehaviorScript bhvPaintingDeathWarp[];
extern const BehaviorScript bhvAirborneDeathWarp[];
extern const BehaviorScript bhvAirborneStarCollectWarp[];
extern const BehaviorScript bhvLaunchStarCollectWarp[];
extern const BehaviorScript bhvLaunchDeathWarp[];
extern const BehaviorScript bhvSwimmingWarp[];
extern const BehaviorScript bhvRandomAnimatedTexture[];
extern const BehaviorScript bhvYellowBackgroundInMenu[];
extern const BehaviorScript bhvMenuButton[];
extern const BehaviorScript bhvMenuButtonManager[];
extern const BehaviorScript bhvActSelectorStarType[];
extern const BehaviorScript bhvActSelector[];
extern const BehaviorScript bhvMovingYellowCoin[];
extern const BehaviorScript bhvMovingBlueCoin[];
extern const BehaviorScript bhvBlueCoinSliding[];
extern const BehaviorScript bhvBlueCoinJumping[];
extern const BehaviorScript bhvSeaweed[];
extern const BehaviorScript bhvSeaweedBundle[];
extern const BehaviorScript bhvBobomb[];
extern const BehaviorScript bhvBobombFuseSmoke[];
extern const BehaviorScript bhvBobombBuddy[];
extern const BehaviorScript bhvBobombBuddyOpensCannon[];
extern const BehaviorScript bhvCannonClosed[];
extern const BehaviorScript bhvWhirlpool[];
extern const BehaviorScript bhvJetStream[];
extern const BehaviorScript bhvMessagePanel[];
extern const BehaviorScript bhvSignOnWall[];
extern const BehaviorScript bhvHomingAmp[];
extern const BehaviorScript bhvCirclingAmp[];
extern const BehaviorScript bhvButterfly[];
extern const BehaviorScript bhvHoot[];
extern const BehaviorScript bhvBetaHoldableObject[];
extern const BehaviorScript bhvCarrySomething1[];
extern const BehaviorScript bhvCarrySomething2[];
extern const BehaviorScript bhvCarrySomething3[];
extern const BehaviorScript bhvCarrySomething4[];
extern const BehaviorScript bhvCarrySomething5[];
extern const BehaviorScript bhvCarrySomething6[];
extern const BehaviorScript bhvObjectBubble[];
extern const BehaviorScript bhvObjectWaterWave[];
extern const BehaviorScript bhvExplosion[];
extern const BehaviorScript bhvBobombBullyDeathSmoke[];
extern const BehaviorScript bhvSmoke[];
extern const BehaviorScript bhvBobombExplosionBubble[];
extern const BehaviorScript bhvBobombExplosionBubble3600[];
extern const BehaviorScript bhvRespawner[];
extern const BehaviorScript bhvSmallBully[];
extern const BehaviorScript bhvBigBully[];
extern const BehaviorScript bhvBigBullyWithMinions[];
extern const BehaviorScript bhvSmallChillBully[];
extern const BehaviorScript bhvBigChillBully[];
extern const BehaviorScript bhvJetStreamRingSpawner[];
extern const BehaviorScript bhvJetStreamWaterRing[];
extern const BehaviorScript bhvMantaRayWaterRing[];
extern const BehaviorScript bhvMantaRayRingManager[];
extern const BehaviorScript bhvBowserBomb[];
extern const BehaviorScript bhvBowserBombExplosion[];
extern const BehaviorScript bhvBowserBombSmoke[];
extern const BehaviorScript bhvCelebrationStar[];
extern const BehaviorScript bhvCelebrationStarSparkle[];
extern const BehaviorScript bhvStarKeyCollectionPuffSpawner[];
extern const BehaviorScript bhvLLLDrawbridgeSpawner[];
extern const BehaviorScript bhvLLLDrawbridge[];
extern const BehaviorScript bhvSmallBomp[];
extern const BehaviorScript bhvLargeBomp[];
extern const BehaviorScript bhvWFSlidingPlatform[];
extern const BehaviorScript bhvMoneybag[];
extern const BehaviorScript bhvMoneybagHidden[];
extern const BehaviorScript bhvPitBowlingBall[];
extern const BehaviorScript bhvFreeBowlingBall[];
extern const BehaviorScript bhvBowlingBall[];
extern const BehaviorScript bhvTTMBowlingBallSpawner[];
extern const BehaviorScript bhvBoBBowlingBallSpawner[];
extern const BehaviorScript bhvTHIBowlingBallSpawner[];
extern const BehaviorScript bhvRRCruiserWing[];
extern const BehaviorScript bhvSpindel[];
extern const BehaviorScript bhvSSLMovingPyramidWall[];
extern const BehaviorScript bhvPyramidElevator[];
extern const BehaviorScript bhvPyramidElevatorTrajectoryMarkerBall[];
extern const BehaviorScript bhvPyramidTop[];
extern const BehaviorScript bhvPyramidTopFragment[];
extern const BehaviorScript bhvPyramidPillarTouchDetector[];
extern const BehaviorScript bhvWaterfallSoundLoop[];
extern const BehaviorScript bhvVolcanoSoundLoop[];
extern const BehaviorScript bhvCastleFlagWaving[];
extern const BehaviorScript bhvBirdsSoundLoop[];
extern const BehaviorScript bhvAmbientSounds[];
extern const BehaviorScript bhvSandSoundLoop[];
extern const BehaviorScript bhvHiddenAt120Stars[];
extern const BehaviorScript bhvSnowmansBottom[];
extern const BehaviorScript bhvSnowmansHead[];
extern const BehaviorScript bhvSnowmansBodyCheckpoint[];
extern const BehaviorScript bhvBigSnowmanWhole[];
extern const BehaviorScript bhvBigBoulder[];
extern const BehaviorScript bhvBigBoulderGenerator[];
extern const BehaviorScript bhvWingCap[];
extern const BehaviorScript bhvMetalCap[];
extern const BehaviorScript bhvNormalCap[];
extern const BehaviorScript bhvVanishCap[];
extern const BehaviorScript bhvStar[];
extern const BehaviorScript bhvStarSpawnCoordinates[];
extern const BehaviorScript bhvHiddenRedCoinStar[];
extern const BehaviorScript bhvRedCoin[];
extern const BehaviorScript bhvBowserCourseRedCoinStar[];
extern const BehaviorScript bhvHiddenStar[];
extern const BehaviorScript bhvHiddenStarTrigger[];
extern const BehaviorScript bhvTTMRollingLog[];
extern const BehaviorScript bhvLLLVolcanoFallingTrap[];
extern const BehaviorScript bhvLLLRollingLog[];
extern const BehaviorScript bhv1UpWalking[];
extern const BehaviorScript bhv1UpRunningAway[];
extern const BehaviorScript bhv1UpSliding[];
extern const BehaviorScript bhv1Up[];
extern const BehaviorScript bhv1UpJumpOnApproach[];
extern const BehaviorScript bhvHidden1Up[];
extern const BehaviorScript bhvHidden1UpTrigger[];
extern const BehaviorScript bhvHidden1UpInPole[];
extern const BehaviorScript bhvHidden1UpInPoleTrigger[];
extern const BehaviorScript bhvHidden1UpInPoleSpawner[];
extern const BehaviorScript bhvControllablePlatform[];
extern const BehaviorScript bhvControllablePlatformSub[];
extern const BehaviorScript bhvBreakableBoxSmall[];
extern const BehaviorScript bhvSlidingSnowMound[];
extern const BehaviorScript bhvSnowMoundSpawn[];
extern const BehaviorScript bhvWDWSquareFloatingPlatform[];
extern const BehaviorScript bhvWDWRectangularFloatingPlatform[];
extern const BehaviorScript bhvJRBFloatingPlatform[];
extern const BehaviorScript bhvArrowLift[];
extern const BehaviorScript bhvOrangeNumber[];
extern const BehaviorScript bhvMantaRay[];
extern const BehaviorScript bhvFallingPillar[];
extern const BehaviorScript bhvFallingPillarHitbox[];
extern const BehaviorScript bhvPillarBase[];
extern const BehaviorScript bhvJRBFloatingBox[];
extern const BehaviorScript bhvDecorativePendulum[];
extern const BehaviorScript bhvTreasureChestsShip[];
extern const BehaviorScript bhvTreasureChestsJRB[];
extern const BehaviorScript bhvTreasureChestsDDD[];
extern const BehaviorScript bhvTreasureChestBottom[];
extern const BehaviorScript bhvTreasureChestTop[];
extern const BehaviorScript bhvMips[];
extern const BehaviorScript bhvYoshi[];
extern const BehaviorScript bhvKoopa[];
extern const BehaviorScript bhvKoopaRaceEndpoint[];
extern const BehaviorScript bhvKoopaFlag[];
extern const BehaviorScript bhvPokey[];
extern const BehaviorScript bhvPokeyBodyPart[];
extern const BehaviorScript bhvSwoop[];
extern const BehaviorScript bhvFlyGuy[];
extern const BehaviorScript bhvGoomba[];
extern const BehaviorScript bhvGoombaTripletSpawner[];
extern const BehaviorScript bhvChainChomp[];
extern const BehaviorScript bhvChainChompChainPart[];
extern const BehaviorScript bhvWoodenPost[];
extern const BehaviorScript bhvChainChompGate[];
extern const BehaviorScript bhvWigglerHead[];
extern const BehaviorScript bhvWigglerBody[];
extern const BehaviorScript bhvEnemyLakitu[];
extern const BehaviorScript bhvCameraLakitu[];
extern const BehaviorScript bhvCloud[];
extern const BehaviorScript bhvCloudPart[];
extern const BehaviorScript bhvSpiny[];
extern const BehaviorScript bhvMontyMole[];
extern const BehaviorScript bhvMontyMoleHole[];
extern const BehaviorScript bhvMontyMoleRock[];
extern const BehaviorScript bhvPlatformOnTrack[];
extern const BehaviorScript bhvTrackBall[];
extern const BehaviorScript bhvSeesawPlatform[];
extern const BehaviorScript bhvFerrisWheelAxle[];
extern const BehaviorScript bhvFerrisWheelPlatform[];
extern const BehaviorScript bhvWaterBombSpawner[];
extern const BehaviorScript bhvWaterBomb[];
extern const BehaviorScript bhvWaterBombShadow[];
extern const BehaviorScript bhvTTCRotatingSolid[];
extern const BehaviorScript bhvTTCPendulum[];
extern const BehaviorScript bhvTTCTreadmill[];
extern const BehaviorScript bhvTTCMovingBar[];
extern const BehaviorScript bhvTTCCog[];
extern const BehaviorScript bhvTTCPitBlock[];
extern const BehaviorScript bhvTTCElevator[];
extern const BehaviorScript bhvTTC2DRotator[];
extern const BehaviorScript bhvTTCSpinner[];
extern const BehaviorScript bhvMrBlizzard[];
extern const BehaviorScript bhvMrBlizzardSnowball[];
extern const BehaviorScript bhvSlidingPlatform2[];
extern const BehaviorScript bhvOctagonalPlatformRotating[];
extern const BehaviorScript bhvAnimatesOnFloorSwitchPress[];
extern const BehaviorScript bhvActivatedBackAndForthPlatform[];
extern const BehaviorScript bhvRecoveryHeart[];
extern const BehaviorScript bhvWaterBombCannon[];
extern const BehaviorScript bhvCannonBarrelBubbles[];
extern const BehaviorScript bhvUnagi[];
extern const BehaviorScript bhvUnagiSubobject[];
extern const BehaviorScript bhvDorrie[];
extern const BehaviorScript bhvHauntedChair[];
extern const BehaviorScript bhvMadPiano[];
extern const BehaviorScript bhvFlyingBookend[];
extern const BehaviorScript bhvBookendSpawn[];
extern const BehaviorScript bhvHauntedBookshelfManager[];
extern const BehaviorScript bhvBookSwitch[];
extern const BehaviorScript bhvFirePiranhaPlant[];
extern const BehaviorScript bhvSmallPiranhaFlame[];
extern const BehaviorScript bhvFireSpitter[];
extern const BehaviorScript bhvFlyguyFlame[];
extern const BehaviorScript bhvSnufit[];
extern const BehaviorScript bhvSnufitBalls[];
extern const BehaviorScript bhvHorizontalGrindel[];
extern const BehaviorScript bhvEyerokBoss[];
extern const BehaviorScript bhvEyerokHand[];
extern const BehaviorScript bhvKlepto[];
extern const BehaviorScript bhvBird[];
extern const BehaviorScript bhvRacingPenguin[];
extern const BehaviorScript bhvPenguinRaceFinishLine[];
extern const BehaviorScript bhvPenguinRaceShortcutCheck[];
extern const BehaviorScript bhvCoffinSpawner[];
extern const BehaviorScript bhvCoffin[];
extern const BehaviorScript bhvClamShell[];
extern const BehaviorScript bhvSkeeter[];
extern const BehaviorScript bhvSkeeterWave[];
extern const BehaviorScript bhvSwingPlatform[];
extern const BehaviorScript bhvDonutPlatformSpawner[];
extern const BehaviorScript bhvDonutPlatform[];
extern const BehaviorScript bhvDDDPole[];
extern const BehaviorScript bhvRedCoinStarMarker[];
extern const BehaviorScript bhvTripletButterfly[];
extern const BehaviorScript bhvBubba[];
extern const BehaviorScript bhvBeginningLakitu[];
extern const BehaviorScript bhvBeginningPeach[];
extern const BehaviorScript bhvEndBirds1[];
extern const BehaviorScript bhvEndBirds2[];
extern const BehaviorScript bhvIntroScene[];
extern const BehaviorScript bhvUnusedFakeStar[];

extern const BehaviorScript bhv2DPhysics[];
extern const BehaviorScript bhvLegacyScrollTexture[];

#ifdef PORT_MOP_OBJS
#include "src/extras/mop/include_behaviors.h"
#endif

#ifdef RM2C_HAS_SCROLLING_TEXTURES
extern const BehaviorScript editor_Scroll_Texture[];
extern const BehaviorScript RM_Scroll_Texture[];
#endif

#endif // BEHAVIOR_DATA_H
