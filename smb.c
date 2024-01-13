// Super Mario Bros. in C
// by PixelBrushArt
// based on the disassembly by doppelganger

// Libaries
#include <stdio.h>
#include <stdint.h>

// Type definitions
#if __STDC_VERSION__ >= 199901L
    // If we're using C99+, we can just use uint8
    typedef uint8_t byte;
#else
    // Otherwise we need to use unsigned chars
    typedef unsigned char byte;
#endif

//-------------------------------------------------------------------------------------
// DEFINES
// This is basically where all Variables are declared.
// Some of the defines in the original decomp refer to addresses,
// which'll be replaced with functions as progress on this game continues.

/*
;-------------------------------------------------------------------------------------
;DEFINES

;NES specific hardware defines

PPU_CTRL_REG1         = 0x2000
PPU_CTRL_REG2         = 0x2001
PPU_STATUS            = 0x2002
PPU_SPR_ADDR          = 0x2003
PPU_SPR_DATA          = 0x2004
PPU_SCROLL_REG        = 0x2005
PPU_ADDRESS           = 0x2006
PPU_DATA              = 0x2007

SND_REGISTER          = 0x4000
SND_SQUARE1_REG       = 0x4000
SND_SQUARE2_REG       = 0x4004
SND_TRIANGLE_REG      = 0x4008
SND_NOISE_REG         = 0x400c
SND_DELTA_REG         = 0x4010
SND_MASTERCTRL_REG    = 0x4015

SPR_DMA               = 0x4014
JOYPAD_PORT           = 0x4016
JOYPAD_PORT1          = 0x4016
JOYPAD_PORT2          = 0x4017
*/

// GAME SPECIFIC DEFINES

byte ObjectOffset = 0x08;

byte FrameCounter = 0x09;

/*
byte SavedJoypadBits= 0x06fc
SavedJoypad1Bits      = 0x06fc
SavedJoypad2Bits      = 0x06fd
JoypadBitMask         = 0x074a
JoypadOverride        = 0x0758

A_B_Buttons           = 0x0a
PreviousA_B_Buttons   = 0x0d
Up_Down_Buttons       = 0x0b
Left_Right_Buttons    = 0x0c

GameEngineSubroutine  = 0x0e

Mirror_PPU_CTRL_REG1  = 0x0778
Mirror_PPU_CTRL_REG2  = 0x0779

OperMode              = 0x0770
OperMode_Task         = 0x0772
ScreenRoutineTask     = 0x073c
*/

byte GamePauseStatus       ; // 0x0776
byte GamePauseTimer        ; // 0x0777

byte DemoAction            ; // 0x0717
byte DemoActionTimer       ; // 0x0718

byte TimerControl          ; // 0x0747
byte IntervalTimerControl  ; // 0x077f

byte Timers                ; // 0x0780
byte SelectTimer           ; // 0x0780
byte PlayerAnimTimer       ; // 0x0781
byte JumpSwimTimer         ; // 0x0782
byte RunningTimer          ; // 0x0783
byte BlockBounceTimer      ; // 0x0784
byte SideCollisionTimer    ; // 0x0785
byte JumpspringTimer       ; // 0x0786
byte GameTimerCtrlTimer    ; // 0x0787
byte ClimbSideTimer        ; // 0x0789
byte EnemyFrameTimer       ; // 0x078a
byte FrenzyEnemyTimer      ; // 0x078f
byte BowserFireBreathTimer ; // 0x0790
byte StompTimer            ; // 0x0791
byte AirBubbleTimer        ; // 0x0792
byte ScrollIntervalTimer   ; // 0x0795
byte EnemyIntervalTimer    ; // 0x0796
byte BrickCoinTimer        ; // 0x079d
byte InjuryTimer           ; // 0x079e
byte StarInvincibleTimer   ; // 0x079f
byte ScreenTimer           ; // 0x07a0
byte WorldEndTimer         ; // 0x07a1
byte DemoTimer             ; // 0x07a2

// This is prolly a pointer
byte Sprite_Data           ; // 0x0200
 
byte Sprite_Y_Position     ; // 0x0200
byte Sprite_Tilenumber     ; // 0x0201
byte Sprite_Attributes     ; // 0x0202
byte Sprite_X_Position     ; // 0x0203
 
byte ScreenEdge_PageLoc    ; // 0x071a
byte ScreenEdge_X_Pos      ; // 0x071c
byte ScreenLeft_PageLoc    ; // 0x071a
byte ScreenRight_PageLoc   ; // 0x071b
byte ScreenLeft_X_Pos      ; // 0x071c
byte ScreenRight_X_Pos     ; // 0x071d
 
byte PlayerFacingDir       ; // 0x33
byte DestinationPageLoc    ; // 0x34
byte VictoryWalkControl    ; // 0x35
byte ScrollFractional      ; // 0x0768
byte PrimaryMsgCounter     ; // 0x0719
byte SecondaryMsgCounter   ; // 0x0749

byte HorizontalScroll      ; // 0x073f
byte VerticalScroll        ; // 0x0740
byte ScrollLock            ; // 0x0723
byte ScrollThirtyTwo       ; // 0x073d
byte Player_X_Scroll       ; // 0x06ff
byte Player_Pos_ForScroll  ; // 0x0755
byte ScrollAmount          ; // 0x0775

byte AreaData              ; // 0xe7
byte AreaDataLow           ; // 0xe7
byte AreaDataHigh          ; // 0xe8
byte EnemyData             ; // 0xe9
byte EnemyDataLow          ; // 0xe9
byte EnemyDataHigh         ; // 0xea

byte AreaParserTaskNum     ; // 0x071f
byte ColumnSets            ; // 0x071e
byte CurrentPageLoc        ; // 0x0725
byte CurrentColumnPos      ; // 0x0726
byte BackloadingFlag       ; // 0x0728
byte BehindAreaParserFlag  ; // 0x0729
byte AreaObjectPageLoc     ; // 0x072a
byte AreaObjectPageSel     ; // 0x072b
byte AreaDataOffset        ; // 0x072c
byte AreaObjOffsetBuffer   ; // 0x072d
byte AreaObjectLength      ; // 0x0730
byte StaircaseControl      ; // 0x0734
byte AreaObjectHeight      ; // 0x0735
byte MushroomLedgeHalfLen  ; // 0x0736
byte EnemyDataOffset       ; // 0x0739
byte EnemyObjectPageLoc    ; // 0x073a
byte EnemyObjectPageSel    ; // 0x073b
byte MetatileBuffer        ; // 0x06a1
byte BlockBufferColumnPos  ; // 0x06a0
byte CurrentNTAddr_Low     ; // 0x0721
byte CurrentNTAddr_High    ; // 0x0720
byte AttributeBuffer       ; // 0x03f9

byte LoopCommand           ; // 0x0745
 
byte DisplayDigits         ; // 0x07d7
byte TopScoreDisplay       ; // 0x07d7
byte ScoreAndCoinDisplay   ; // 0x07dd
byte PlayerScoreDisplay    ; // 0x07dd
byte GameTimerDisplay      ; // 0x07f8
byte DigitModifier         ; // 0x0134
 
byte VerticalFlipFlag      ; // 0x0109
byte FloateyNum_Control    ; // 0x0110
byte ShellChainCounter     ; // 0x0125
byte FloateyNum_Timer      ; // 0x012c
byte FloateyNum_X_Pos      ; // 0x0117
byte FloateyNum_Y_Pos      ; // 0x011e
byte FlagpoleFNum_Y_Pos    ; // 0x010d
byte FlagpoleFNum_YMFDummy ; // 0x010e
byte FlagpoleScore         ; // 0x010f
byte FlagpoleCollisionYPos ; // 0x070f
byte StompChainCounter     ; // 0x0484
 
byte VRAM_Buffer1_Offset   ; // 0x0300
byte VRAM_Buffer1          ; // 0x0301
byte VRAM_Buffer2_Offset   ; // 0x0340
byte VRAM_Buffer2          ; // 0x0341
byte VRAM_Buffer_AddrCtrl  ; // 0x0773
byte Sprite0HitDetectFlag  ; // 0x0722
byte DisableScreenFlag     ; // 0x0774
byte DisableIntermediate   ; // 0x0769
byte ColorRotateOffset     ; // 0x06d4
 
byte TerrainControl        ; // 0x0727
byte AreaStyle             ; // 0x0733
byte ForegroundScenery     ; // 0x0741
byte BackgroundScenery     ; // 0x0742
byte CloudTypeOverride     ; // 0x0743
byte BackgroundColorCtrl   ; // 0x0744
byte AreaType              ; // 0x074e
byte AreaAddrsLOffset      ; // 0x074f
byte AreaPointer           ; // 0x0750
 
byte PlayerEntranceCtrl    ; // 0x0710
byte GameTimerSetting      ; // 0x0715
byte AltEntranceControl    ; // 0x0752
byte EntrancePage          ; // 0x0751
byte NumberOfPlayers       ; // 0x077a
byte WarpZoneControl       ; // 0x06d6
byte ChangeAreaTimer       ; // 0x06de
 
byte MultiLoopCorrectCntr  ; // 0x06d9
byte MultiLoopPassCntr     ; // 0x06da
 
byte FetchNewGameTimerFlag ; // 0x0757
byte GameTimerExpiredFlag  ; // 0x0759
 
byte PrimaryHardMode       ; // 0x076a
byte SecondaryHardMode     ; // 0x06cc
byte WorldSelectNumber     ; // 0x076b
byte WorldSelectEnableFlag ; // 0x07fc
byte ContinueWorld         ; // 0x07fd
 
byte CurrentPlayer         ; // 0x0753
byte PlayerSize            ; // 0x0754
byte PlayerStatus          ; // 0x0756
 
byte OnscreenPlayerInfo    ; // 0x075a
byte NumberofLives         ; // 0x075a ;used by current player
byte HalfwayPage           ; // 0x075b
byte LevelNumber           ; // 0x075c ;the actual dash number
byte Hidden1UpFlag         ; // 0x075d
byte CoinTally             ; // 0x075e
byte WorldNumber           ; // 0x075f
byte AreaNumber            ; // 0x0760 ;internal number used to find areas
 
byte CoinTallyFor1Ups      ; // 0x0748
 
byte OffscreenPlayerInfo   ; // 0x0761
byte OffScr_NumberofLives  ; // 0x0761 ;used by offscreen player
byte OffScr_HalfwayPage    ; // 0x0762
byte OffScr_LevelNumber    ; // 0x0763
byte OffScr_Hidden1UpFlag  ; // 0x0764
byte OffScr_CoinTally      ; // 0x0765
byte OffScr_WorldNumber    ; // 0x0766
byte OffScr_AreaNumber     ; // 0x0767
 
byte BalPlatformAlignment  ; // 0x03a0
byte Platform_X_Scroll     ; // 0x03a1
byte PlatformCollisionFlag ; // 0x03a2
byte YPlatformTopYPos      ; // 0x0401
byte YPlatformCenterYPos   ; // 0x58
 
byte BrickCoinTimerFlag    ; // 0x06bc
byte StarFlagTaskControl   ; // 0x0746
 
byte PseudoRandomBitReg    ; // 0x07a7
byte WarmBootValidation    ; // 0x07ff
 
byte SprShuffleAmtOffset   ; // 0x06e0
byte SprShuffleAmt         ; // 0x06e1
byte SprDataOffset         ; // 0x06e4
byte Player_SprDataOffset  ; // 0x06e4
byte Enemy_SprDataOffset   ; // 0x06e5
byte Block_SprDataOffset   ; // 0x06ec
byte Alt_SprDataOffset     ; // 0x06ec
byte Bubble_SprDataOffset  ; // 0x06ee
byte FBall_SprDataOffset   ; // 0x06f1
byte Misc_SprDataOffset    ; // 0x06f3
byte SprDataOffset_Ctrl    ; // 0x03ee
 
byte Player_State          ; // 0x1d
byte Enemy_State           ; // 0x1e
byte Fireball_State        ; // 0x24
byte Block_State           ; // 0x26
byte Misc_State            ; // 0x2a
 
byte Player_MovingDir      ; // 0x45
byte Enemy_MovingDir       ; // 0x46
 
byte SprObject_X_Speed     ; // 0x57
byte Player_X_Speed        ; // 0x57
byte Enemy_X_Speed         ; // 0x58
byte Fireball_X_Speed      ; // 0x5e
byte Block_X_Speed         ; // 0x60
byte Misc_X_Speed          ; // 0x64
 
byte Jumpspring_FixedYPos  ; // 0x58
byte JumpspringAnimCtrl    ; // 0x070e
byte JumpspringForce       ; // 0x06db
 
byte SprObject_PageLoc     ; // 0x6d
byte Player_PageLoc        ; // 0x6d
byte Enemy_PageLoc         ; // 0x6e
byte Fireball_PageLoc      ; // 0x74
byte Block_PageLoc         ; // 0x76
byte Misc_PageLoc          ; // 0x7a
byte Bubble_PageLoc        ; // 0x83


byte SprObject_X_Position  ; // 0x86
byte Player_X_Position     ; // 0x86
byte Enemy_X_Position      ; // 0x87
byte Fireball_X_Position   ; // 0x8d
byte Block_X_Position      ; // 0x8f
byte Misc_X_Position       ; // 0x93
byte Bubble_X_Position     ; // 0x9c
 
byte SprObject_Y_Speed     ; // 0x9f
byte Player_Y_Speed        ; // 0x9f
byte Enemy_Y_Speed         ; // 0xa0
byte Fireball_Y_Speed      ; // 0xa6
byte Block_Y_Speed         ; // 0xa8
byte Misc_Y_Speed          ; // 0xac
 
byte SprObject_Y_HighPos   ; // 0xb5
byte Player_Y_HighPos      ; // 0xb5
byte Enemy_Y_HighPos       ; // 0xb6
byte Fireball_Y_HighPos    ; // 0xbc
byte Block_Y_HighPos       ; // 0xbe
byte Misc_Y_HighPos        ; // 0xc2
byte Bubble_Y_HighPos      ; // 0xcb
 
byte SprObject_Y_Position  ; // 0xce
byte Player_Y_Position     ; // 0xce
byte Enemy_Y_Position      ; // 0xcf
byte Fireball_Y_Position   ; // 0xd5
byte Block_Y_Position      ; // 0xd7
byte Misc_Y_Position       ; // 0xdb
byte Bubble_Y_Position     ; // 0xe4
 
byte SprObject_Rel_XPos    ; // 0x03ad
byte Player_Rel_XPos       ; // 0x03ad
byte Enemy_Rel_XPos        ; // 0x03ae
byte Fireball_Rel_XPos     ; // 0x03af
byte Bubble_Rel_XPos       ; // 0x03b0
byte Block_Rel_XPos        ; // 0x03b1
byte Misc_Rel_XPos         ; // 0x03b3
 
byte SprObject_Rel_YPos    ; // 0x03b8
byte Player_Rel_YPos       ; // 0x03b8
byte Enemy_Rel_YPos        ; // 0x03b9
byte Fireball_Rel_YPos     ; // 0x03ba
byte Bubble_Rel_YPos       ; // 0x03bb
byte Block_Rel_YPos        ; // 0x03bc
byte Misc_Rel_YPos         ; // 0x03be

byte SprObject_SprAttrib   ; // 0x03c4
byte Player_SprAttrib      ; // 0x03c4
byte Enemy_SprAttrib       ; // 0x03c5
 
byte SprObject_X_MoveForce ; // 0x0400
byte Enemy_X_MoveForce     ; // 0x0401
 
byte SprObject_YMF_Dummy   ; // 0x0416
byte Player_YMF_Dummy      ; // 0x0416
byte Enemy_YMF_Dummy       ; // 0x0417
byte Bubble_YMF_Dummy      ; // 0x042c
 
byte SprObject_Y_MoveForce ; // 0x0433
byte Player_Y_MoveForce    ; // 0x0433
byte Enemy_Y_MoveForce     ; // 0x0434
byte Block_Y_MoveForce     ; // 0x043c
 
byte DisableCollisionDet   ; // 0x0716
byte Player_CollisionBits  ; // 0x0490
byte Enemy_CollisionBits   ; // 0x0491
 
byte SprObj_BoundBoxCtrl   ; // 0x0499
byte Player_BoundBoxCtrl   ; // 0x0499
byte Enemy_BoundBoxCtrl    ; // 0x049a
byte Fireball_BoundBoxCtrl ; // 0x04a0
byte Misc_BoundBoxCtrl     ; // 0x04a2
 
byte EnemyFrenzyBuffer     ; // 0x06cb
byte EnemyFrenzyQueue      ; // 0x06cd
byte Enemy_Flag            ; // 0x0f
byte Enemy_ID              ; // 0x16
 
byte PlayerGfxOffset       ; // 0x06d5
byte Player_XSpeedAbsolute ; // 0x0700
byte FrictionAdderHigh     ; // 0x0701
byte FrictionAdderLow      ; // 0x0702
byte RunningSpeed          ; // 0x0703
byte SwimmingFlag          ; // 0x0704
byte Player_X_MoveForce    ; // 0x0705
byte DiffToHaltJump        ; // 0x0706
byte JumpOrigin_Y_HighPos  ; // 0x0707
byte JumpOrigin_Y_Position ; // 0x0708
byte VerticalForce         ; // 0x0709
byte VerticalForceDown     ; // 0x070a
byte PlayerChangeSizeFlag  ; // 0x070b
byte PlayerAnimTimerSet    ; // 0x070c
byte PlayerAnimCtrl        ; // 0x070d
byte DeathMusicLoaded      ; // 0x0712
byte FlagpoleSoundQueue    ; // 0x0713
byte CrouchingFlag         ; // 0x0714
byte MaximumLeftSpeed      ; // 0x0450
byte MaximumRightSpeed     ; // 0x0456
 
byte SprObject_OffscrBits  ; // 0x03d0
byte Player_OffscreenBits  ; // 0x03d0
byte Enemy_OffscreenBits   ; // 0x03d1
byte FBall_OffscreenBits   ; // 0x03d2
byte Bubble_OffscreenBits  ; // 0x03d3
byte Block_OffscreenBits   ; // 0x03d4
byte Misc_OffscreenBits    ; // 0x03d6
byte EnemyOffscrBitsMasked ; // 0x03d8
 
byte Cannon_Offset         ; // 0x046a
byte Cannon_PageLoc        ; // 0x046b
byte Cannon_X_Position     ; // 0x0471
byte Cannon_Y_Position     ; // 0x0477
byte Cannon_Timer          ; // 0x047d
 
byte Whirlpool_Offset      ; // 0x046a
byte Whirlpool_PageLoc     ; // 0x046b
byte Whirlpool_LeftExtent  ; // 0x0471
byte Whirlpool_Length      ; // 0x0477
byte Whirlpool_Flag        ; // 0x047d
 
byte VineFlagOffset        ; // 0x0398
byte VineHeight            ; // 0x0399
byte VineObjOffset         ; // 0x039a
byte VineStart_Y_Position  ; // 0x039d
 
byte Block_Orig_YPos       ; // 0x03e4
byte Block_BBuf_Low        ; // 0x03e6
byte Block_Metatile        ; // 0x03e8
byte Block_PageLoc2        ; // 0x03ea
byte Block_RepFlag         ; // 0x03ec
byte Block_ResidualCounter ; // 0x03f0
byte Block_Orig_XPos       ; // 0x03f1
 
byte BoundingBox_UL_XPos   ; // 0x04ac
byte BoundingBox_UL_YPos   ; // 0x04ad
byte BoundingBox_DR_XPos   ; // 0x04ae
byte BoundingBox_DR_YPos   ; // 0x04af
byte BoundingBox_UL_Corner ; // 0x04ac
byte BoundingBox_LR_Corner ; // 0x04ae
byte EnemyBoundingBoxCoord ; // 0x04b0
 
byte PowerUpType           ; // 0x39
 
byte FireballBouncingFlag  ; // 0x3a
byte FireballCounter       ; // 0x06ce
byte FireballThrowingTimer ; // 0x0711
 
byte HammerEnemyOffset     ; // 0x06ae
byte JumpCoinMiscOffset    ; // 0x06b7
 
byte Block_Buffer_1        ; // 0x0500
byte Block_Buffer_2        ; // 0x05d0
 
byte HammerThrowingTimer   ; // 0x03a2
byte HammerBroJumpTimer    ; // 0x3c
byte Misc_Collision_Flag   ; // 0x06be
 
byte RedPTroopaOrigXPos    ; // 0x0401
byte RedPTroopaCenterYPos  ; // 0x58
 
byte XMovePrimaryCounter   ; // 0xa0
byte XMoveSecondaryCounter ; // 0x58
 
byte CheepCheepMoveMFlag   ; // 0x58
byte CheepCheepOrigYPos    ; // 0x0434
byte BitMFilter            ; // 0x06dd
 
byte LakituReappearTimer   ; // 0x06d1
byte LakituMoveSpeed       ; // 0x58
byte LakituMoveDirection   ; // 0xa0
 
byte FirebarSpinState_Low  ; // 0x58
byte FirebarSpinState_High ; // 0xa0
byte FirebarSpinSpeed      ; // 0x0388
byte FirebarSpinDirection  ; // 0x34
 
byte DuplicateObj_Offset   ; // 0x06cf
byte NumberofGroupEnemies  ; // 0x06d3
 
byte BlooperMoveCounter    ; // 0xa0
byte BlooperMoveSpeed      ; // 0x58
 
byte BowserBodyControls    ; // 0x0363
byte BowserFeetCounter     ; // 0x0364
byte BowserMovementSpeed   ; // 0x0365
byte BowserOrigXPos        ; // 0x0366
byte BowserFlameTimerCtrl  ; // 0x0367
byte BowserFront_Offset    ; // 0x0368
byte BridgeCollapseOffset  ; // 0x0369
byte BowserGfxFlag         ; // 0x036a
byte BowserHitPoints       ; // 0x0483
byte MaxRangeFromOrigin    ; // 0x06dc
 
byte BowserFlamePRandomOfs ; // 0x0417
 
byte PiranhaPlantUpYPos    ; // 0x0417
byte PiranhaPlantDownYPos  ; // 0x0434
byte PiranhaPlant_Y_Speed  ; // 0x58
byte PiranhaPlant_MoveFlag ; // 0xa0
 
byte FireworksCounter      ; // 0x06d7
byte ExplosionGfxCounter   ; // 0x58
byte ExplosionTimerCounter ; // 0xa0

// Sound related defines
byte Squ2_NoteLenBuffer    ; // 0x07b3
byte Squ2_NoteLenCounter   ; // 0x07b4
byte Squ2_EnvelopeDataCtrl ; // 0x07b5
byte Squ1_NoteLenCounter   ; // 0x07b6
byte Squ1_EnvelopeDataCtrl ; // 0x07b7
byte Tri_NoteLenBuffer     ; // 0x07b8
byte Tri_NoteLenCounter    ; // 0x07b9
byte Noise_BeatLenCounter  ; // 0x07ba
byte Squ1_SfxLenCounter    ; // 0x07bb
byte Squ2_SfxLenCounter    ; // 0x07bd
byte Sfx_SecondaryCounter  ; // 0x07be
byte Noise_SfxLenCounter   ; // 0x07bf

byte PauseSoundQueue       ; // 0xfa
byte Square1SoundQueue     ; // 0xff
byte Square2SoundQueue     ; // 0xfe
byte NoiseSoundQueue       ; // 0xfd
byte AreaMusicQueue        ; // 0xfb
byte EventMusicQueue       ; // 0xfc

byte Square1SoundBuffer    ; // 0xf1
byte Square2SoundBuffer    ; // 0xf2
byte NoiseSoundBuffer      ; // 0xf3
byte AreaMusicBuffer       ; // 0xf4
byte EventMusicBuffer      ; // 0x07b1
byte PauseSoundBuffer      ; // 0x07b2

byte MusicData             ; // 0xf5
byte MusicDataLow          ; // 0xf5
byte MusicDataHigh         ; // 0xf6
byte MusicOffset_Square2   ; // 0xf7
byte MusicOffset_Square1   ; // 0xf8
byte MusicOffset_Triangle  ; // 0xf9
byte MusicOffset_Noise     ; // 0x07b0
 
byte NoteLenLookupTblOfs   ; // 0xf0
byte DAC_Counter           ; // 0x07c0
byte NoiseDataLoopbackOfs  ; // 0x07c1
byte NoteLengthTblAdder    ; // 0x07c4
byte AreaMusicBuffer_Alt   ; // 0x07c5
byte PauseModeFlag         ; // 0x07c6
byte GroundMusicHeaderOfs  ; // 0x07c7
byte AltRegContentFlag     ; // 0x07ca

//-------------------------------------------------------------------------------------
// CONSTANTS

// Sound effects constants
#define Sfx_SmallJump 0b10000000
#define Sfx_Flagpole 0b01000000
#define Sfx_Fireball 0b00100000
#define Sfx_PipeDown_Injury 0b00010000
#define Sfx_EnemySmack 0b00001000
#define Sfx_EnemyStomp 0b00000100
#define Sfx_Bump 0b00000010
#define Sfx_BigJump 0b00000001

#define Sfx_BowserFall 0b10000000
#define Sfx_ExtraLife 0b01000000
#define Sfx_PowerUpGrab 0b00100000
#define Sfx_TimerTick 0b00010000
#define Sfx_Blast 0b00001000
#define Sfx_GrowVine 0b00000100
#define Sfx_GrowPowerUp 0b00000010
#define Sfx_CoinGrab 0b00000001

#define Sfx_BowserFlame 0b00000010
#define Sfx_BrickShatter 0b00000001

// Music constants
#define Silence 0b10000000

#define StarPowerMusic 0b01000000
#define PipeIntroMusic 0b00100000
#define CloudMusic 0b00010000
#define CastleMusic 0b00001000
#define UndergroundMusic 0b00000100
#define WaterMusic 0b00000010
#define GroundMusic 0b00000001

#define TimeRunningOutMusic 0b01000000
#define EndOfLevelMusic 0b00100000
#define AltGameOverMusic 0b00010000
#define EndOfCastleMusic 0b00001000
#define VictoryMusic 0b00000100
#define GameOverMusic 0b00000010
#define DeathMusic 0b00000001

// Enemy object constants 
#define GreenKoopa 0x00
#define BuzzyBeetle 0x02
#define RedKoopa 0x03
#define HammerBro 0x05
#define Goomba 0x06
#define Bloober 0x07
#define BulletBill_FrenzyVar 0x08
#define GreyCheepCheep 0x0a
#define RedCheepCheep 0x0b
#define Podoboo 0x0c
#define PiranhaPlant 0x0d
#define GreenParatroopaJump 0x0e
#define RedParatroopa 0x0f
#define GreenParatroopaFly 0x10
#define Lakitu 0x11
#define Spiny 0x12
#define FlyCheepCheepFrenzy 0x14
#define FlyingCheepCheep 0x14
#define BowserFlame 0x15
#define Fireworks 0x16
#define BBill_CCheep_Frenzy 0x17
#define Stop_Frenzy 0x18
#define Bowser 0x2d
#define PowerUpObject 0x2e
#define VineObject 0x2f
#define FlagpoleFlagObject 0x30
#define StarFlagObject 0x31
#define JumpspringObject 0x32
#define BulletBill_CannonVar 0x33
#define RetainerObject 0x35
#define TallEnemy 0x09

// Level Number Constants
#define World1 0
#define World2 1
#define World3 2
#define World4 3
#define World5 4
#define World6 5
#define World7 6
#define World8 7

#define Level1 0
#define Level2 1
#define Level3 2
#define Level4 3

// Controller bits
#define A_Button 0b10000000
#define B_Button 0b01000000
#define Select_Button 0b00100000
#define Start_Button 0b00010000
#define Up_Dir 0b00001000
#define Down_Dir 0b00000100
#define Left_Dir 0b00000010
#define Right_Dir 0b00000001

#define TitleScreenModeValue 0
#define GameModeValue 1
#define VictoryModeValue 2
#define GameOverModeValue 3

int main() {
    printf("Hello, World!\n");
    return 0;
}