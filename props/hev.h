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
// - POWER Button:                                                     //
//     - Long-click           - ON/OFF                                 //
//     - Hold                 - Recharge Armor                         //
//     - Double-click         - Toggle track                           //
//     - Triple-click         - Next preset                            //
//     - Quad-click (OFF)     - Enter Settings Menu                    //
// - AUX Button:                                                       //
//     - Hold                 - Recharge Health                        //
//     - Single-click         - Deactivate Hazard                      //
//     - Double-click         - Armor Readout                          //
//     - Triple-click         - Previous preset                        //
//     - Quad-click (OFF)     - Enter Settings Menu                    //
//                                                                     //
// - SIMULTANEOUS BUTTONS:                                             //
//     - Hold POWER + Click AUX (ON) - Toggle Combat Mode              //
//       (Disables all voice lines and effects in real-time)           //
//                                                                     //
//---------------------------------------------------------------------//
//                         SETTINGS MENU                               //
//---------------------------------------------------------------------//
//                                                                     //
// - Entering Menu:                                                    //
//     - Quad-click POWER or AUX while the suit is OFF                 //
// - Navigating Menu:                                                  //
//     - Hold POWER (medium) to navigate forward through options       //
//     - Hold AUX (medium) to navigate backward through options        //
//     - Options: Hazards, Health Alerts, Armor Alerts, Clash Damage   //
// - Toggling Settings:                                                //
//     - Single-click POWER to toggle selected setting ON/OFF          //
// - Exiting Menu:                                                     //
//     - Single-click AUX (or double-click POWER) to exit menu         //
//                                                                     //
// - Settings:                                                         //
//     1. Hazards             - Disables hazard voice alerts           //
//                              (hazards still occur, just silent)     //
//     2. Health Alerts       - Disables health voice announcements    //
//                              (health still changes, just silent)    //
//     3. Armor Alerts        - Disables armor voice/alarm sounds      //
//                              (armor still changes, just silent)     //
//     4. Clash Damage        - Disables physical clash damage         //
//                              (actually prevents damage application) //
//                                                                     //
// Note: Settings 1-3 only control audio/visual feedback. The         //
//       underlying systems (health, armor, hazards) continue to       //
//       function normally. Setting 4 actually disables damage.        //
//       All settings default to ENABLED and are SAVED to SD card      //
//       (hev.ini) - they persist across power cycles.                //
//                                                                     //
//---------------------------------------------------------------------//
//                          COMBAT MODE                                //
//---------------------------------------------------------------------//
//                                                                     //
// Combat Mode is a real-time toggle that disables all voice lines    //
// and sound effects while keeping the suit functional. This is ideal  //
// for combat scenarios where audio feedback would be distracting.     //
//                                                                     //
// - Toggle: Hold POWER + Click AUX (while suit is ON)                //
// - Effect: Disables all HEV voice lines and effects                  //
// - State Preservation:                                               //
//     * Entering Combat Mode saves current Health and Armor values    //
//     * Exiting Combat Mode restores the saved values                 //
//     * Allows you to "pause" damage tracking during combat           //
// - Persists: Until toggled off or suit is powered off                //
//                                                                     //
//---------------------------------------------------------------------//
//              PHYSICAL DAMAGE & HAZARD DAMAGE LOGIC                  //
//---------------------------------------------------------------------//
//                                                                     //
// - The HEV suit has two main resources: Health and Armor.            //
//     - Both have a maximum value of 100.                             //
//     - Both active only while the suit is ON.                        //
// - Random Hazards:                                                   //
//     - Active only while the suit is ON.                             //
//     - Always damages Armor first, then Health.                      //
//     - Triggered at intervals with a chance-based system.            //
// - When Armor is depleted:                                           //
//     - Hazards begin directly damaging Health.                       //
//     - Clashes deal full damage to Health.                           //
// - When Armor is active:                                             //
//     - Clashes (physical impacts) are negated:                       //
//         ▪ 80% is divided in half, then applied to Armor.            //
//         ▪ 20% is applied to Health.                                 //
// - Clash damage is based on force of impact:                         //
//     - Cannot exceed 50 total damage.                                //
//                                                                     //
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
//                                                                     //
//----------------------- Voice Line Cooldowns ------------------------//
//                                                                     //
// ▪ Some (HEV VOICE LINES) have configurable cooldowns to prevent     //
//   them from being spammed.                                          //
// ▪ Default cooldown times are defined here, but can be customized in //
//   hev_config.h per voice line to your liking.                       //
// ▪ It is worth noting that cooldowns are work together with          //
//   a definable *chance* to trigger said voice lines.                 //
//   This means that even if a voice line is off cooldown, it may not  //
//   always play. This creates variability in the suit's responses.    //
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
//  HEV_HAZARD_DECREASE_MS                                             //
//      - Time (ms) between each tick of Hazard damage.                //
//        Lower = faster damage-over-time.                             //
//                                                                     //
//  HEV_HAZARD_AFTER_REVIVE_MS                                         //
//      - Time (ms) after reviving before Hazards can happen again.    //
//                                                                     //
//  HEV_HEALTH_INCREASE_MS                                             //
//      - Time (ms) between each Health recharge tick (hold AUX).      //
//        Default from 0 - 100 Health is 10 seconds.                   //
//        Lower = faster healing.                                      //
//                                                                     //
//  HEV_ARMOR_INCREASE_MS                                              //
//      - Time (ms) between each armor recharge tick (hold POWER).     //
//        Default from 0 - 100 Armor is 10 seconds.                    //
//        Lower = faster recharge.                                     //
//=====================================================================//

#ifndef HEV_RANDOM_EVENT_INTERVAL_MS
#define HEV_RANDOM_EVENT_INTERVAL_MS 600000
#endif
#ifndef HEV_RANDOM_HAZARD_CHANCE
#define HEV_RANDOM_HAZARD_CHANCE 50
#endif
#ifndef HEV_MEDKIT_INTERVAL_MIN_MS
#define HEV_MEDKIT_INTERVAL_MIN_MS 600000
#endif
#ifndef HEV_MEDKIT_INTERVAL_MAX_MS
#define HEV_MEDKIT_INTERVAL_MAX_MS 1200000
#endif
#ifndef HEV_MEDKIT_CHANCE
#define HEV_MEDKIT_CHANCE 100
#endif
#ifndef HEV_BATTERY_INTERVAL_MIN_MS
#define HEV_BATTERY_INTERVAL_MIN_MS 600000
#endif
#ifndef HEV_BATTERY_INTERVAL_MAX_MS
#define HEV_BATTERY_INTERVAL_MAX_MS 1200000
#endif
#ifndef HEV_BATTERY_CHANCE
#define HEV_BATTERY_CHANCE 100
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
#ifndef HEV_CLASH_MINOR_LACERATION_CHANCE
#define HEV_CLASH_MINOR_LACERATION_CHANCE 50
#endif
#ifndef HEV_CLASH_MINOR_FRACTURE_CHANCE
#define HEV_CLASH_MINOR_FRACTURE_CHANCE 50
#endif
#ifndef HEV_CLASH_MAJOR_LACERATION_CHANCE
#define HEV_CLASH_MAJOR_LACERATION_CHANCE 50
#endif
#ifndef HEV_CLASH_MAJOR_FRACTURE_CHANCE
#define HEV_CLASH_MAJOR_FRACTURE_CHANCE 50
#endif
#ifndef HEV_HEALTH_SEEK_MEDIC_CHANCE
#define HEV_HEALTH_SEEK_MEDIC_CHANCE 55
#endif
#ifndef HEV_HEALTH_CRITICAL_CHANCE
#define HEV_HEALTH_CRITICAL_CHANCE 65
#endif
#ifndef HEV_HEALTH_DEATH_IMMINENT_CHANCE
#define HEV_HEALTH_DEATH_IMMINENT_CHANCE 90
#endif
#ifndef HEV_COOLDOWN_SEEK_MEDIC_MS
#define HEV_COOLDOWN_SEEK_MEDIC_MS 40000
#endif
#ifndef HEV_COOLDOWN_HEALTH_CRITICAL_MS
#define HEV_COOLDOWN_HEALTH_CRITICAL_MS 40000
#endif
#ifndef HEV_COOLDOWN_DEATH_IMMINENT_MS
#define HEV_COOLDOWN_DEATH_IMMINENT_MS 40000
#endif
#ifndef HEV_COOLDOWN_MINOR_LACERATION_MS
#define HEV_COOLDOWN_MINOR_LACERATION_MS 30000
#endif
#ifndef HEV_COOLDOWN_MINOR_FRACTURE_MS
#define HEV_COOLDOWN_MINOR_FRACTURE_MS 30000
#endif
#ifndef HEV_COOLDOWN_MAJOR_LACERATION_MS
#define HEV_COOLDOWN_MAJOR_LACERATION_MS 30000
#endif
#ifndef HEV_COOLDOWN_MAJOR_FRACTURE_MS
#define HEV_COOLDOWN_MAJOR_FRACTURE_MS 30000
#endif
#ifndef HEV_COOLDOWN_MORPHINE_MS
#define HEV_COOLDOWN_MORPHINE_MS 30000
#endif
#ifndef HEV_MORPHINE_CHANCE
#define HEV_MORPHINE_CHANCE 75
#endif
#ifndef HEV_HEALTH_RESERVES 75
#define HEV_HEALTH_RESERVES 75
#endif
#ifndef HEV_ARMOR_RESERVES 75
#define HEV_ARMOR_RESERVES 75
#endif
#ifndef HEV_HEALTH_RESERVES_DELAY_MS
#define HEV_HEALTH_RESERVES_DELAY_MS 30000
#endif
#ifndef HEV_ARMOR_RESERVES_DELAY_MS
#define HEV_ARMOR_RESERVES_DELAY_MS 30000
#endif
#ifndef HEV_HEALTH_RESERVES_REFILL_MS
#define HEV_HEALTH_RESERVES_REFILL_MS 1600  // 2 minutes to refill 75 H Reserves
#endif
#ifndef HEV_ARMOR_RESERVES_REFILL_MS
#define HEV_ARMOR_RESERVES_REFILL_MS 1600  // 2 minutes to refill 75 A Reserves
#endif

#include "prop_base.h"

// HEV MENU SOUNDS (for settings toggles)
EFFECT(atmospherics_on);
EFFECT(atmospherics_off);
EFFECT(automedic_on);
EFFECT(automedic_off);
EFFECT(powerarmor_on);
EFFECT(powerarmor_off);
EFFECT(vitalsigns_on);
EFFECT(vitalsigns_off);
EFFECT(safe_day);

// Current alternative directory for Hazard sounds
extern int current_alternative;

// Forward declaration for hev_menu.h
namespace hev_settings {
  extern bool in_settings_menu;
}

#include "../modes/hev_menu.h"
#include "../common/config_file.h"

// HEV Settings Config File for persistent storage
class HevSettingsFile : public ConfigFile {
public:
  void iterateVariables(VariableOP *op) override {
    CONFIG_VARIABLE2(hazards_enabled, 1);
    CONFIG_VARIABLE2(health_alerts_enabled, 1);
    CONFIG_VARIABLE2(armor_alerts_enabled, 1);
    CONFIG_VARIABLE2(clash_damage_enabled, 1);
  }
  int hazards_enabled;
  int health_alerts_enabled;
  int armor_alerts_enabled;
  int clash_damage_enabled;
};

// Global HEV settings (toggleable via menu)
namespace hev_settings {
  bool hazards_enabled = true;
  bool health_alerts_enabled = true;
  bool armor_alerts_enabled = true;
  bool clash_damage_enabled = true;
  bool combat_mode = false;  // Real-time toggle: disables voice lines and effects
  bool in_settings_menu = false;  // True when user is in settings menu

  HevSettingsFile saved_settings;
  
  void SaveSettings() {
    PVLOG_STATUS << "Saving HEV Settings\n";
    saved_settings.hazards_enabled = hazards_enabled ? 1 : 0;
    saved_settings.health_alerts_enabled = health_alerts_enabled ? 1 : 0;
    saved_settings.armor_alerts_enabled = armor_alerts_enabled ? 1 : 0;
    saved_settings.clash_damage_enabled = clash_damage_enabled ? 1 : 0;
    saved_settings.WriteToRootDir("hev");
  }
  
  void LoadSettings() {
    if (saved_settings.ReadINIFromRootDir("hev") == ConfigFile::ReadStatus::READ_END) {
      PVLOG_STATUS << "Loaded HEV Settings\n";
      hazards_enabled = saved_settings.hazards_enabled != 0;
      health_alerts_enabled = saved_settings.health_alerts_enabled != 0;
      armor_alerts_enabled = saved_settings.armor_alerts_enabled != 0;
      clash_damage_enabled = saved_settings.clash_damage_enabled != 0;
    } else {
      PVLOG_STATUS << "Using default HEV Settings\n";
    }
  }
}

// HEV VOICE LINES
EFFECT(armor);
EFFECT(armor_hundred);
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
EFFECT(armor_zero);
EFFECT(battery);
EFFECT(death);
EFFECT(fuzz);
EFFECT(medkit);
EFFECT(health_reserve_bgn);
EFFECT(health_reserve_end);
EFFECT(armor_reserve_bgn);
EFFECT(armor_reserve_end);
EFFECT(warning);

// ENVIRONMENTAL SFX
EFFECT(stun);

// VOLUME MENU
EFFECT(vmbegin);
EFFECT(vmend);
EFFECT(volup);
EFFECT(voldown);
EFFECT(volmax);
EFFECT(volmin);

EFFECT(voice_on);    // Enter "Combat" Mode
EFFECT(voice_off);   // Exit "Combat" Mode

struct HEVTimerBase {
  bool active_ = false;
  bool paused_ = false;
  uint32_t start_ = 0;
  uint32_t interval_ = 0;
  uint32_t paused_at_ = 0;

  void reset() { active_ = false; paused_ = false; }
  void start() { active_ = true; paused_ = false; start_ = millis(); }
  void configure(uint32_t interval) { interval_ = interval; }
  void configure_random(uint32_t min_ms, uint32_t max_ms) {
    interval_ = min_ms + random(max_ms - min_ms + 1);
  }
  void pause() {
    if (active_ && !paused_) {
      paused_ = true;
      paused_at_ = millis();
    }
  }
  void resume() {
    if (active_ && paused_) {
      start_ += millis() - paused_at_;
      paused_ = false;
    }
  }
  
  bool check() {
    if (paused_) return false;
    return !active_ || (millis() - start_ > interval_);
  }
  bool running() const {
    if (paused_) return false;
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
  HEVTimerBase timer_random_medkit_;
  HEVTimerBase timer_random_battery_;
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
  HEVTimerBase timer_health_reserves_delay_;
  HEVTimerBase timer_armor_reserves_delay_;
  HEVTimerBase timer_health_reserves_refill_;
  HEVTimerBase timer_armor_reserves_refill_;

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
    timer_cooldown_minor_laceration_.configure(HEV_COOLDOWN_MINOR_LACERATION_MS);
    timer_cooldown_minor_fracture_.configure(HEV_COOLDOWN_MINOR_FRACTURE_MS);
    timer_cooldown_major_laceration_.configure(HEV_COOLDOWN_MAJOR_LACERATION_MS);
    timer_cooldown_major_fracture_.configure(HEV_COOLDOWN_MAJOR_FRACTURE_MS);
    timer_cooldown_morphine_.configure(HEV_COOLDOWN_MORPHINE_MS);
    timer_health_reserves_delay_.configure(HEV_HEALTH_RESERVES_DELAY_MS);
    timer_armor_reserves_delay_.configure(HEV_ARMOR_RESERVES_DELAY_MS);
    timer_health_reserves_refill_.configure(HEV_HEALTH_RESERVES_REFILL_MS);
    timer_armor_reserves_refill_.configure(HEV_ARMOR_RESERVES_REFILL_MS);
    
    // Load saved HEV settings from SD card
    hev_settings::LoadSettings();
  }

  // Helper method to pause specific HEV timers during Vol & Settings Menu
  void PauseGameTimers() {
    timer_hazard_delay_.pause();
    timer_hazard_surge_.pause();
    timer_random_event_.pause();
    timer_random_medkit_.pause();
    timer_random_battery_.pause();
    timer_hazard_after_revive_.pause();
    timer_health_reserves_delay_.pause();
    timer_armor_reserves_delay_.pause();
    timer_health_reserves_refill_.pause();
    timer_armor_reserves_refill_.pause();
  }

  void ResumeGameTimers() {
    timer_hazard_delay_.resume();
    timer_hazard_surge_.resume();
    timer_random_event_.resume();
    timer_random_medkit_.resume();
    timer_random_battery_.resume();
    timer_hazard_after_revive_.resume();
    timer_health_reserves_delay_.resume();
    timer_armor_reserves_delay_.resume();
    timer_health_reserves_refill_.resume();
    timer_armor_reserves_refill_.resume();
  }

#ifndef MENU_SPEC_TEMPLATE
  void Setup() override {
    MKSPEC<mode::HevMenuSpec>::SoundLibrary::init();
  }
#endif

  const char* name() override { return "Hev"; }

  int health_ = 100;
  int armor_ = 100;
  int health_reserves_ = HEV_HEALTH_RESERVES;
  int armor_reserves_ = HEV_ARMOR_RESERVES;
  int health_reserves_refilled_ = 0;  // Tracks total refilled in current cycle
  int armor_reserves_refilled_ = 0;   // Tracks total refilled in current cycle
  int injury_ = 0; // 0 = Lacerations, 1 = Fractures
  int impact_ = 0; // 0 = Minor, 1 = Major
  bool queue_morphine_ = false; // Flag to queue morphine after other voice lines

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

  // Start with the the suit ON (not in Standby Mode) by default.
  // Replicate PropBase::SetPreset logic to inject volume muting
  // at the right time (after chdir resets volumes, before FastOn plays sound)
  void SetPreset(int preset_num, bool announce) override {
    PVLOG_DEBUG << "SetPreset(" << preset_num << ")\n";
    TRACE(PROP, "start");
    BladeSet previously_on = PropBase::BladeOff();
    PropBase::SaveColorChangeIfNeeded();
    
    // First free all styles, then allocate new ones to avoid memory fragmentation
    PropBase::FreeBladeStyles();
    PropBase::current_preset_.SetPreset(preset_num);
    PropBase::AllocateBladeStyles();
    PropBase::chdir(PropBase::current_preset_.font.get());
    
    // Mute SFX_out and SFX_blst before FastOn
    saved_out_volume_ = SFX_out.GetVolume();
    SFX_out.SetVolume(0);
    saved_blst_volume_ = SFX_blst.GetVolume();
    SFX_blst.SetVolume(0);
    
    if (previously_on.on()) PropBase::FastOn(EffectLocation(0, previously_on));
    if (announce) {
      PVLOG_STATUS << "Current Preset: " << PropBase::current_preset_name() << "\n";
      SaberBase::DoNewFont();
    }
    TRACE(PROP, "end");

    if (!SaberBase::IsOn()) {
      On();
    }
    
    // Mark that we need to restore volume later (will be set in Loop once sound starts)
    restore_volume_time_ = 1;
  }

  // Structure to hold damage results
  struct DamageResult {
    bool armor_compromised = false;
    bool health_alert_triggered = false;
    int health_range = 0;
    bool death_occurred = false;
  };

  // Calculate Physical and Hazard Damage
  DamageResult DoDamage(int damage, bool quiet = false, DamageType type = DAMAGE_PHYSICAL) {
    DamageResult result;
    int previous_health = health_;
    int previous_armor = armor_;
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
    if (previous_armor > 0 && armor_ == 0 && hev_settings::armor_alerts_enabled && !hev_settings::combat_mode) {
      result.armor_compromised = true;
      PVLOG_NORMAL << "Armor Compromised!\n";
    }

    // (ENVIRONMENTAL FX) Damage Sounds
    // Should always play in and outside of Combat Mode
    if (!quiet && current_hazard_ != HAZARD_NONE) {
      SaberBase::DoEffect(EFFECT_STUN, 0.0);
    }
    
    // (HEV UI SOUNDS) Logic for Death Sound
    if (health_ == 0 && previous_health > 0) {
      result.death_occurred = true;
      SaberBase::DoEffect(EFFECT_EMPTY, 0.0);
      return result;
    }
    
    // (HEV VOICE LINE) Logic for Health Alert
    // Plays a certain alert when Health is below 50. (avoid 50 silent wavs)
    if (health_ != 0 && health_ < 50 && hev_settings::health_alerts_enabled && !hev_settings::combat_mode) {
      // Map health ranges to announcements
      result.health_range = (health_ >= 31) ? 3 : (health_ >= 11) ? 2 : 1;
      result.health_alert_triggered = true;
      const char* health_message = (result.health_range == 3) ? "Seek Medical Attention" : 
                                    (result.health_range == 2) ? "Vital Signs Critical" : 
                                    "User Death Imminent";
      
      PVLOG_NORMAL << "Health Alert: health=" << health_ << " range=" << result.health_range 
                    << " (" << health_message << ")\n";
    }

    // Print Damage, Health and Armor
    PVLOG_NORMAL << "DAMAGE: -" << damage << " / ";
    PVLOG_NORMAL << "HAZARD DAMAGE: -" << log_hazard_damage << "\n";
    PVLOG_NORMAL << "HEALTH: " << health_ << " / ";
    PVLOG_NORMAL << "ARMOR: " << armor_ << "\n";
    
    return result;
  }

  // Armor Readout
  void armor_readout() {
    PVLOG_NORMAL << "Current Armor: " << armor_ << "\n";

    int armor_to_variation = round((armor_ * 32765.0) / 100.0);
    SaberBase::SetVariation(armor_to_variation);

    if (armor_ > 0) {
      SOUNDQ->Play(&SFX_fuzz);
      if (armor_ >= 100) {
        SOUNDQ->Play(&SFX_armor_hundred);
      } else {
        SOUNDQ->Play(&SFX_armor);
        // Round armor to nearest 5 for voice line
        int armor_rounded = (armor_ + 2) / 5 * 5;
        sound_library_.SayNumber(armor_rounded, SAY_WHOLE);
        sound_library_.SayPercent();
      }
    } else {
      // If Armor is 0, immediately plays a warning sound.
      hybrid_font.PlayCommon(&SFX_armor_zero);
    }
  }

  // Clashes
  void Clash(bool stab, float strength) override {
    // Don't process clashes if in Standby Mode, in Volume Menu, dead, in settings menu, or during clash cooldown.
    if (!SaberBase::IsOn() ||
        mode_volume_ ||
        health_ == 0 ||
        hev_settings::in_settings_menu ||
        (timer_clash_.active_ && !timer_clash_.check())) {
      return;
    }

    PropBase::Clash(false, strength);

    int damage = std::min((int)(strength * 4), 50);
    float v = (strength - GetCurrentClashThreshold()) / 3;

    SFX_clash.SelectFloat(v);
    SFX_clsh.SelectFloat(v);
    SFX_stab.SelectFloat(v);

    // Only play alarm if armor alerts are enabled and not in combat mode
    if (damage >= 30 && hev_settings::armor_alerts_enabled && !hev_settings::combat_mode) {
      hybrid_font.PlayPolyphonic(&SFX_armor_alarm);
    }

    // Capture the Injury type and Impact (sub-sub sound IDs).
    // Get what clsh sub-sub wav the player is currently playing
    // then queue up either a Laceration or Fracture voice line.
    RefPtr<BufferedWavPlayer> subsub = GetWavPlayerPlaying(&SFX_clsh);
    int injury_type = 0; // 0 = Laceration, 1 = Fracture
    if (subsub) {
      injury_type = subsub->current_file_id().GetSubId();
    }
    int severity = (damage >= 25) ? 1 : 0; // 0 = Minor, 1 = Major

    injury_ = injury_type;
    impact_ = severity;

    // Apply damage.
    DamageResult result = DoDamage(damage, true);
      
    // Queue effects in the correct order (only if not in combat mode and not dead)
    // Reset morphine flag before queueing effects
    queue_morphine_ = false;
    if (!hev_settings::combat_mode && health_ != 0) {
      // 1. Injury Detected
      SaberBase::DoEffect(EFFECT_USER3, 0.0);

      // NOTE: Clashes should NEVER trigger hazard alerts
      // Hazard alerts are only played when a new hazard starts in CheckRandomEvent()
      // The EFFECT_ALT_SOUND plays a random hazard sound, which made it seem like
      // a new hazard was caused by clashes during a hazard.
      // // 2. Hazard Alert (only if hazard is active)
      // if (current_hazard_ != HAZARD_NONE) {
      //   SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0);
      // }
      
      // 2. Armor Compromised (only if armor just dropped to zero)
      if (result.armor_compromised) {
        SaberBase::DoEffect(EFFECT_USER2, 0.0);
      }
      
      // 3. Health Alert (only if health dropped below 50)
      if (result.health_alert_triggered) {
        QueueHealthAlert(result.health_range);
      }
      
      // 4. Morphine (queued last, ONLY IF major injury was played AND clash_damage_enabled)
      if (queue_morphine_ && hev_settings::clash_damage_enabled) {
        SOUNDQ->Play(SoundToPlay(&SFX_morphine));
        timer_cooldown_morphine_.start();
      }
    }
    timer_clash_.start();
  }

  // Swings do nothing!
  void DoMotion(const Vec3& motion, bool clear) override {
    PropBase::DoMotion(Vec3(0), clear);
  }

  // Random Hazards, Medkits and Batteries
  void CheckRandomEvent() {
    // Skip check if in Standby Mode, in Volume Menu, dead, in settings menu, or during revive cooldown.
    // Note: hazards_enabled only affects audio/visual, not the actual hazard system
    if (!SaberBase::IsOn() ||
        mode_volume_ ||
        health_ == 0 ||
        !timer_hazard_after_revive_.check()) {
      return;
    }

    // Initialize timer. Stops immediate check at boot
    if (!timer_random_event_.active_) {
      timer_random_event_.start();
      return;
    }

    // --- Hazard ---
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

    // --- Medkit ---
    if (!timer_random_medkit_.active_) {
      timer_random_medkit_.configure_random(
      HEV_MEDKIT_INTERVAL_MIN_MS,
      HEV_MEDKIT_INTERVAL_MAX_MS
      );
      timer_random_medkit_.start();
    }
    if (random(100) < HEV_MEDKIT_CHANCE) {
      if (timer_random_medkit_.check()) {
        PVLOG_NORMAL << "Random Medkit event triggered.\n";
        ItemMedkit();
        timer_random_medkit_.configure_random(
          HEV_MEDKIT_INTERVAL_MIN_MS,
          HEV_MEDKIT_INTERVAL_MAX_MS
        );
        timer_random_medkit_.start();
      }
    }

    // --- Battery ---
    if (!timer_random_battery_.active_) {
      timer_random_battery_.configure_random(
      HEV_BATTERY_INTERVAL_MIN_MS,
      HEV_BATTERY_INTERVAL_MAX_MS
      );
      timer_random_battery_.start();
    }
    if (random(100) < HEV_BATTERY_CHANCE) {
      if (timer_random_battery_.check()) {
        PVLOG_NORMAL << "Random Battery event triggered.\n";
        ItemBattery();
        timer_random_battery_.configure_random(
          HEV_BATTERY_INTERVAL_MIN_MS,
          HEV_BATTERY_INTERVAL_MAX_MS
        );
        timer_random_battery_.start();
      }
    }
  }

  // Hazard Damage. Decrease armor (if any) or health over time.
  void HazardDecrease() {
    // Reset timer when Hazard is cleared or failed to roll a Hazard.
    if (current_hazard_ == HAZARD_NONE) {
      timer_hazard_delay_.reset();
      timer_hazard_surge_.reset();
      return;
    }

    // Start delay if not running
    if (!timer_hazard_delay_.active_) {
      timer_hazard_delay_.configure(HEV_HAZARD_DELAY_MS);
      timer_hazard_delay_.start();
      return;
    }

    // Check delay if is finished, then proceed.
    if (!timer_hazard_delay_.running()) {
      // For Heat/Shock: if surge inactive, configure random dps then start surge.
      if ((current_hazard_ == HAZARD_HEA || current_hazard_ == HAZARD_SHO)) {
        if (!timer_hazard_surge_.active_) {
          timer_hazard_surge_.configure_random(
            HEV_HAZARD_SURGE_MIN_MS,
            HEV_HAZARD_SURGE_MAX_MS
          );
          timer_hazard_surge_.start();
        // If surge active, check if it's finished then clear Hazard, reset timers and start random event timer.
        } else if (timer_hazard_surge_.check()) {
          PVLOG_NORMAL << "Heat/Shock Hazard expired.\n";
          current_hazard_ = HAZARD_NONE;
          SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
          timer_hazard_delay_.reset();
          timer_hazard_surge_.reset();
          timer_random_event_.start();
          return;
        }
      }

      // For Biochemical, Radiation, Blood Toxins, Chemical, apply Hazard damage.
      DamageResult result = DoDamage(0, false, DAMAGE_HAZARD);

      // For Hazard damage, we should trigger Armor Compromised and Health Alerts if needed, unless dead or
      // in Combat Mode.
      if (!hev_settings::combat_mode && health_ != 0) {
        // Armor Compromised (only if Armor just dropped to zero).
        if (result.armor_compromised) {
          SaberBase::DoEffect(EFFECT_USER2, 0.0);
        }
        
        // Health Alert (only if Health dropped below 50)
        if (result.health_alert_triggered) {
          QueueHealthAlert(result.health_range);
        }
      }

      // When dead, clear Hazard and reset timers.
      if (health_ == 0) {
        current_hazard_ = HAZARD_NONE;
        SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
        timer_hazard_delay_.reset();
        timer_hazard_surge_.reset();
        return;
      }

      // Randomised damage infliction.
      timer_hazard_delay_.configure_random(
        HEV_HAZARD_DECREASE_MIN_MS,
        HEV_HAZARD_DECREASE_MAX_MS
      );

      // Use this to follow up with continuous damage during Hazards.
      // Will remain until cleared, dead, or if Heat/Shock end themselves.
      timer_hazard_delay_.start();
    }
  }

  // Reset random event timer after revive.
  void Revive() {
    if (health_ == 0) {
      timer_random_event_.reset();
      timer_hazard_surge_.reset();
      SaberBase::DoEffect(EFFECT_USER4, 0.0);  // Toggle dead animation OFF
      PVLOG_NORMAL << "** Stopping Death Animation\n";
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

    // Stop healing permanently if refill cycle complete (Refilled 75 total)
    // OR if Reserves are depleted with delay active or not refilling.
    if (health_reserves_refilled_ >= HEV_HEALTH_RESERVES ||
        (health_reserves_ <= 0 && 
        (timer_health_reserves_delay_.active_ || !timer_health_reserves_refill_.active_))) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      timer_health_increase_.reset();
      if (health_reserves_refilled_ >= HEV_HEALTH_RESERVES) {
        PVLOG_NORMAL << "Health Reserves refill cycle complete. Cannot heal until new cycle.\n";
      } else {
        PVLOG_NORMAL << "Health Reserves empty. Healing stopped.\n";
      }
      return;
    }

    // Temporarily pause healing if reserves hit 0 during refill (consumption outpaced refill)
    // This handles the situation where healing (100ms) is faster than refilling (1600ms)
    if (health_reserves_ <= 0) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      timer_health_increase_.reset();
      PVLOG_NORMAL << "Health Reserves at 0. Healing paused.\n";
      return;
    }

    health_++;
    health_reserves_--;
    PVLOG_NORMAL << "Health: " << health_ << " (Reserves: " << health_reserves_ 
                                          << "/" << HEV_HEALTH_RESERVES << ")\n";
    timer_health_increase_.start();
  }

  // Refill Health Reserves over time.
  void HealthReservesRefill() {
    // Start delay timer when reserves drop to 15% or below (only if not already started)
    if (health_reserves_ <= (HEV_HEALTH_RESERVES * 0.15) && 
        !timer_health_reserves_delay_.active_ && 
        !timer_health_reserves_refill_.active_) {
      hybrid_font.PlayCommon(&SFX_warning);
      timer_health_reserves_delay_.start();
      PVLOG_NORMAL << "Health Reserves at 15% or below. Starting delay timer.\n";
      return;
    }

    // Wait for delay to finish.
    if (timer_health_reserves_delay_.active_ && !timer_health_reserves_delay_.check()) {
      return;
    }

    // Delay finished, start refilling Reserves.
    if (timer_health_reserves_delay_.active_) {
      timer_health_reserves_delay_.reset();
      hybrid_font.PlayCommon(&SFX_health_reserve_bgn);
      timer_health_reserves_refill_.start();
      PVLOG_NORMAL << "Health Reserves delay complete. Starting refill cycle.\n";
    }

    // Check before refilling Health Reserves over time.
    if (timer_health_reserves_refill_.active_ && timer_health_reserves_refill_.check()) {
      // Check if we've refilled to max for this cycle (75 total)
      // Max cap is whatever HEV_HEALTH_RESERVES is set to (default 75).
      // Filling from 15% or less to max counts as 1 cycle.
      // Cannot consume/refill more than set max in 1 cycle.
      if (health_reserves_refilled_ >= HEV_HEALTH_RESERVES) {
        // Refill cycle complete - reset counter
        health_reserves_refilled_ = 0;
        hybrid_font.PlayCommon(&SFX_health_reserve_end);
        timer_health_reserves_refill_.reset();
        PVLOG_NORMAL << "Health Reserves refill cycle complete (refilled " << HEV_HEALTH_RESERVES 
                     << " total). Reserves at " << health_reserves_ << "/" << HEV_HEALTH_RESERVES << "\n";
        return;
      }
      
      // Refilling Health Reserves and increment counter to track total refilled this cycle.
      health_reserves_++;
      health_reserves_refilled_++;
      PVLOG_NORMAL << "Refilling H Reserves: " << health_reserves_ << "/" << HEV_HEALTH_RESERVES 
                   << " (Total this cycle: " << health_reserves_refilled_ << "/" << HEV_HEALTH_RESERVES << ")\n";
      timer_health_reserves_refill_.start();
    }
  }

  // Increase armor (Hold POWER). Works the same as Health.
  void IncreaseArmor() {
    if (SaberBase::Lockup() != LOCKUP_FILL_ARMOR) return;

    if (armor_ >= 100) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      return;
    }

    if (timer_armor_increase_.running()) return;

    if (armor_reserves_refilled_ >= HEV_ARMOR_RESERVES ||
        (armor_reserves_ <= 0 && (timer_armor_reserves_delay_.active_ || !timer_armor_reserves_refill_.active_))) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      timer_armor_increase_.reset();
      if (armor_reserves_refilled_ >= HEV_ARMOR_RESERVES) {
        PVLOG_NORMAL << "Armor Reserves refill cycle complete. Cannot recharge until new cycle.\n";
      } else {
        PVLOG_NORMAL << "Armor Reserves empty. Recharging stopped.\n";
      }
      return;
    }

    if (armor_reserves_ <= 0) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      timer_armor_increase_.reset();
      PVLOG_NORMAL << "Armor Reserves at 0. Recharging paused.\n";
      return;
    }

    armor_++;
    armor_reserves_--;
    PVLOG_NORMAL << "Armor: " << armor_ << " (Reserves: " << armor_reserves_ 
                                        << "/" << HEV_ARMOR_RESERVES << ")\n";
    timer_armor_increase_.start();
  }

  // Refill Armor Reserves over time. Works the same as Health Reserves.
  void ArmorReservesRefill() {
    if (armor_reserves_ <= (HEV_ARMOR_RESERVES * 0.15) && 
        !timer_armor_reserves_delay_.active_ && 
        !timer_armor_reserves_refill_.active_) {
      hybrid_font.PlayCommon(&SFX_warning);
      timer_armor_reserves_delay_.start();
      PVLOG_NORMAL << "Armor Reserves at 15% or below. Starting delay timer.\n";
      return;
    }

    if (timer_armor_reserves_delay_.active_ && !timer_armor_reserves_delay_.check()) {
      return;
    }

    if (timer_armor_reserves_delay_.active_) {
      timer_armor_reserves_delay_.reset();
      hybrid_font.PlayCommon(&SFX_armor_reserve_bgn);
      timer_armor_reserves_refill_.start();
      PVLOG_NORMAL << "Armor Reserves delay complete. Starting refill cycle.\n";
    }

    if (timer_armor_reserves_refill_.active_ && timer_armor_reserves_refill_.check()) {
      if (armor_reserves_refilled_ >= HEV_ARMOR_RESERVES) {
        armor_reserves_refilled_ = 0;
        hybrid_font.PlayCommon(&SFX_armor_reserve_end);
        timer_armor_reserves_refill_.reset();
        PVLOG_NORMAL << "Armor Reserves refill cycle complete (refilled " << HEV_ARMOR_RESERVES 
                     << " total). Reserves at " << armor_reserves_ << "/" << HEV_ARMOR_RESERVES << "\n";
        return;
      }

      armor_reserves_++;
      armor_reserves_refilled_++;
      PVLOG_NORMAL << "Refilling A Reserves: " << armor_reserves_ << "/" << HEV_ARMOR_RESERVES 
                   << " (Total this cycle: " << armor_reserves_refilled_ << "/" << HEV_ARMOR_RESERVES << ")\n";
      timer_armor_reserves_refill_.start();
    }
  }

  // Instantly heal 15 Health (Medkit)
  void ItemMedkit() {
    if (health_ < 100) {
      int heal = std::min(15, 100 - health_);
      health_ += heal;
      PVLOG_NORMAL << "Medkit used: +" << heal << " Health (" << health_ << ")\n";
      hybrid_font.PlayCommon(&SFX_medkit);
    } else {
      // Already at max Health
      hybrid_font.PlayCommon(&SFX_endlock);
    }
  }

  // Instantly recharge 15 Armor (Battery)
  void ItemBattery() {
    if (armor_ < 100) {
      int recharge = std::min(15, 100 - armor_);
      armor_ += recharge;
      PVLOG_NORMAL << "Battery used: +" << recharge << " Armor (" << armor_ << ")\n";
      hybrid_font.PlayCommon(&SFX_battery);
      // Call armor readout to let user know new armor value
      armor_readout();
    } else {
      // Already at max Armor
      hybrid_font.PlayCommon(&SFX_endlb);
    }
  }

  // Volume Menu
  void VolumeMenu() {
    // if (combat_mode_) return;
    mode_volume_ = !mode_volume_;
    if (mode_volume_) {
      // Pause game timers
      PauseGameTimers();
      PVLOG_NORMAL << "Volume Menu entered - timers paused\n";
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
      // Resume game timers
      ResumeGameTimers();
      PVLOG_NORMAL << "Volume Menu exited - timers resumed\n";
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

  void DoSpokenBatteryLevel(bool volts) {
    // Avoid weird battery readings when using USB
    if (battery_monitor.battery() < 0.5) {
      sound_library_.SayBatteryLevel();
      sound_library_.SayDisabled();
      return;
    }
    if (volts) {
      sound_library_.SayBatteryVolts();
      PVLOG_NORMAL << "Battery Voltage: " << battery_monitor.battery() << "\n";
      SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
    } else {
      sound_library_.SayBatteryPercent();
      PVLOG_NORMAL << "Battery Percentage: " << battery_monitor.battery_percent() << "%\n";
      SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
    }
  }

  // Main Loop
  void Loop() override {
    PauseResumeTimersSettingsMenu();

    // Process HEV functions
    CheckRandomEvent();
    HazardDecrease();
    IncreaseHealth();
    IncreaseArmor();
    HealthReservesRefill();
    ArmorReservesRefill();

    // Restore volumes after boot
    SilenceAtBoot();

    PropBase::Loop();
  }

  // Button Events
  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, modifiers)) {

// AUX BUTTON EVENTS
// Clear hazard (1x click AUX)
// Volume Up
      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
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

// Start healing (Hold AUX)
      case EVENTID(BUTTON_AUX, EVENT_FIRST_HELD_MEDIUM, MODE_ON):
        if (mode_volume_) return false;
        if (!SaberBase::Lockup()) {
          // Check if health is already full.
          if (health_ == 100) {
            SaberBase::DoEndLockup();
            SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
            PVLOG_NORMAL << "Health Full. Cannot Heal.\n";
            return true;
          }
          // Only start healing if we have reserves and health not full.
          SaberBase::SetLockup(SaberBase::LOCKUP_HEALING);
          SaberBase::DoBeginLockup();
          return true;
        }
        break;

// Stop healing (Release AUX or wait until full)
      case EVENTID(BUTTON_AUX, EVENT_RELEASED, MODE_ON):
        if (SaberBase::Lockup()) {
          SaberBase::DoEndLockup();
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          timer_health_increase_.reset();
          return true;
        }
        break;

// Armor Readout (2x click AUX)
      case EVENTID(BUTTON_AUX, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
        if (mode_volume_) return false;
        SaberBase::DoEffect(EFFECT_USER8, 0.0);
        armor_readout();
        return true;

// Spoken Battery Level in percentage (3x click AUX)
      case EVENTID(BUTTON_AUX, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_OFF):
        DoSpokenBatteryLevel(false);
        return true;

// Spoken Battery Level in volts (3x click & hold AUX)
      case EVENTID(BUTTON_AUX, EVENT_THIRD_HELD_MEDIUM, MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_THIRD_HELD_MEDIUM, MODE_OFF):
        DoSpokenBatteryLevel(true);
        return true;

// Next/Previous preset. (4x click AUX = Next, 4x click & hold AUX = Previous)
      case EVENTID(BUTTON_AUX, EVENT_FOURTH_SAVED_CLICK_SHORT, MODE_ON):
        if (mode_volume_) return false;
        next_preset();
        return true;
      case EVENTID(BUTTON_AUX, EVENT_FOURTH_HELD_MEDIUM, MODE_ON):
        if (mode_volume_) return false;
        previous_preset();
        return true;

// POWER BUTTON EVENTS
// Flashlight ON/OFF (1x click POW)
// Volume Down
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_OFF):
        if (!mode_volume_) {
          SaberBase::DoBlast();
        } else {
          VolumeDown();
        }
        return true;

// Start recharging armor (Hold POW)
      case EVENTID(BUTTON_POWER, EVENT_FIRST_HELD_MEDIUM, MODE_ON):
        if (mode_volume_) return false;
        if (!SaberBase::Lockup()) {
          // Check if armor is already full.
          if (armor_ == 100) {
            SaberBase::DoEndLockup();
            SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
            PVLOG_NORMAL << "Armor Full. Cannot Recharge.\n";
            return true;
          }
          // Only start recharging if we have reserves and armor not full.
          SaberBase::SetLockup(SaberBase::LOCKUP_FILL_ARMOR);
          SaberBase::DoBeginLockup();
          return true;
        }
        break;

// Stop recharging armor (Release POW or wait until full)
      case EVENTID(BUTTON_POWER, EVENT_RELEASED, MODE_ON):
        if (SaberBase::Lockup()) {
          SaberBase::DoEndLockup();
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          timer_armor_increase_.reset();
          return true;
        }
        break;

// Enter HEV Settings Menu (2x click POW)
      case EVENTID(BUTTON_POWER, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_OFF):
        if (mode_volume_) return false;
        if (current_mode == this) {
          pushMode<MKSPEC<mode::HevMenuSpec>::HevSettingsMenu>();
          return true;
        }
        break;

// Activate Standby Mode (2x click & hold POW)
      case EVENTID(BUTTON_POWER, EVENT_SECOND_HELD_MEDIUM, MODE_ON):
        if (mode_volume_) return false;
        if (current_hazard_) {
          current_hazard_ = HAZARD_NONE;
          SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, current_hazard_);
          timer_random_event_.reset();
        }
        // Stop voice reports
        SOUNDQ->clear_pending();
        // Stop dead animation if showing.
        if (health_ == 0) SaberBase::DoEffect(EFFECT_USER4, 0.0);
        Off();
        return true;

// Deactivate Standby Mode (2x click & hold POW)
      case EVENTID(BUTTON_POWER, EVENT_SECOND_HELD_MEDIUM, MODE_OFF):
#ifndef STANDBY_NO_RESET_HEALTH_ARMOR
        health_ = 100;
        armor_ = 100;
        health_reserves_refilled_ = 0;
        armor_reserves_refilled_ = 0;
#endif
        timer_random_event_.reset();
        timer_hazard_surge_.reset();
        SaberBase::DoEffect(EFFECT_USER7, 0.0);  // Power On Pulse
        On();
        return true;

// Enter/Exit Volume Menu (3x click POW)
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_OFF):
        VolumeMenu();
        return true;

// Start/stop track (3x click & hold POW)
      case EVENTID(BUTTON_POWER, EVENT_THIRD_HELD_MEDIUM, MODE_ON):
        if (mode_volume_) return false;
        StartOrStopTrack();
        return true;

// Combat Mode ON/OFF (4x click POW)
      case EVENTID(BUTTON_POWER, EVENT_FOURTH_SAVED_CLICK_SHORT, MODE_ON):
        if (mode_volume_) return false;
        hev_settings::combat_mode = !hev_settings::combat_mode;
        if (hev_settings::combat_mode) {
          hybrid_font.PlayPolyphonic(&SFX_voice_off);
          PVLOG_NORMAL << "Combat Mode: DISABLED (voice/effects disabled)\n";
        } else {
          hybrid_font.PlayPolyphonic(&SFX_voice_on);
          PVLOG_NORMAL << "Combat Mode: ENABLED (voice/effects enabled)\n";
        }
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

      // (ENVIRONMENTAL FX) Hazard SFX
      case EFFECT_STUN:
        hybrid_font.PlayCommon(&SFX_stun);
        return;

      // (HEV VOICE LINE) Injury Detected (Laceration/Fracture)
      case EFFECT_USER3: {
        int injury_type = injury_; // 0 = Laceration, 1 = Fracture
        int impact = impact_;      // 0 = Minor, 1 = Major

        if (injury_type == 0) { // Laceration
          if (impact == 1) { // Major
            if (random(100) < HEV_CLASH_MAJOR_LACERATION_CHANCE && timer_cooldown_major_laceration_.check()) {
              SOUNDQ->Play(SoundToPlay(&SFX_major_laceration));
              timer_cooldown_major_laceration_.start();
              // Set flag to queue morphine later (after other voice lines)
              if (random(100) < HEV_MORPHINE_CHANCE && timer_cooldown_morphine_.check()) {
                queue_morphine_ = true;
              }
            }
          } else { // Minor
            if (random(100) < HEV_CLASH_MINOR_LACERATION_CHANCE && timer_cooldown_minor_laceration_.check()) {
              SOUNDQ->Play(SoundToPlay(&SFX_minor_laceration));
              timer_cooldown_minor_laceration_.start();
            }
          }
        } else { // Fracture
          if (impact == 1) { // Major
            if (random(100) < HEV_CLASH_MAJOR_FRACTURE_CHANCE && timer_cooldown_major_fracture_.check()) {
              SOUNDQ->Play(SoundToPlay(&SFX_major_fracture));
              timer_cooldown_major_fracture_.start();
              // Set flag to queue morphine later (after other voice lines)
              if (random(100) < HEV_MORPHINE_CHANCE && timer_cooldown_morphine_.check()) {
                queue_morphine_ = true;
              }
            }
          } else { // Minor
            if (random(100) < HEV_CLASH_MINOR_FRACTURE_CHANCE && timer_cooldown_minor_fracture_.check()) {
              SOUNDQ->Play(SoundToPlay(&SFX_minor_fracture));
              timer_cooldown_minor_fracture_.start();
            }
          }
        }
        return;
      }

      // (HEV VOICE LINE) Armor Compromised
      case EFFECT_USER2:
        SOUNDQ->Play(SoundToPlay(&SFX_armor_compromised, EFFECT_USER2_STEP2));
        return;

      case EFFECT_USER2_STEP2: {
        RefPtr<BufferedWavPlayer> tmp = GetWavPlayerPlaying(&SFX_armor_compromised);
        if (tmp) {
          SaberBase::sound_length = tmp->length();
        }
        return;
      }

      // (HEV VOICE LINE) Health Alert
      case EFFECT_USER1:
        if (health_ == 0) return; // Don't queue health sounds if dead
        if (SaberBase::sound_number >= 0) {
          // Files are 1-indexed (health01.wav, health02.wav,health03.wav) but selection is 0-indexed
          int idx = (int)SaberBase::sound_number - 1;
          bool can_play = true;
          // Roll then check cooldowns for each health alert
          switch (idx) {
            case 0: // health01
              if (random(100) >= HEV_HEALTH_DEATH_IMMINENT_CHANCE) can_play = false;
              else if (!timer_cooldown_death_imminent_.check()) can_play = false;
              else timer_cooldown_death_imminent_.start();
              break;
            case 1: // health02
              if (random(100) >= HEV_HEALTH_CRITICAL_CHANCE) can_play = false;
              else if (!timer_cooldown_health_critical_.check()) can_play = false;
              else timer_cooldown_health_critical_.start();
              break;
            case 2: // health03
              if (random(100) >= HEV_HEALTH_SEEK_MEDIC_CHANCE) can_play = false;
              else if (!timer_cooldown_seek_medic_.check()) can_play = false;
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
        return;
      }

      // (HEV UI SOUNDS) Death Sound
      case EFFECT_EMPTY:
        if (health_ == 0) {
          SOUNDQ->clear_pending();
        }
        hybrid_font.PlayCommon(&SFX_death);
        SaberBase::DoEffect(EFFECT_USER4, 0.0);  // Toggle dead animation ON
        PVLOG_NORMAL << "** Starting Death Animation\n";
        return;
    }
  }

  void SB_Effect2(EffectType effect, EffectLocation location) override {
    switch (effect) {
      default: return;

      // (HEV VOICE LINE) Hazard Alert
      case EFFECT_ALT_SOUND:
        // Switch alt via hybrid_font; play hazard voice only when enabled and not in combat.
        // Announce both on activation (altNNN) and on clear (alt000).
        if (hev_settings::hazards_enabled && !hev_settings::combat_mode) {
          int count = SFX_hazard.files_found();
          if (count > 0) {
            SFX_hazard.Select(random(count));
          }
          SOUNDQ->Play(SoundToPlay(&SFX_hazard));
          // Clear selection so future plays randomize again
          SFX_hazard.Select(-1);
        }
        return;
    }
  }

private:
  bool mode_volume_ = false;
  int saved_out_volume_ = -1;  // suppressed out.wav during boot
  int saved_blst_volume_ = -1;  // suppressed blst.wav during boot
  uint32_t restore_volume_time_ = 0;

  // Helper to pause/resume game timers when entering/exiting Settings Menu.
  void PauseResumeTimersSettingsMenu() {
    static bool prev_in_settings_menu = false;
    
    if (hev_settings::in_settings_menu && !prev_in_settings_menu) {
      // Just entered Settings Menu
      PauseGameTimers();
      PVLOG_NORMAL << "Settings Menu entered - timers paused\n";
    } else if (!hev_settings::in_settings_menu && prev_in_settings_menu) {
      // Just exited Settings Menu
      ResumeGameTimers();
      PVLOG_NORMAL << "Settings Menu exited - timers resumed\n";
    }
    prev_in_settings_menu = hev_settings::in_settings_menu;
  }

  // Helper to mute SFX_out and SFX_blst volumes during boot, then restore after.
  void SilenceAtBoot() {
    if (saved_out_volume_ >= 0 || saved_blst_volume_ >= 0) {
      if (restore_volume_time_ == 1) {
        RefPtr<BufferedWavPlayer> player = GetWavPlayerPlaying(&SFX_out);
        if (!player) player = GetWavPlayerPlaying(&SFX_blst);
        if (player) {
          float length = player->length();
          if (length > 0) {
            restore_volume_time_ = millis() + (uint32_t)(length * 1000);
          } else {
            // Unknown length, use default delay
            restore_volume_time_ = millis() + 10000;
          }
        }
      } else if (restore_volume_time_ > 1 && millis() >= restore_volume_time_) {
        // Time to restore both volumes
        if (saved_out_volume_ >= 0) {
          SFX_out.SetVolume(saved_out_volume_);
          saved_out_volume_ = -1;
        }
        if (saved_blst_volume_ >= 0) {
          SFX_blst.SetVolume(saved_blst_volume_);
          saved_blst_volume_ = -1;
        }
        restore_volume_time_ = 0;
      }
    }
  }

  // Helper to queue health alert with optional "Seek Medical Attention" append
  void QueueHealthAlert(int health_range) {
    SaberBase::DoEffect(EFFECT_USER1, 0.0, health_range);
    
    // For health ranges 1 and 2, chance to append "Seek Medical Attention"
    if (health_range < 3 && random(100) < HEV_HEALTH_SEEK_MEDIC_CHANCE) {
      // Check cooldown before playing health03 (Seek Medical Attention)
      if (timer_cooldown_seek_medic_.check()) {
        PVLOG_NORMAL << "  + Cooldown PASSED. Appending health03 (Seek Medical Attention)\n";
        SFX_health.Select(3);
        SOUNDQ->Play(SoundToPlay(&SFX_health));
        timer_cooldown_seek_medic_.start();
      } else {
        PVLOG_NORMAL << "  + Cooldown BLOCKED. Appending health03 (Seek Medical Attention)\n";
      }
    } else if (health_range < 3) {
      PVLOG_NORMAL << "  + NO append health03 (failed 50% chance roll)\n";
    }
  }
};

// HEV menu BoolSetting methods
namespace mode {

template<class SPEC>
bool HazardEnabledSetting<SPEC>::get() {
  return hev_settings::hazards_enabled;
}

template<class SPEC>
void HazardEnabledSetting<SPEC>::set(bool value) {
  hev_settings::hazards_enabled = value;
  hev_settings::SaveSettings();
}

template<class SPEC>
bool HealthAlertsEnabledSetting<SPEC>::get() {
  return hev_settings::health_alerts_enabled;
}

template<class SPEC>
void HealthAlertsEnabledSetting<SPEC>::set(bool value) {
  hev_settings::health_alerts_enabled = value;
  hev_settings::SaveSettings();
}

template<class SPEC>
bool ArmorAlertsEnabledSetting<SPEC>::get() {
  return hev_settings::armor_alerts_enabled;
}

template<class SPEC>
void ArmorAlertsEnabledSetting<SPEC>::set(bool value) {
  hev_settings::armor_alerts_enabled = value;
  hev_settings::SaveSettings();
}

template<class SPEC>
bool ClashDamageEnabledSetting<SPEC>::get() {
  return hev_settings::clash_damage_enabled;
}

template<class SPEC>
void ClashDamageEnabledSetting<SPEC>::set(bool value) {
  hev_settings::clash_damage_enabled = value;
  hev_settings::SaveSettings();
}

}  // namespace mode

#endif
