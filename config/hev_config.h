#ifdef CONFIG_TOP
#include "proffieboard_v2_config.h"
#define NUM_BLADES 6
#define NUM_BUTTONS 2
#define VOLUME 1500
#define BOOT_VOLUME 150
#define SAVE_VOLUME
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 3.0
//If not disabled, Armor Readout play back floats around current Armor value.
#define DISABLE_NO_REPEAT_RANDOM
#define IDLE_OFF_TIME 9999999
// #define HEV_RANDOM_EVENT_INTERVAL_MS 10000
// #define HEV_RANDOM_HAZARD_CHANCE 95
#define HEV_HEALTH_ANNOUNCEMENT_CHANCE 100  // defaults to 50%
// #define LIGHTS_ON_RESETS_HEALTH_ARMOR  // if not defined, resumes levels where you left off
#define MOUNT_SD_SETTING

#endif

#ifdef CONFIG_PROP
#include "../props/hev.h"
#endif

// All HALF-LIFE sfx audio can be found in the game's "sound" directory.
// Specifically, HEV Suit voice lines can be found within the "fvox" dir.
// The music tracks can be found in the "media" dir in the root folder.

#ifdef CONFIG_PRESETS

using OnDemandVolumeLevel = TransitionEffectL<TrConcat<TrSmoothFade<200>,AlphaL<Gradient<Blue,Green>,SmoothStep<VolumeLevel,Int<-1>>>,TrDelay<1000>,TrSmoothFade<500>>,EFFECT_VOLUME_LEVEL>;

Preset armor[] = {

{ "hev;HEVcommon", "HEVcommon/tracks/hl1_ost/10 Valve Theme [Extended].wav",
// Left front (inner LED =1)
StylePtr<Layers<
  ColorSelect<AltF,TrFade<300>,Mix<Int<16384>,Moccasin,Black>,TransitionLoop<Black,TrConcat<TrInstant,AlphaL<ImperialYellow,LayerFunctions<LinearSectionF<Int<5400>,Int<10900>>,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<333>,AlphaL<ImperialYellow,LinearSectionF<Int<16384>,Int<10900>>>,TrDelay<333>>>,RandomBlink<3000,Sparkle<Black,Green,3000,900>>,Pulsing<Mix<Int<16384>,Red,Black>,Black,800>,Pulsing<Gradient<Yellow,Black>,Gradient<Black,Black,Yellow>,800>,Pulsing<Gradient<Orange,Orange,Red,Red>,Gradient<Red,Red,Orange>,800>,Pulsing<Mix<Int<16384>,Black,Blue>,Black,800>>,
  // Physical Damage
  TransitionEffectL<TrSelect<EffectRandomF<EFFECT_CLASH>,TrConcat<TrSparkX<Red,Int<100>,Int<200>>,TrSparkX<Red,Int<100>,Int<300>>>,TrConcat<TrInstant,BrownNoiseFlicker<Black,Red,50>,TrFadeX<WavLen<EFFECT_CLASH>>>,TrConcat<TrInstant,BlinkingX<Red,Black,Scale<RandomF,Int<300>,Int<700>>,Scale<RandomF,Int<0>,Int<1000>>>,TrFadeX<WavLen<EFFECT_CLASH>>>>,EFFECT_CLASH>,
  // Environmental Damage
  TransitionEffectL<TrConcat<TrInstant,ColorSelect<AltF,TrInstant,Mix<Int<16384>,Moccasin,Black>,Blinking<Black,Green,200,400>,Blinking<Yellow,Black,180,400>,Blinking<Yellow,Orange,200,400>,Blinking<ViolentViolet,Flamingo,200,400>,Blinking<SafetyOrange,Red,200,400>,Blinking<Cyan,BlueRibbon,200,400>>,TrJoin<TrFade<500>,TrBoing<500,4>>>,EFFECT_STUN>,
  // Armor Readout
  TransitionEffectL<TrConcat<TrInstant,Orange,TrFade<240>,Black,TrInstant,Orange,TrFade<240>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>>,EFFECT_USER8>,
  // Health Warning Beeps
  TransitionEffectL<TrConcat<TrInstant,Red,TrDelay<400>,Black,TrDelay<50>,Yellow,TrDelay<400>,Black,TrDelay<50>,Red,TrDelay<400>,Black,TrDelay<100>>,EFFECT_USER1_STEP2>,
  // Health Alert
  TransitionEffectL<TrConcat<TrDelay<1400>,Black,TrFade<300>,Cylon<Red,5,20,Gradient<Red,Red,Green>,33,50,1>,TrDelayX<Percentage<WavLen<EFFECT_USER1_STEP2>,70>>,TrFade<300>,Black,TrFade<300>>,EFFECT_USER1_STEP2>,
  // Armor Compromised
  TransitionEffectL<TrConcat<TrInstant,Cylon<Red,20,150,Red,20,150,1>,TrDelayX<WavLen<EFFECT_USER2_STEP2>>>,EFFECT_USER2_STEP2>,
  // Healing
  LockupTrL<StripesX<Int<200>,Int<3000>,
      White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
      Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrConcat<TrInstant,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<25>,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<100>,
    TrWipeInSparkTip<White,350,100>,Cyan,TrWipeIn<200>,Black,TrInstant,
    StripesX<Int<200>,Scale<Trigger<EFFECT_LOCKUP_BEGIN,Int<10000>,Int<1000>,Int<1>>,Int<300>,Int<3000>>,
    White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
    Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrDelay<10000>>,TrInstant,SaberBase::LOCKUP_NORMAL>,
  TransitionEffectL<TrConcat<TrInstant,Pulsing<Green,Cyan,400>,TrFade<2000>>,EFFECT_LOCKUP_END>,
  //Armor fill
  LockupTrL<Stripes<200,1000,Black,Black,DeepSkyBlue,Black,Black,Orange>,TrConcat<TrInstant,Layers<
    Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Black,TrDelay<100>,White,TrFade<500>,Orange,TrFade<500>>,TrInstant,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
  TransitionEffectL<TrConcat<TrInstant,Strobe<Black,Orange,15,20>,TrDelay<200>,DeepSkyBlue,TrFade<500>,Black,TrInstant>,EFFECT_LB_END>,
  InOutTrL<TrConcat<TrInstant,White,TrDelay<800>,TrSmoothFade<1200>>,TrInstant>,
  OnDemandVolumeLevel
>>(),

// Left shoulder (inner LED =1)
StylePtr<Layers<
  ColorSelect<AltF,TrFade<300>,Mix<Int<16384>,Moccasin,Black>,TransitionLoop<Black,TrConcat<TrInstant,AlphaL<ImperialYellow,LayerFunctions<LinearSectionF<Int<5400>,Int<10900>>,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<333>,AlphaL<ImperialYellow,LinearSectionF<Int<16384>,Int<10900>>>,TrDelay<333>>>,RandomBlink<3000,Sparkle<Black,Green,3000,900>>,Pulsing<Mix<Int<16384>,Red,Black>,Black,800>,Pulsing<Gradient<Yellow,Black>,Gradient<Black,Black,Yellow>,800>,Pulsing<Gradient<Orange,Orange,Red,Red>,Gradient<Red,Red,Orange>,800>,Pulsing<Mix<Int<16384>,Black,Blue>,Black,800>>,
  // Physical Damage
  TransitionEffectL<TrSelect<EffectRandomF<EFFECT_CLASH>,TrConcat<TrSparkX<Red,Int<100>,Int<200>>,TrSparkX<Red,Int<100>,Int<300>>>,TrConcat<TrInstant,BrownNoiseFlicker<Black,Red,50>,TrFadeX<WavLen<EFFECT_CLASH>>>,TrConcat<TrInstant,BlinkingX<Red,Black,Scale<RandomF,Int<300>,Int<700>>,Scale<RandomF,Int<0>,Int<1000>>>,TrFadeX<WavLen<EFFECT_CLASH>>>>,EFFECT_CLASH>,
  // Environmental Damage
  TransitionEffectL<TrConcat<TrInstant,ColorSelect<AltF,TrInstant,Mix<Int<16384>,Moccasin,Black>,Blinking<Black,Green,200,400>,Blinking<Yellow,Black,180,400>,Blinking<Yellow,Orange,200,400>,Blinking<ViolentViolet,Flamingo,200,400>,Blinking<SafetyOrange,Red,200,400>,Blinking<Cyan,BlueRibbon,200,400>>,TrJoin<TrFade<500>,TrBoing<500,4>>>,EFFECT_STUN>,
  // Armor Readout
  TransitionEffectL<TrConcat<TrInstant,Orange,TrFade<240>,Black,TrInstant,Orange,TrFade<240>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>>,EFFECT_USER8>,
  // Health Warning Beeps
  TransitionEffectL<TrConcat<TrInstant,Red,TrDelay<400>,Black,TrDelay<50>,Yellow,TrDelay<400>,Black,TrDelay<50>,Red,TrDelay<400>,Black,TrDelay<100>>,EFFECT_USER1_STEP2>,
  // Health Alert
  TransitionEffectL<TrConcat<TrDelay<1400>,Black,TrFade<300>,Cylon<Red,5,20,Gradient<Red,Red,Green>,33,50,1>,TrDelayX<Percentage<WavLen<EFFECT_USER1_STEP2>,70>>,TrFade<300>,Black,TrFade<300>>,EFFECT_USER1_STEP2>,
  // Armor Compromised
  TransitionEffectL<TrConcat<TrInstant,Cylon<Red,20,150,Red,20,150,1>,TrDelayX<WavLen<EFFECT_USER2_STEP2>>>,EFFECT_USER2_STEP2>,
  // Healing
  LockupTrL<StripesX<Int<200>,Int<3000>,
      White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
      Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrConcat<TrInstant,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<25>,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<100>,
    TrWipeInSparkTip<White,350,100>,Cyan,TrWipeIn<200>,Black,TrInstant,
    StripesX<Int<200>,Scale<Trigger<EFFECT_LOCKUP_BEGIN,Int<10000>,Int<1000>,Int<1>>,Int<300>,Int<3000>>,
    White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
    Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrDelay<10000>>,TrInstant,SaberBase::LOCKUP_NORMAL>,
  TransitionEffectL<TrConcat<TrInstant,Pulsing<Green,Cyan,400>,TrFade<2000>>,EFFECT_LOCKUP_END>,
  //Armor fill
  LockupTrL<Stripes<200,1000,Black,Black,DeepSkyBlue,Black,Black,Orange>,
    TrConcat<TrInstant,Layers<
    Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Black,TrDelay<100>,White,TrFade<500>,Orange,TrFade<500>>,TrInstant,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
  TransitionEffectL<TrConcat<TrInstant,Strobe<Black,Orange,15,20>,TrDelay<200>,DeepSkyBlue,TrFade<500>,Black,TrInstant>,EFFECT_LB_END>,
  InOutTrL<TrConcat<TrInstant,White,TrDelay<800>,TrSmoothFade<1200>>,TrInstant>,
  OnDemandVolumeLevel
>>(),

// Left back (bottom = LED 1)
StylePtr<Layers<
  ColorSelect<AltF,TrFade<300>,Mix<Int<16384>,Red,Black>,TransitionLoop<Black,TrConcat<TrInstant,AlphaL<ImperialYellow,LayerFunctions<LinearSectionF<Int<5400>,Int<10900>>,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<333>,AlphaL<ImperialYellow,LinearSectionF<Int<16384>,Int<10900>>>,TrDelay<333>>>,RandomBlink<3000,Sparkle<Black,Green,3000,900>>,Pulsing<Mix<Int<16384>,Red,Black>,Black,800>,Pulsing<Gradient<Yellow,Black>,Gradient<Black,Black,Yellow>,800>,Pulsing<Gradient<Orange,Orange,Red,Red>,Gradient<Red,Red,Orange>,800>,Pulsing<Mix<Int<16384>,Black,Blue>,Black,800>>,
  // Physical Damage
  TransitionEffectL<TrSelect<EffectRandomF<EFFECT_CLASH>,TrConcat<TrSparkX<Red,Int<100>,Int<200>>,TrSparkX<Red,Int<100>,Int<300>>>,TrConcat<TrInstant,BrownNoiseFlicker<Black,Red,50>,TrFadeX<WavLen<EFFECT_CLASH>>>,TrConcat<TrInstant,BlinkingX<Red,Black,Scale<RandomF,Int<300>,Int<700>>,Scale<RandomF,Int<0>,Int<1000>>>,TrFadeX<WavLen<EFFECT_CLASH>>>>,EFFECT_CLASH>,
  // Environmental Damage
  TransitionEffectL<TrConcat<TrInstant,ColorSelect<AltF,TrInstant,Mix<Int<16384>,Moccasin,Black>,Blinking<Black,Green,200,400>,Blinking<Yellow,Black,180,400>,Blinking<Yellow,Orange,200,400>,Blinking<ViolentViolet,Flamingo,200,400>,Blinking<SafetyOrange,Red,200,400>,Blinking<Cyan,BlueRibbon,200,400>>,TrJoin<TrFade<500>,TrBoing<500,4>>>,EFFECT_STUN>,
  // Armor Readout
  TransitionEffectL<TrConcat<TrInstant,Orange,TrFade<240>,Black,TrInstant,Orange,TrFade<240>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>>,EFFECT_USER8>,
  // Health Warning Beeps
  TransitionEffectL<TrConcat<TrInstant,Red,TrDelay<400>,Black,TrDelay<50>,Yellow,TrDelay<400>,Black,TrDelay<50>,Red,TrDelay<400>,Black,TrDelay<100>>,EFFECT_USER1_STEP2>,
  // Health Alert
  TransitionEffectL<TrConcat<TrDelay<1400>,Black,TrFade<300>,Cylon<Red,5,20,Gradient<Red,Red,Green>,33,50,1>,TrDelayX<Percentage<WavLen<EFFECT_USER1_STEP2>,70>>,TrFade<300>,Black,TrFade<300>>,EFFECT_USER1_STEP2>,
  // Armor Compromised
  TransitionEffectL<TrConcat<TrInstant,Cylon<Red,20,150,Red,20,150,1>,TrDelayX<WavLen<EFFECT_USER2_STEP2>>>,EFFECT_USER2_STEP2>,
  // Healing
  LockupTrL<StripesX<Int<200>,Int<3000>,
      White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
      Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrConcat<TrInstant,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<25>,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<100>,
    TrWipeInSparkTip<White,350,100>,Cyan,TrWipeIn<200>,Black,TrInstant,
    StripesX<Int<200>,Scale<Trigger<EFFECT_LOCKUP_BEGIN,Int<10000>,Int<1000>,Int<1>>,Int<300>,Int<3000>>,
    White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
    Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrDelay<10000>>,TrInstant,SaberBase::LOCKUP_NORMAL>,
  TransitionEffectL<TrConcat<TrInstant,Pulsing<Green,Cyan,400>,TrFade<2000>>,EFFECT_LOCKUP_END>,
  //Armor fill
  LockupTrL<Stripes<200,1000,Black,Black,DeepSkyBlue,Black,Black,Orange>,
    TrConcat<TrInstant,Layers<
    Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Black,TrDelay<100>,White,TrFade<500>,Orange,TrFade<500>>,TrInstant,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
  TransitionEffectL<TrConcat<TrInstant,Strobe<Black,Orange,15,20>,TrDelay<200>,DeepSkyBlue,TrFade<500>,Black,TrInstant>,EFFECT_LB_END>,
  InOutTrL<TrConcat<TrInstant,White,TrDelay<800>,TrSmoothFade<1200>>,TrInstant>,
  OnDemandVolumeLevel
>>(),

// Right back (bottom = LED 1)
StylePtr<Layers<
  ColorSelect<AltF,TrFade<300>,Mix<Int<16384>,Red,Black>,TransitionLoop<Black,TrConcat<TrInstant,AlphaL<ImperialYellow,LayerFunctions<LinearSectionF<Int<5400>,Int<10900>>,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<333>,AlphaL<ImperialYellow,LinearSectionF<Int<16384>,Int<10900>>>,TrDelay<333>>>,RandomBlink<3000,Sparkle<Black,Green,3000,900>>,Pulsing<Mix<Int<16384>,Red,Black>,Black,800>,Pulsing<Gradient<Yellow,Black>,Gradient<Black,Black,Yellow>,800>,Pulsing<Gradient<Orange,Orange,Red,Red>,Gradient<Red,Red,Orange>,800>,Pulsing<Mix<Int<16384>,Black,Blue>,Black,800>>,
  // Physical Damage
  TransitionEffectL<TrSelect<EffectRandomF<EFFECT_CLASH>,TrConcat<TrSparkX<Red,Int<100>,Int<200>>,TrSparkX<Red,Int<100>,Int<300>>>,TrConcat<TrInstant,BrownNoiseFlicker<Black,Red,50>,TrFadeX<WavLen<EFFECT_CLASH>>>,TrConcat<TrInstant,BlinkingX<Red,Black,Scale<RandomF,Int<300>,Int<700>>,Scale<RandomF,Int<0>,Int<1000>>>,TrFadeX<WavLen<EFFECT_CLASH>>>>,EFFECT_CLASH>,
  // Environmental Damage
  TransitionEffectL<TrConcat<TrInstant,ColorSelect<AltF,TrInstant,Mix<Int<16384>,Moccasin,Black>,Blinking<Black,Green,200,400>,Blinking<Yellow,Black,180,400>,Blinking<Yellow,Orange,200,400>,Blinking<ViolentViolet,Flamingo,200,400>,Blinking<SafetyOrange,Red,200,400>,Blinking<Cyan,BlueRibbon,200,400>>,TrJoin<TrFade<500>,TrBoing<500,4>>>,EFFECT_STUN>,
  // Armor Readout
  TransitionEffectL<TrConcat<TrInstant,Orange,TrFade<240>,Black,TrInstant,Orange,TrFade<240>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>>,EFFECT_USER8>,
  // Health Warning Beeps
  TransitionEffectL<TrConcat<TrInstant,Red,TrDelay<400>,Black,TrDelay<50>,Yellow,TrDelay<400>,Black,TrDelay<50>,Red,TrDelay<400>,Black,TrDelay<100>>,EFFECT_USER1_STEP2>,
  // Health Alert
  TransitionEffectL<TrConcat<TrDelay<1400>,Black,TrFade<300>,Cylon<Red,5,20,Gradient<Red,Red,Green>,33,50,1>,TrDelayX<Percentage<WavLen<EFFECT_USER1_STEP2>,70>>,TrFade<300>,Black,TrFade<300>>,EFFECT_USER1_STEP2>,
  // Armor Compromised
  TransitionEffectL<TrConcat<TrInstant,Cylon<Red,20,150,Red,20,150,1>,TrDelayX<WavLen<EFFECT_USER2_STEP2>>>,EFFECT_USER2_STEP2>,
  // Healing
  LockupTrL<StripesX<Int<200>,Int<3000>,
      White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
      Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrConcat<TrInstant,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<25>,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<100>,
    TrWipeInSparkTip<White,350,100>,Cyan,TrWipeIn<200>,Black,TrInstant,
    StripesX<Int<200>,Scale<Trigger<EFFECT_LOCKUP_BEGIN,Int<10000>,Int<1000>,Int<1>>,Int<300>,Int<3000>>,
    White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
    Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrDelay<10000>>,TrInstant,SaberBase::LOCKUP_NORMAL>,
  TransitionEffectL<TrConcat<TrInstant,Pulsing<Green,Cyan,400>,TrFade<2000>>,EFFECT_LOCKUP_END>,
  //Armor fill
  LockupTrL<Stripes<200,1000,Black,Black,DeepSkyBlue,Black,Black,Orange>,
    TrConcat<TrInstant,Layers<
    Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Black,TrDelay<100>,White,TrFade<500>,Orange,TrFade<500>>,TrInstant,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
  TransitionEffectL<TrConcat<TrInstant,Strobe<Black,Orange,15,20>,TrDelay<200>,DeepSkyBlue,TrFade<500>,Black,TrInstant>,EFFECT_LB_END>,
  InOutTrL<TrConcat<TrInstant,White,TrDelay<800>,TrSmoothFade<1200>>,TrInstant>,
  OnDemandVolumeLevel
>>(),

// Right shoulder (inner LED =1)
StylePtr<Layers<
  ColorSelect<AltF,TrFade<300>,Mix<Int<16384>,Moccasin,Black>,TransitionLoop<Black,TrConcat<TrInstant,AlphaL<ImperialYellow,LayerFunctions<LinearSectionF<Int<5400>,Int<10900>>,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<333>,AlphaL<ImperialYellow,LinearSectionF<Int<16384>,Int<10900>>>,TrDelay<333>>>,RandomBlink<3000,Sparkle<Black,Green,3000,900>>,Pulsing<Mix<Int<16384>,Red,Black>,Black,800>,Pulsing<Gradient<Yellow,Black>,Gradient<Black,Black,Yellow>,800>,Pulsing<Gradient<Orange,Orange,Red,Red>,Gradient<Red,Red,Orange>,800>,Pulsing<Mix<Int<16384>,Black,Blue>,Black,800>>,
  // Physical Damage
  TransitionEffectL<TrSelect<EffectRandomF<EFFECT_CLASH>,TrConcat<TrSparkX<Red,Int<100>,Int<200>>,TrSparkX<Red,Int<100>,Int<300>>>,TrConcat<TrInstant,BrownNoiseFlicker<Black,Red,50>,TrFadeX<WavLen<EFFECT_CLASH>>>,TrConcat<TrInstant,BlinkingX<Red,Black,Scale<RandomF,Int<300>,Int<700>>,Scale<RandomF,Int<0>,Int<1000>>>,TrFadeX<WavLen<EFFECT_CLASH>>>>,EFFECT_CLASH>,
  // Environmental Damage
  TransitionEffectL<TrConcat<TrInstant,ColorSelect<AltF,TrInstant,Mix<Int<16384>,Moccasin,Black>,Blinking<Black,Green,200,400>,Blinking<Yellow,Black,180,400>,Blinking<Yellow,Orange,200,400>,Blinking<ViolentViolet,Flamingo,200,400>,Blinking<SafetyOrange,Red,200,400>,Blinking<Cyan,BlueRibbon,200,400>>,TrJoin<TrFade<500>,TrBoing<500,4>>>,EFFECT_STUN>,
  // Armor Readout
  TransitionEffectL<TrConcat<TrInstant,Orange,TrFade<240>,Black,TrInstant,Orange,TrFade<240>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>>,EFFECT_USER8>,
  // Health Warning Beeps
  TransitionEffectL<TrConcat<TrInstant,Red,TrDelay<400>,Black,TrDelay<50>,Yellow,TrDelay<400>,Black,TrDelay<50>,Red,TrDelay<400>,Black,TrDelay<100>>,EFFECT_USER1_STEP2>,
  // Health Alert
  TransitionEffectL<TrConcat<TrDelay<1400>,Black,TrFade<300>,Cylon<Red,5,20,Gradient<Red,Red,Green>,33,50,1>,TrDelayX<Percentage<WavLen<EFFECT_USER1_STEP2>,70>>,TrFade<300>,Black,TrFade<300>>,EFFECT_USER1_STEP2>,
  // Armor Compromised
  TransitionEffectL<TrConcat<TrInstant,Cylon<Red,20,150,Red,20,150,1>,TrDelayX<WavLen<EFFECT_USER2_STEP2>>>,EFFECT_USER2_STEP2>,
  // Healing
  LockupTrL<StripesX<Int<200>,Int<3000>,
      White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
      Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrConcat<TrInstant,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<25>,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<100>,
    TrWipeInSparkTip<White,350,100>,Cyan,TrWipeIn<200>,Black,TrInstant,
    StripesX<Int<200>,Scale<Trigger<EFFECT_LOCKUP_BEGIN,Int<10000>,Int<1000>,Int<1>>,Int<300>,Int<3000>>,
    White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
    Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrDelay<10000>>,TrInstant,SaberBase::LOCKUP_NORMAL>,
  TransitionEffectL<TrConcat<TrInstant,Pulsing<Green,Cyan,400>,TrFade<2000>>,EFFECT_LOCKUP_END>,
  //Armor fill
  LockupTrL<Stripes<200,1000,Black,Black,DeepSkyBlue,Black,Black,Orange>,
    TrConcat<TrInstant,Layers<
    Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Black,TrDelay<100>,White,TrFade<500>,Orange,TrFade<500>>,TrInstant,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
  TransitionEffectL<TrConcat<TrInstant,Strobe<Black,Orange,15,20>,TrDelay<200>,DeepSkyBlue,TrFade<500>,Black,TrInstant>,EFFECT_LB_END>,
  InOutTrL<TrConcat<TrInstant,White,TrDelay<800>,TrSmoothFade<1200>>,TrInstant>,
  OnDemandVolumeLevel
>>(),

// Right front (inner LED =1)
StylePtr<Layers<
  ColorSelect<AltF,TrFade<300>,Mix<Int<16384>,Moccasin,Black>,TransitionLoop<Black,TrConcat<TrInstant,AlphaL<ImperialYellow,LayerFunctions<LinearSectionF<Int<5400>,Int<10900>>,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<333>,AlphaL<ImperialYellow,LinearSectionF<Int<16384>,Int<10900>>>,TrDelay<333>>>,RandomBlink<3000,Sparkle<Black,Green,3000,900>>,Pulsing<Mix<Int<16384>,Red,Black>,Black,800>,Pulsing<Gradient<Yellow,Black>,Gradient<Black,Black,Yellow>,800>,Pulsing<Gradient<Orange,Orange,Red,Red>,Gradient<Red,Red,Orange>,800>,Pulsing<Mix<Int<16384>,Black,Blue>,Black,800>>,
  // Physical Damage
  TransitionEffectL<TrSelect<EffectRandomF<EFFECT_CLASH>,TrConcat<TrSparkX<Red,Int<100>,Int<200>>,TrSparkX<Red,Int<100>,Int<300>>>,TrConcat<TrInstant,BrownNoiseFlicker<Black,Red,50>,TrFadeX<WavLen<EFFECT_CLASH>>>,TrConcat<TrInstant,BlinkingX<Red,Black,Scale<RandomF,Int<300>,Int<700>>,Scale<RandomF,Int<0>,Int<1000>>>,TrFadeX<WavLen<EFFECT_CLASH>>>>,EFFECT_CLASH>,
  // Environmental Damage
  TransitionEffectL<TrConcat<TrInstant,ColorSelect<AltF,TrInstant,Mix<Int<16384>,Moccasin,Black>,Blinking<Black,Green,200,400>,Blinking<Yellow,Black,180,400>,Blinking<Yellow,Orange,200,400>,Blinking<ViolentViolet,Flamingo,200,400>,Blinking<SafetyOrange,Red,200,400>,Blinking<Cyan,BlueRibbon,200,400>>,TrJoin<TrFade<500>,TrBoing<500,4>>>,EFFECT_STUN>,
  // Armor Readout
  TransitionEffectL<TrConcat<TrInstant,Orange,TrFade<240>,Black,TrInstant,Orange,TrFade<240>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>,Black,TrFade<1000>,
    Layers<Black,AlphaL<Gradient<Orange,Blue>,SmoothStep<Variation,Int<-1>>>>,TrFade<1000>>,EFFECT_USER8>,
  // Health Warning Beeps
  TransitionEffectL<TrConcat<TrInstant,Red,TrDelay<400>,Black,TrDelay<50>,Yellow,TrDelay<400>,Black,TrDelay<50>,Red,TrDelay<400>,Black,TrDelay<100>>,EFFECT_USER1_STEP2>,
  // Health Alert
  TransitionEffectL<TrConcat<TrDelay<1400>,Black,TrFade<300>,Cylon<Red,5,20,Gradient<Red,Red,Green>,33,50,1>,TrDelayX<Percentage<WavLen<EFFECT_USER1_STEP2>,70>>,TrFade<300>,Black,TrFade<300>>,EFFECT_USER1_STEP2>,
  // Armor Compromised
  TransitionEffectL<TrConcat<TrInstant,Cylon<Red,20,150,Red,20,150,1>,TrDelayX<WavLen<EFFECT_USER2_STEP2>>>,EFFECT_USER2_STEP2>,
  // Healing
  LockupTrL<StripesX<Int<200>,Int<3000>,
      White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
      Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrConcat<TrInstant,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<25>,
    Layers<Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,
    Black,TrDelay<100>,
    TrWipeInSparkTip<White,350,100>,Cyan,TrWipeIn<200>,Black,TrInstant,
    StripesX<Int<200>,Scale<Trigger<EFFECT_LOCKUP_BEGIN,Int<10000>,Int<1000>,Int<1>>,Int<300>,Int<3000>>,
    White,White,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,
    Green,Green,Green,Green,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>,Mix<Int<26000>,Cyan,Black>>,
    TrDelay<10000>>,TrInstant,SaberBase::LOCKUP_NORMAL>,
  TransitionEffectL<TrConcat<TrInstant,Pulsing<Green,Cyan,400>,TrFade<2000>>,EFFECT_LOCKUP_END>,
  //Armor fill
  LockupTrL<Stripes<200,1000,Black,Black,DeepSkyBlue,Black,Black,Orange>,
    TrConcat<TrInstant,Layers<
    Black,AlphaL<White,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<27400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<16384>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<White,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Layers<
    Black,AlphaL<Orange,LinearSectionF<Int<5400>,Int<10900>>>>,TrDelay<50>,Black,TrDelay<100>,White,TrFade<500>,Orange,TrFade<500>>,TrInstant,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
  TransitionEffectL<TrConcat<TrInstant,Strobe<Black,Orange,15,20>,TrDelay<200>,DeepSkyBlue,TrFade<500>,Black,TrInstant>,EFFECT_LB_END>,
  InOutTrL<TrConcat<TrInstant,White,TrDelay<800>,TrSmoothFade<1200>>,TrInstant>,
  OnDemandVolumeLevel
>>(),
"hev"
},


// LED1
// LinearSectionF<Int<5400>,Int<10900>>

// LED2
// LinearSectionF<Int<16384>,Int<10900>>

// LED3
// LinearSectionF<Int<27400>,Int<10900>>


};

BladeConfig blades[] = {

{ 0,
  SubBlade (15, 17, WS281XBladePtr<18, bladePin, Color8::RGB, PowerPINS<bladePowerPin2, bladePowerPin3> >() ),  // // Left front (inner LED =1)
  SubBlade (12, 14, NULL),  // Left shoulder (inner LED =1)
  SubBlade (9, 11, NULL),  // Left back (bottom = LED 1)
  SubBlade (6, 8, NULL),  // Right back (bottom = LED 1)
  SubBladeReverse (3, 5, NULL),  // Right shoulder (inner LED =1)
  SubBladeReverse (0, 2, NULL),  // Right front (inner LED =1)
CONFIGARRAY(armor),
"HEV_Suit_Save"}
};

#endif

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif




