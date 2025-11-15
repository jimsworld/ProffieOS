//=====================================================================//
//                        H A L F - L I F E                            //
//                      ─────────────────────                          //
//              Hazardous Environment Suit Diagnostics                 //
//              H.E.V. Mark V - Configuration Protocol                 //
//---------------------------------------------------------------------//
//                      PROPERTY OF BLACK MESA                         //
//---------------------------------------------------------------------//
//                      Created by James Nash,                         //
//           with fundamental support and contributions from           //
//                 Fredrik Hubinette & Brian Conner                    //
//=====================================================================//

//=====================================================================//
//                    H.E.V. SUIT - USAGE GUIDE                        //
//                    ─────────────────────────                        //
// **2 BUTTON SETUP**                                                  //
//                                                                     //
// ▪ PWR Button:                                                       //
//     - Long-click           - ON/OFF                                 //
//     - Hold                 - Recharge Armor                         //
//     - Double-click         - Toggle track                           //
//     - Triple-click         - Next preset                            //
// ▪ AUX Button:                                                       //
//     - Hold                 - Recharge Health                        //
//     - Single-click         - Deactivate Hazard                      //
//     - Double-click         - Armor Readout                          //
//     - Triple-click         - Previous preset                        //
//=====================================================================//

//=====================================================================//
//                     AUDIO SYSTEM CATEGORIES                         //
//                    ─────────────────────────                        //
//                                                                     //
// All HALF-LIFE audio files can be found in the game's "sound" folder.//
// Specifically, HEV voice lines can be found within "fvox" folder.    //
// The music tracks can be found in the "media" folder in the root dir.//
//                                                                     //
//----------------------  HEV VOICE LINES -----------------------------//
//                                                                     //
// - armor**.wav             - Armor Readouts                          //
// - health**.wav            - Health Alerts                           //
// - armor_compromised**.wav - Plays when armor drops to 0             //
// - boot01.wav              - HEV welcome message (shortened)         //
// - boot02.wav              - HEV welcome message (original)          //
// - hazard**.wav            - Hazard Alerts                           //
// - minor_laceration.wav    - Plays Minor Lacerations Detected quote  //
// - minor_fracture.wav      - Plays Minor Fracture Detected quote     //
// - major_laceration.wav    - Plays Major Lacerations Detected quote  //
// - major_fracture.wav      - Plays Major Fracture Detected quote     //
// - morphine.wav            - Plays after a Major Detected quote      //
//                                                                     //
//------------------------ HEV UI SOUNDS ------------------------------//
//                                                                     //
// - armor_alarm.wav         - Short alert // plays when damage ≥ 30   //
// - battery.wav             - Battery SFX // armor pickup             //
// - bgnlb.wav               - Start armor charge                      //
// - bgnlock.wav             - Start health charge                     //
// - death.wav               - Heart monitor flatline // health = 0    //
// - endlb.wav               - End armor charge                        //
// - endlock.wav             - End health charge                       //
// - font.wav                - Weapon select SFX (placeholder)         //
// - fuzz**.wav              - Subtle alert // precedes armor**.wav    //
// - in.wav                  - Torch OFF                               //
// - lb.wav                  - Looping armor charge                    //
// - lock.wav                - Looping health charge                   //
// - medkit.wav              - Medkit SFX // health pickup             //
// - out.wav                 - Torch ON                                //
// - armor00.wav             - No Armor SFX // Armor = 0               //
//                                                                     //
//---------------------- ENVIRONMENTAL SFX ----------------------------//
//                                                                     //
// - stun**.wav              - Hazard SFX // alt001–alt006 = hazards   //
// - clsh**.wav              - Physical impacts, slashes, collisions   //
//                                                                     //
//----------------------------- MISC ----------------------------------//
//                                                                     //
// - blank.wav               - Placeholder inside altchng/ folder      //
//                                                                     //
//---------------------- Clash Sounds Setup ---------------------------//
//                                                                     //
// ▪ When we use Clashes for the HEV Suit, the suit may offer audible  //
//   feedback based on the type of Clash recieved and might apply      //
//   medical assistance.                                               //
// ▪ This is explained further in the section below;                   //
//   SYSTEM & VOICE BREAKDOWN                                          //
//                                                                     //
// ▪ Clash sfx (ENVIRONMENTAL SFX) must be set up as sub-sub sounds:   //
//   - https://pod.hubbe.net/sound/sub-sub-sounds.html                 //
//                                                                     //
// ▪ If we have 8 levels of severity, we will need 16 various          //
//   Clash sfx (ENVIRONMENTAL SFX).                                    //
//   This is because Clashes have 2 types of *injuries*, Lacerations   //
//   and Fractures. So we should have 8 Laceration sfx and 8           //
//   Fracture sfx.                                                     //
//                                                                     //
// ▪ Create the clsh/ folder in the root of the sound font.            //
// ▪ Inside clsh/, create the following sub-folders:                   //
//   ├── 000/     - Lowest severity                                    //
//   ├── 001/                                                          //
//   ├── 002/                                                          //
//   ├── 003/                                                          //
//   ├── 004/                                                          //
//   ├── 005/                                                          //
//   ├── 006/                                                          //
//   └── 007/     - Highest severity                                   //
//                                                                     //
// ▪ Each NNN/ folder, must contain:                                   //
//   ├── 000.wav                                                       //
//   └── 001.wav                                                       //
//     - 000.wav would be a "Laceration" sound, and 001.wav would be   //
//       a "Fracture" sound.                                           //
//     - The NNN would be determined by the strength and 000/001 would //
//       be selected randomly.                                         //
//                                                                     //
//------------------ Random Hazard Sounds Setup -----------------------//
//                                                                     //
// ▪ Random Hazards are explained in the section below;                //
//   SYSTEM & VOICE BREAKDOWN                                          //
//                                                                     //
// ▪ Since there are 6 Random Hazards, the following must be set up in //
//   the sound font:                                                   //
//                                                                     //
// ▪ Create 7 alt**/ folders in the root of the sound font:            //
//   ├── alt00/     - None                                             //
//   ├── alt01/     - Biohazard                                        //
//   ├── alt02/     - Radiation                                        //
//   ├── alt03/     - Blood Toxins                                     //
//   ├── alt04/     - Chemical                                         //
//   ├── alt05/     - Heat                                             //
//   └── alt06/     - Shock                                            //
// ▪ Each alt**/ folder must contain:                                  //
//   ├── hazard00.wav                                                  //
//   └── hazard01.wav                                                  //
//     - These are the Hazard Alerts (HEV VOICE LINES) for that folder.//
//                                                                     //
// ▪ Inside each alt**/ folder, create an altchng/ folder:             //
// ▪ Each altchng/ folder must contain:                                //
//   └── blank.wav                                                     //
//     - A silent placeholder to satisfy the altchng structure.        //
//                                                                     //
// ▪ Inside each alt**/ folder, create a stun/ folder:                 //
// ▪ Each stun/ folder must contain:                                   //
//   └── stun**.wav                                                    //
//     - These are the (ENVIRONMENTAL SFX) that should match the Hazard//
//       (e.g. spark, burn, Geiger counter).                           //
//     - Include as many different variations as you'd like.           //
//                                                                     //
// ▪ All alt**/ folders (alt00–alt06) must have the **same number** of //
//    WAVs inside including **all** sub folders.                       //
//=====================================================================//

//=====================================================================//
//                     SYSTEM & VOICE BREAKDOWN                        //
//                    ─────────────────────────                        //
//                                                                     //
//------------------------- Health & Armor ----------------------------//
//                                                                     //
// ▪ The HEV suit has two main resources: Health & Armor.              //
//   - Both have a maximum value of 100.                               //
//   - Active only while the suit is ON.                               //
//                                                                     //
//------------------------- Armor Alarm -------------------------------//
//                                                                     //
// ▪ If Armor reaches 0:                                               //
//   - Configurable chance to play armor_compromised.wav               //
//     (HEV VOICE LINE). 100% default.                                 //
//                                                                     //
//------------------------- Armor Alerts ------------------------------//
//                                                                     //
// ▪ When Clash damage ≥ 30:                                           //
//   - armor_alarm.wav will play. (HEV UI SOUNDS)                      //
//                                                                     //
//------------------------- Armor Readout -----------------------------//
//                                                                     //
// ▪ Armor Readout is used to hear the current Armor value.            //
// ▪ Triggered by double-clicking AUX.                                 //
// ▪ Activates a sequence of (HEV UI SOUNDS) then (HEV VOICE LINE):    //
//   - Subtle alert fuzz**.wav → Armor Readout armor**.wav.            //
// ▪ If Armor = 0:                                                     //
//   - Plays armor00.wav (HEV UI SOUNDS)                               //
//   - No (HEV VOICE LINE)                                             //
//                                                                     //
//------------------------- Random Hazards ----------------------------//
//                                                                     //
// ▪ Always damages Armor first directly, then Health.                 //
// ▪ Triggers at intervals and also chance-based.                      //
// ▪ Active only while the suit is ON.                                 //
// ▪ When triggered, randomly selects 1 of 6 Hazards:                  //
//   - Biohazard, Radiation, Blood Toxins, Chemical, Heat or Shock.    //
// ▪ If Biohazard, Radiation, Blood Toxins or Chemical are triggered,  //
//   periodic damage will linger over time.                            //
// ▪ Heat and Shock do not have lingering damage and should be         //
//   cleared immediately by clicking AUX.                              //
//                                                                     //
//-------------------------- Clash Damage -----------------------------//
//                                                                     //
// ▪ Clash damage is based on force and cannot exceed 50.              //
//   - Active only while the suit is ON.                               //
// ▪ When Armor is active, Clash damage is negated:                    //
//   - 80% is divided in half and applied to Armor.                    //
//   - 20% is applied to Health.                                       //
// ▪ When Armor is depleted:                                           //
//   - Clashes deal full damage to Health.                             //
//   - Active Hazards begin directly damaging Health.                  //
//                                                                     //
//------------------------ Clash Detected -----------------------------//
//                                                                     //
// ▪ Depending on Clash damage value, the suit may say the following:  //
//   - "Minor Laceration/Fracture Detected"    - < 25: Minor Clash     //
//   - "Major Laceration/Fracture Detected"    - ≥ 25: Major Clash     //
// ▪ Minor/Major are chosen depending on the sub-sub sound that played.//
//                                                                     //
//-------------------- Morphine Auto-Injection ------------------------//
//                                                                     //
// ▪ Only if a Major (HEV VOICE LINE) plays:                           //
//   - 40% chance to follow-up with morphine.wav (HEV VOICE LINE).     //
//     → Configurable cooldown, to avoid overdosing.                   //
//                                                                     //
//------------------------- Health Alerts -----------------------------//
//                                                                     //
// ▪ Health Alerts only active when Health is 50 or below.             //
// ▪ When Health drops to a lower 10th decimal (e.g., from 43 → 36),   //
//   a Health Alert (health**.wav) will play, (HEV VOICE LINE).        //
// ▪ The suit may say 1 of 3 Health Alert statements, depending on     //
//   what Health dropped to:                                           //
//   - ≤ 10: "User Death Imminent"    - Range: health01 - health10     //
//   - ≤ 30: "Vital Signs Critical"   - Range: health11 - health30     //
//   - ≤ 50: "Seek Medical Attention" - Range: health31 - health50     //
// ▪ If Vital Signs Critical or User Death Imminent plays, there is a  //
//   configurable % chance (50% default) the suit will append          //
//   Seek Medical Attention after the initial alert.                   //
// ▪ When Health is 0, death.wav will play.                            //
//                                                                     //
//----------------- Quick Healing & Recharging ------------------------//
//                                                                     //
// ▪ Two quick recovery options are available, which replicate the     //
//   small Medkit and Battery pickups in-game.                         //
//   - Medkit   → Immediately recovers 15 Health.                      //
//   - Battery  → Immediately recovers 15 Armor.                       //
// ▪ Both have their own distinct (HEV UI SOUNDS):                     //
//   - Medkit   → medkit.wav                                           //
//   - Battery  → battery.wav                                          //
//     → Both must be in the root of the sound font.                   //
// ▪ Medkit sound feedback:                                            //
//   - Plays medkit.wav on trigger.                                    //
//   - endlock.wav plays if already at max Health.                     //
// ▪ Battery sound feedback:                                           //
//   - Plays battery.wav on trigger.                                   //
//   - endlb.wav plays if already at max Armor.                        //
//   - Plays Armor Readout function, but rounds the value to           //
//     the nearest multiple of 5.                                      //
//=====================================================================//

#ifndef PROPS_HEV_H
#define PROPS_HEV_H
#define PROP_TYPE Hev
#define LOCKUP_HEALING SaberBase::LOCKUP_NORMAL
#define LOCKUP_FILL_ARMOR SaberBase::LOCKUP_LIGHTNING_BLOCK

//=====================================================================//
//                     HEV SUIT TIMING DEFINES                         //
//                    ─────────────────────────                        //
//                                                                     //
//  Below are the HEV_ #defines which control the timings of how       //
//  often Hazards, Healing and Armor recharge work in the HEV suit.    //
//  All times are in (ms). Below values are the default.               //
//  To fine-tune the behaviour, adjust the values in hev_config.h      //
//                                                                     //
//  HEV_RANDOM_EVENT_INTERVAL_MS                                       //
//  ▪ How often (ms) to check for a Random Hazard.                     //
//    Higher = less frequent checks.                                   //
//                                                                     //
//  HEV_RANDOM_HAZARD_CHANCE                                           //
//  ▪ Chance (0–100) for a Random Hazard to occur each check.          //
//    Higher = more frequent Hazards.                                  //
//                                                                     //
//  HEV_HAZARD_DELAY_MS                                                //
//  ▪ Delay (ms) before Hazard damage starts after checking and        //
//    triggering Hazard. Allows time for HEV Voice Line to finish.     //
//                                                                     //
//  HEV_HAZARD_DECREASE_MIN_MS                                         //
//  ▪ Minimum time (ms) between each tick of Hazard damage.            //
//                                                                     //
//  HEV_HAZARD_DECREASE_MAX_MS                                         //
//  ▪ Maximum time (ms) between each tick of Hazard damage.            //
//                                                                     //
//  HEV_HAZARD_SURGE_MIN_MS                                            //
//  ▪ Minimum time (ms) for a quick surge of Hazard damage.            //
//                                                                     //
//  HEV_HAZARD_SURGE_MAX_MS                                            //
//  ▪ Maximum time (ms) for a quick surge of Hazard damage.            //
//                                                                     //
//  HEV_HAZARD_AFTER_REVIVE_MS                                         //
//  ▪ Time (ms) after reviving before Hazards can happen again.        //
//                                                                     //
//  HEV_HEALTH_INCREASE_MS                                             //
//  ▪ Time (ms) between each Health recharge tick (hold AUX).          //
//    Default from 0 - 100 Health is 10 seconds.                       //
//    Lower = faster healing.                                          //
//                                                                     //
//  HEV_ARMOR_INCREASE_MS                                              //
//  ▪ Time (ms) between each armor recharge tick (hold POWER).         //
//    Default from 0 - 100 Armor is 10 seconds.                        //
//    Lower = faster recharge.                                         //
//                                                                     //
//  HEV_COOLDOWN_SEEK_MEDIC_MS                                         //
//  HEV_COOLDOWN_HEALTH_CRITICAL_MS                                    //
//  HEV_COOLDOWN_DEATH_IMMINENT_MS                                     //
//  HEV_COOLDOWN_HAZARD_ALERT_MS                                       //
//  HEV_COOLDOWN_MINOR_LACERATION_MS                                   //
//  HEV_COOLDOWN_MINOR_FRACTURE_MS                                     //
//  HEV_COOLDOWN_MAJOR_LACERATION_MS                                   //
//  HEV_COOLDOWN_MAJOR_FRACTURE_MS                                     //
//  HEV_COOLDOWN_MORPHINE_MS                                           //
//  ▪ Cooldown (ms) for specified voice lines. Can be customized       //
//    per voice line to your liking. Prevents spam.                    //
//=====================================================================//

#ifndef HEV_RANDOM_EVENT_INTERVAL_MS
#define HEV_RANDOM_EVENT_INTERVAL_MS 60000
#endif
#ifndef HEV_RANDOM_HAZARD_CHANCE
#define HEV_RANDOM_HAZARD_CHANCE 15
#endif
#ifndef HEV_HAZARD_DELAY_MS
#define HEV_HAZARD_DELAY_MS 6000
#endif
#ifndef HEV_HAZARD_DECREASE_MIN_MS
#define HEV_HAZARD_DECREASE_MIN_MS 1000
#endif
#ifndef HEV_HAZARD_DECREASE_MAX_MS
#define HEV_HAZARD_DECREASE_MAX_MS 4000
#endif
#ifndef HEV_HAZARD_SURGE_MIN_MS
#define HEV_HAZARD_SURGE_MIN_MS 8000
#endif
#ifndef HEV_HAZARD_SURGE_MAX_MS
#define HEV_HAZARD_SURGE_MAX_MS 15000
#endif
#ifndef HEV_HAZARD_AFTER_REVIVE_MS
#define HEV_HAZARD_AFTER_REVIVE_MS 60000
#endif
#ifndef HEV_HEALTH_INCREASE_MS
#define HEV_HEALTH_INCREASE_MS 100
#endif
#ifndef HEV_ARMOR_INCREASE_MS
#define HEV_ARMOR_INCREASE_MS 100
#endif
#ifndef HEV_HEALTH_ANNOUNCEMENT_CHANCE
#define HEV_HEALTH_ANNOUNCEMENT_CHANCE 50
#endif
#ifndef HEV_COOLDOWN_SEEK_MEDIC_MS
#define HEV_COOLDOWN_SEEK_MEDIC_MS 20000
#endif
#ifndef HEV_COOLDOWN_HEALTH_CRITICAL_MS
#define HEV_COOLDOWN_HEALTH_CRITICAL_MS 20000
#endif
#ifndef HEV_COOLDOWN_DEATH_IMMINENT_MS
#define HEV_COOLDOWN_DEATH_IMMINENT_MS 10000
#endif
#ifndef HEV_COOLDOWN_HAZARD_ALERT_MS
#define HEV_COOLDOWN_HAZARD_ALERT_MS 10000
#endif
#ifndef HEV_COOLDOWN_MINOR_LACERATION_MS
#define HEV_COOLDOWN_MINOR_LACERATION_MS 10000
#endif
#ifndef HEV_COOLDOWN_MINOR_FRACTURE_MS
#define HEV_COOLDOWN_MINOR_FRACTURE_MS 10000
#endif
#ifndef HEV_COOLDOWN_MAJOR_LACERATION_MS
#define HEV_COOLDOWN_MAJOR_LACERATION_MS 10000
#endif
#ifndef HEV_COOLDOWN_MAJOR_FRACTURE_MS
#define HEV_COOLDOWN_MAJOR_FRACTURE_MS 10000
#endif
#ifndef HEV_COOLDOWN_MORPHINE_MS
#define HEV_COOLDOWN_MORPHINE_MS 300000
#endif

#include "prop_base.h"
#include <cmath>

// HEV VOICE LINES
EFFECT(armor);
EFFECT(health);
EFFECT(armor_compromised);
EFFECT(hazard);
EFFECT(minor_laceration);
EFFECT(minor_fracture);
EFFECT(major_laceration);
EFFECT(major_fracture);
EFFECT(morphine);

// HEV UI SOUNDS
EFFECT(armor_alarm);
EFFECT(battery);
EFFECT(death);
EFFECT(fuzz);
EFFECT(medkit);

// ENVIRONMENTAL SFX
EFFECT(stun);

// VOLUME MENU
EFFECT(vmbegin);
EFFECT(vmend);
EFFECT(volup);
EFFECT(voldown);
EFFECT(volmax);
EFFECT(volmin);

struct HEVTimerBase {
  uint32_t start_ = 0;
  uint32_t interval_ = 0;
  bool active_ = false;

  void reset() { active_ = false; }
  void start() { active_ = true; start_ = millis(); }
  void configure(uint32_t interval) { interval_ = interval; }
  void configure_random(uint32_t min_ms, uint32_t max_ms) {
    interval_ = min_ms + random(max_ms - min_ms + 1);
  }

  bool check() {
    return !active_ || (millis() - start_ > interval_);
  }
  bool running() const {
    return active_ && (millis() - start_) <= interval_;
  }
};

class Hev : public PROP_INHERIT_PREFIX PropBase {
public:

  //=====================================================================//
  //                       TIMER CONFIGURATION                           //
  //                    ─────────────────────────                        //
  //                                                                     //
  // ▪ timer_clash_               - Uses clash_timeout from PropBase.    //
  //                                Debounce to prevent false Clashes.   //
  // ▪ timer_random_event_        - Interval timer for Random Hazards.   //
  //                                Controls how often Hazards can occur.//
  // ▪ timer_hazard_delay_        - Delay between event trigger and      //
  //                                Hazard DPS. Also used as a gap for   //
  //                                voice to end before stun sfx start.  //
  // ▪ timer_hazard_surge_        - Duration timer for a quick surge of  //
  //                                hazardous damage (Heat/Shock).       //
  // ▪ timer_hazard_after_revive_ - Cooldown after user revives.         //
  //                                Blocks Hazards until timer is done.  //
  // ▪ timer_health_increase_     - Interval for Health recharge.        //
  //                                Controls healing rate.               //
  // ▪ timer_armor_increase_      - Interval for Armor recharge.         //
  //                                Controls Armor recharge rate.        //
  // ▪ timer_cooldown_seek_medic_                                        //
  // ▪ timer_cooldown_health_critical_                                   //
  // ▪ timer_cooldown_death_imminent_                                    //
  // ▪ timer_cooldown_hazard_alert_                                      //
  // ▪ timer_cooldown_minor_laceration_                                  //
  // ▪ timer_cooldown_minor_fracture_                                    //
  // ▪ timer_cooldown_major_laceration_                                  //
  // ▪ timer_cooldown_major_fracture_                                    //
  // ▪ timer_cooldown_morphine_   - Cooldown timers for certain quotes.  //
  //=====================================================================//

  HEVTimerBase timer_clash_;
  HEVTimerBase timer_random_event_;
  HEVTimerBase timer_hazard_delay_;
  HEVTimerBase timer_hazard_surge_;
  HEVTimerBase timer_hazard_after_revive_;
  HEVTimerBase timer_health_increase_;
  HEVTimerBase timer_armor_increase_;
  HEVTimerBase timer_cooldown_seek_medic_;
  HEVTimerBase timer_cooldown_health_critical_;
  HEVTimerBase timer_cooldown_death_imminent_;
  HEVTimerBase timer_cooldown_hazard_alert_;
  HEVTimerBase timer_cooldown_minor_laceration_;
  HEVTimerBase timer_cooldown_minor_fracture_;
  HEVTimerBase timer_cooldown_major_laceration_;
  HEVTimerBase timer_cooldown_major_fracture_;
  HEVTimerBase timer_cooldown_morphine_;


  Hev() : PropBase() {
    timer_clash_.configure(this->clash_timeout_);
    timer_random_event_.configure(HEV_RANDOM_EVENT_INTERVAL_MS);
    timer_hazard_delay_.configure(HEV_HAZARD_DELAY_MS);
    timer_hazard_surge_.configure(0);
    timer_hazard_after_revive_.configure(HEV_HAZARD_AFTER_REVIVE_MS);
    timer_health_increase_.configure(HEV_HEALTH_INCREASE_MS);
    timer_armor_increase_.configure(HEV_ARMOR_INCREASE_MS);
    timer_cooldown_seek_medic_.configure(HEV_COOLDOWN_SEEK_MEDIC_MS);
    timer_cooldown_health_critical_.configure(HEV_COOLDOWN_HEALTH_CRITICAL_MS);
    timer_cooldown_death_imminent_.configure(HEV_COOLDOWN_DEATH_IMMINENT_MS);
    timer_cooldown_hazard_alert_.configure(HEV_COOLDOWN_HAZARD_ALERT_MS);
    timer_cooldown_minor_laceration_.configure(HEV_COOLDOWN_MINOR_LACERATION_MS);
    timer_cooldown_minor_fracture_.configure(HEV_COOLDOWN_MINOR_FRACTURE_MS);
    timer_cooldown_major_laceration_.configure(HEV_COOLDOWN_MAJOR_LACERATION_MS);
    timer_cooldown_major_fracture_.configure(HEV_COOLDOWN_MAJOR_FRACTURE_MS);
    timer_cooldown_morphine_.configure(HEV_COOLDOWN_MORPHINE_MS);
  }

  const char* name() override { return "Hev"; }

  int health_ = 100;
  int armor_ = 100;

  enum DamageType {
    DAMAGE_PHYSICAL,
    DAMAGE_HAZARD,
  };

  enum Hazard {
    HAZARD_NONE = 0,
    HAZARD_BIO = 1,
    HAZARD_RAD = 2,
    HAZARD_BLO = 3,
    HAZARD_CHE = 4,
    HAZARD_HEA = 5,
    HAZARD_SHO = 6,
  };

  Hazard current_hazard_ = HAZARD_NONE;

  // Calculate Physical and Hazard Damage
  void DoDamage(int damage, bool quiet = false, DamageType type = DAMAGE_PHYSICAL) {
    int previous_health = health_;
    int previous_armor = armor_;
    int tens = health_ / 10;
    int log_hazard_damage = 0;

    // Damage type and calculation
    switch (type) {
      case DAMAGE_PHYSICAL:
        if (armor_ >= damage) {
          armor_ -= ceilf(damage * 0.80 / 2);
          health_ -= ceilf(damage * 0.20);
        } else if (armor_ > 0) {
          int excess_physical = damage - armor_;
          health_ -= excess_physical;
          armor_ = 0;
        } else {
          health_ -= damage;
        }
        break;

      case DAMAGE_HAZARD:
        int hazard_damage = damage;
        if (damage == 0) {
          switch (current_hazard_) {
            case HAZARD_BIO: hazard_damage = 2; break;
            case HAZARD_RAD: hazard_damage = 3; break;
            case HAZARD_BLO: hazard_damage = 2; break;
            case HAZARD_CHE: hazard_damage = 2; break;
            case HAZARD_HEA: hazard_damage = 4; break;
            case HAZARD_SHO: hazard_damage = 5; break;
            default: hazard_damage = 1; break;
          }
        }
        if (armor_ > 0) {
          armor_ -= hazard_damage;
        } else {
          health_ -= hazard_damage;
        }
        log_hazard_damage = hazard_damage;
        break;
    }

    // Enforce minimum values
    if (health_ < 0) health_ = 0;
    if (armor_ < 0) armor_ = 0;

    // (HEV VOICE LINE) Logic for Armor Compromised
    // if (previous_armor > 0 && armor_ == 0 && health_ == 0) {
    if (previous_armor > 0 && armor_ == 0) {
      SaberBase::DoEffect(EFFECT_USER2, 0.0);
      PVLOG_NORMAL << "Armor Compromised!\n";
    }

    // (ENVIRONMENTAL FX) Damage Sounds
    if (!quiet) SaberBase::DoEffect(EFFECT_STUN, 0.0);
    
    // (HEV UI SOUNDS) Logic for Death Sound
    if (health_ == 0 && previous_health > 0) {
      SaberBase::DoEffect(EFFECT_EMPTY, 0.0);
      return;
    }
    
    // (HEV VOICE LINE) Logic for Health Alert
    // Only plays when Health enters a new multiple of 10
    // and only if alive and health is less than 50. (avoid 50 silent wavs)
    // Configurable chance to announce and reduce spam.
    int new_tens = health_ / 10;
    if (tens != new_tens && health_ != 0 && health_ < 50) {
      if (random(100) < HEV_HEALTH_ANNOUNCEMENT_CHANCE) {
        // Map health ranges to announcements
        int health_range = (health_ >= 31) ? 3 : (health_ >= 11) ? 2 : 1;
        const char* health_message = (health_range == 3) ? "Seek Medical Attention" : 
                                     (health_range == 2) ? "Vital Signs Critical" : 
                                     "User Death Imminent";
        
        PVLOG_NORMAL << "Health Alert: health=" << health_ << " range=" << health_range 
                     << " (" << health_message << ")\n";
        SaberBase::DoEffect(EFFECT_USER1, 0.0, health_range);  // Pass health_range as sound_number
        
        // For health ranges 1 and 2, 50% chance to append "Seek Medical Attention"
        int roll = random(100);
        if (health_range < 3 && roll < 50) {
          // Add cooldown check for health03 (Seek Medical Attention)
          if (timer_cooldown_seek_medic_.check()) {
            PVLOG_NORMAL << "  + Appending health03 (Seek Medical Attention) [PLAYING, cooldown started]\n";
            SFX_health.Select(3);
            SOUNDQ->Play(SoundToPlay(&SFX_health));
            timer_cooldown_seek_medic_.start();
          } else {
            PVLOG_NORMAL << "  + Appending health03 (Seek Medical Attention) [BLOCKED by cooldown]\n";
          }
        } else if (health_range < 3) {
          PVLOG_NORMAL << "  + NO append health03 (failed 50% chance roll)\n";
        }
      }
    }

    // Print Damage, Health and Armor
    PVLOG_NORMAL << "DAMAGE: -" << damage << " / ";
    PVLOG_NORMAL << "HAZARD DAMAGE: -" << log_hazard_damage << "\n";
    PVLOG_NORMAL << "HEALTH: " << health_ << " / ";
    PVLOG_NORMAL << "ARMOR: " << armor_ << "\n";
  }

  // Armor Readout
  void armor_readout() {
    PVLOG_NORMAL << "Current Armor: " << armor_ << "\n";

    int armor_to_variation = round((armor_ * 32765.0) / 100.0);
    SaberBase::SetVariation(armor_to_variation);

    // Play random "fuzz" sound only if armor is above 0.
    if (armor_ > 0) {
      SOUNDQ->Play(&SFX_fuzz);

      // Play Armor Readout
      SFX_armor.SelectFloat(armor_ / 100.0);
      SOUNDQ->Play(&SFX_armor);

    } else {
      // If Armor is 0, immediately plays a warning sound.
      SFX_armor.SelectFloat(armor_ / 0.0);
      hybrid_font.PlayCommon(&SFX_armor);
    }
  }

  // Clashes
  void Clash(bool stab, float strength) override {
    // Don't process clashes if dead or during cooldown.
    if (!SaberBase::IsOn() || health_ == 0 || (timer_clash_.active_ && !timer_clash_.check())) {
      return;
    }

    PropBase::Clash(false, strength);

    int damage = std::min((int)(strength * 4), 50);
    float v = (strength - GetCurrentClashThreshold()) / 3;

    SFX_clash.SelectFloat(v);
    SFX_clsh.SelectFloat(v);
    SFX_stab.SelectFloat(v);

    if (damage >= 30) {
      hybrid_font.PlayPolyphonic(&SFX_armor_alarm);
    }

    DoDamage(damage, true);
    timer_clash_.start();
  }

  // Swings do nothing!
  void DoMotion(const Vec3& motion, bool clear) override {
    PropBase::DoMotion(Vec3(0), clear);
  }

  // Random Hazards
  void CheckRandomEvent() {
    // Skip Hazard check if OFF, dead, or during revive cooldown
    if (!SaberBase::IsOn() || health_ == 0 || !timer_hazard_after_revive_.check()) {
      return;
    }

    // Initialize timer. Stops immediate Hazard at boot
    if (!timer_random_event_.active_) {
      timer_random_event_.start();
      return;
    }

    // Check for new Hazard if timer expired and no current Hazard
    if (timer_random_event_.check() && current_hazard_ == HAZARD_NONE) {
            
      // Roll for Random Hazard
      if (random(100) < HEV_RANDOM_HAZARD_CHANCE) {
        PVLOG_NORMAL << "Activating Hazard.\n";
        current_hazard_ = (Hazard)(1 + random(6));
        SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
      } else {
        PVLOG_NORMAL << "Skipping Hazard.\n";
        timer_random_event_.start();
      }
    }
  }

  // Hazard Damage. Decrease armor (if any) or health over time.
  void HazardDecrease() {
    // Reset timer when hazard is cleared
    if (current_hazard_ == HAZARD_NONE) {
      timer_hazard_delay_.reset();
      timer_hazard_surge_.reset();
      return;
    }

    // Start sequence if not running
    if (!timer_hazard_delay_.active_) {
      timer_hazard_delay_.configure(HEV_HAZARD_DELAY_MS);
      timer_hazard_delay_.start();
      return;
    }

    // Check sequence then start surge timer or apply hazard damage
    if (!timer_hazard_delay_.running()) {
      // For Heat/Shock: start surge timer if not already started
      if ((current_hazard_ == HAZARD_HEA || current_hazard_ == HAZARD_SHO)) {
        if (!timer_hazard_surge_.active_) {
          timer_hazard_surge_.configure_random(
            HEV_HAZARD_SURGE_MIN_MS,
            HEV_HAZARD_SURGE_MAX_MS
          );
          timer_hazard_surge_.start();
        } else if (timer_hazard_surge_.check()) {
          PVLOG_NORMAL << "Heat/Shock Hazard expired.\n";
          current_hazard_ = HAZARD_NONE;
          timer_hazard_delay_.reset();
          timer_hazard_surge_.reset();
          SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
          timer_random_event_.start();
          return;
        }
      }
      // Apply hazard damage
      DoDamage(0, false, DAMAGE_HAZARD);

      // Clear hazard on death
      if (health_ == 0) {
        current_hazard_ = HAZARD_NONE;
        timer_hazard_delay_.reset();
        timer_hazard_surge_.reset();
        SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
        return;
      }

      // Interval for continuous damage is randomized between min and max
      timer_hazard_delay_.configure_random(
        HEV_HAZARD_DECREASE_MIN_MS,
        HEV_HAZARD_DECREASE_MAX_MS
      );
      timer_hazard_delay_.start();
    }
  }

  // Reset random event timer after revive.
  void Revive() {
    if (health_ == 0) {
      timer_random_event_.reset();
      timer_hazard_surge_.reset();
    }
  }

  // Increase health (Hold AUX).
  void IncreaseHealth() {
    if (SaberBase::Lockup() != LOCKUP_HEALING) return;

    if (health_ >= 100) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      return;
    }

    if (timer_health_increase_.running()) return;

    Revive();

    health_++;
    timer_health_increase_.start();
    PVLOG_NORMAL << "Health: " << health_ << "\n";
  }

  // Increase armor (Hold POWER).
  void IncreaseArmor() {
    if (SaberBase::Lockup() != LOCKUP_FILL_ARMOR) return;

    if (armor_ >= 100) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      return;
    }

    if (timer_armor_increase_.running()) return;

    armor_++;
    timer_armor_increase_.start();
    PVLOG_NORMAL << "Armor: " << armor_ << "\n";
  }

// Volume Menu
  void VolumeMenu() {
    // if (combat_mode_) return;
    mode_volume_ = !mode_volume_;
    if (mode_volume_) {
      if (SFX_vmbegin) {
        sound_library_.SayEnterVolumeMenu();
      } else {
        beeper.Beep(0.1, 1000);
        beeper.Beep(0.1, 2000);
        beeper.Beep(0.1, 3000);
      }
      PVLOG_NORMAL << "** Enter Volume Menu\n";
      SaberBase::DoEffect(EFFECT_VOLUME_LEVEL, 0);
    } else {
      if (SFX_vmend) {
        sound_library_.SayVolumeMenuEnd();
      } else {
        beeper.Beep(0.1, 2000);
        beeper.Beep(0.1, 1000);
      }
      PVLOG_NORMAL << "** Exit Volume Menu\n";
    }
  }

  const int maxVolume = VOLUME;
  const int minVolume = VOLUME * 0.10;
  int currentVolume = dynamic_mixer.get_volume();

  void VolumeUp() {
    SaberBase::DoEffect(EFFECT_VOLUME_LEVEL, 0);
    int increasedVolume = std::min<int>(maxVolume, currentVolume + maxVolume * 0.10);

    if (currentVolume < maxVolume) {
      currentVolume = increasedVolume;
      dynamic_mixer.set_volume(currentVolume);
      if (!hybrid_font.PlayPolyphonic(&SFX_volup)) {
        beeper.Beep(0.10, 2000);
        beeper.Beep(0.20, 2500);
      }
      PVLOG_NORMAL << "** Volume Up - Current Volume: " << currentVolume << "\n";
    } else {
      currentVolume = maxVolume;
      dynamic_mixer.set_volume(currentVolume);
      if (!hybrid_font.PlayPolyphonic(&SFX_volmax)) {
        beeper.Beep(0.5, 3000);
      }
      PVLOG_NORMAL << "** Maximum Volume\n";
    }
  }

  void VolumeDown() {
    SaberBase::DoEffect(EFFECT_VOLUME_LEVEL, 0);
    int decreasedVolume = std::max<int>(minVolume, currentVolume - maxVolume * 0.10);

    if (currentVolume > minVolume) {
      currentVolume = decreasedVolume;
      dynamic_mixer.set_volume(currentVolume);
      if (!hybrid_font.PlayPolyphonic(&SFX_voldown)) {
        beeper.Beep(0.10, 2000);
        beeper.Beep(0.20, 1500);
      }
      PVLOG_NORMAL << "** Volume Down - Current Volume: " << currentVolume << "\n";
    } else {
      currentVolume = minVolume;
      dynamic_mixer.set_volume(currentVolume);
      if (!hybrid_font.PlayPolyphonic(&SFX_volmin)) {
        beeper.Beep(0.5, 1000);
      }
      PVLOG_NORMAL << "** Minimum Volume\n";
    }
  }

  // Main Loop
  void Loop() override {
    CheckRandomEvent();
    HazardDecrease();
    IncreaseHealth();
    IncreaseArmor();
    PropBase::Loop();
  }

  // Button Events
  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, modifiers)) {
      // On/Off long-click
      case EVENTID(BUTTON_POWER, EVENT_FIRST_CLICK_LONG, MODE_OFF):
#ifdef LIGHTS_ON_RESETS_HEALTH_ARMOR
        health_ = 100;
        armor_ = 100;
#endif
        On();
        return true;
      case EVENTID(BUTTON_POWER, EVENT_FIRST_CLICK_LONG, MODE_ON):
        if (current_hazard_) {
          current_hazard_ = HAZARD_NONE;
          SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
          timer_random_event_.reset();
        }
        Off();
        return true;

      // short-click AUX to clear hazard / Volume Up
      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_OFF):
        if (current_hazard_) {
          current_hazard_ = HAZARD_NONE;
          SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
          timer_random_event_.reset();
          timer_random_event_.start();
          timer_hazard_delay_.reset();
          return true;
        } else if (mode_volume_) {
            VolumeUp();
        }
        // Play a no-hazard sound ?
        return true;

      // short-click POW to Volume Down
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_OFF):
        if (mode_volume_) VolumeDown();
        return true;

      // Double-click power to start/stop track.
      case EVENTID(BUTTON_POWER, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_OFF):
        StartOrStopTrack();
        return true;
    
      // Double-click AUX for Armor Readout.
      case EVENTID(BUTTON_AUX, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_OFF):
        SaberBase::DoEffect(EFFECT_USER8, 0.0);
        armor_readout();
        return true;

      // Next/Previous preset. Triple-click on either button.
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_OFF):
        next_preset();
        return true;
      case EVENTID(BUTTON_AUX, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ANY_BUTTON | MODE_OFF):
        previous_preset();
        return true;

      // Hold AUX to start healing
      case EVENTID(BUTTON_AUX, EVENT_HELD_MEDIUM, MODE_ON):
        if (!SaberBase::Lockup()) {
          SaberBase::SetLockup(SaberBase::LOCKUP_HEALING);
          SaberBase::DoBeginLockup();
          timer_health_increase_.start();
          return true;
        }
        break;

      // Release AUX to stop healing (or wait until full).
      case EVENTID(BUTTON_AUX, EVENT_RELEASED, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_RELEASED, MODE_ANY_BUTTON | MODE_OFF):
        if (SaberBase::Lockup()) {
          SaberBase::DoEndLockup();
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          timer_health_increase_.reset();
          return true;
        }
        break;

      // Hold POWER to start recharging armor
      case EVENTID(BUTTON_POWER, EVENT_HELD_MEDIUM, MODE_ON):
        if (!SaberBase::Lockup()) {
          SaberBase::SetLockup(SaberBase::LOCKUP_FILL_ARMOR);
          SaberBase::DoBeginLockup();
          timer_armor_increase_.start();
          return true;
        }
        break;

      // Release POWER to stop recharging armor (or wait until full).
      case EVENTID(BUTTON_POWER, EVENT_RELEASED, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_RELEASED, MODE_ANY_BUTTON | MODE_OFF):
        if (SaberBase::Lockup()) {
          SaberBase::DoEndLockup();
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          timer_armor_increase_.reset();
          return true;
        }
        break;

        // Enter/Exit Volume Menu
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_OFF):
        VolumeMenu();
        return true;



#ifdef BLADE_DETECT_PIN
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_ON, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_ON, MODE_ANY_BUTTON | MODE_OFF):
        // Might need to do something cleaner, but let's try this for now.
        blade_detected_ = true;
        FindBladeAgain();
        SaberBase::DoBladeDetect(true);
        return true;

      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_OFF, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_OFF, MODE_ANY_BUTTON | MODE_OFF):
        // Might need to do something cleaner, but let's try this for now.
        blade_detected_ = false;
        FindBladeAgain();
        SaberBase::DoBladeDetect(false);
        return true;
#endif
    }
    return false;
  }

   // Hev effects, auto fire is handled by begin/end lockup
  void SB_Effect(EffectType effect, EffectLocation location) override {
    // Don't queue new sounds if dead (except death sound).
    // Once dead, if a queued sound is currently playing, allow it to finish
    // alongside death sound. However all pending sounds should be cleared.
    switch (effect) {
      default: return;
      case EFFECT_BOOT:
        hybrid_font.PlayCommon(&SFX_boot);
        return;

      // (ENVIRONMENTAL FX) Hazard SFX
      case EFFECT_STUN:
        hybrid_font.PlayCommon(&SFX_stun);
        return;

      // (HEV VOICE LINE) Health Alert
      case EFFECT_USER1:
        if (health_ == 0) return; // Don't queue health sounds if dead
        if (SaberBase::sound_number >= 0) {
          // Files are 1-indexed (health01.wav, health02.wav,health03.wav) but selection is 0-indexed
          int idx = (int)SaberBase::sound_number - 1;
          bool can_play = true;
          // Check cooldowns for each health alert
          switch (idx) {
            case 0: // health01
              if (!timer_cooldown_death_imminent_.check()) can_play = false;
              else timer_cooldown_death_imminent_.start();
              break;
            case 1: // health02
              if (!timer_cooldown_health_critical_.check()) can_play = false;
              else timer_cooldown_health_critical_.start();
              break;
            case 2: // health03
              if (!timer_cooldown_seek_medic_.check()) can_play = false;
              else timer_cooldown_seek_medic_.start();
              break;
            default:
              break;
          }
          if (can_play) {
            PVLOG_NORMAL << "PLAYING Health Alert. Cooldown started.\n";
            SoundToPlay stp(&SFX_health, idx);
            stp.effect_to_trigger_ = EFFECT_USER1_STEP2;
            SOUNDQ->Play(stp);
          } else {
            PVLOG_NORMAL << "BLOCKED Health Alert by cooldown.\n";
          }
        }
        return;

      case EFFECT_USER1_STEP2: {
        // Get the sound length when the effect actually triggers for WavLen use.
        RefPtr<BufferedWavPlayer> tmp = GetWavPlayerPlaying(&SFX_health);
        if (tmp) {
          SaberBase::sound_length = tmp->length();
        }
        // PVLOG_NORMAL << "******** STEP2 effect triggered SaberBase::sound_length = " << SaberBase::sound_length << "\n";
        return;
      }

      // (HEV VOICE LINE) Armor Compromised
      case EFFECT_USER2:
        // PVLOG_NORMAL << "******** Queueing SFX_armor_compromised sound with STEP2 trigger\n";
        SOUNDQ->Play(SoundToPlay(&SFX_armor_compromised, EFFECT_USER2_STEP2));
        return;

      case EFFECT_USER2_STEP2: {
        RefPtr<BufferedWavPlayer> tmp = GetWavPlayerPlaying(&SFX_armor_compromised);
        if (tmp) {
          SaberBase::sound_length = tmp->length();
        }
        // PVLOG_NORMAL << "******** STEP2 effect triggered SaberBase::sound_length = " << SaberBase::sound_length << "\n";
        return;
      }

      // (HEV UI SOUNDS) Death Sound
      case EFFECT_EMPTY:
        if (health_ == 0) {
          SOUNDQ->clear_pending();
        }
        hybrid_font.PlayCommon(&SFX_death);
        return;
    }
  }

  void SB_Effect2(EffectType effect, EffectLocation location) override {
    switch (effect) {
      default: return;

      // (HEV VOICE LINE) Hazard Alert
      case EFFECT_ALT_SOUND:
        SOUNDQ->Play(SoundToPlay(&SFX_hazard));
        return;
    }
  }

private:
  bool mode_volume_ = false;

};

#endif
