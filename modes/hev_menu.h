#ifndef MODES_HEV_MENU_H
#define MODES_HEV_MENU_H

//=====================================================================//
//                      HEV SETTINGS MENU SYSTEM                       //
//                     ─────────────────────────                       //
//                                                                     //
// This file implements the settings menu for the HEV prop file,       //
// allowing users to toggle various HEV suit features on/off via       //
// button-based navigation (no rotation required).                     //
//                                                                     //
// Settings are stored in the global hev_settings namespace and are    //
// accessible from both the prop file and the menu system.             //
//                                                                     //
// How to use:                                                         //
// - Quad-click POWER or AUX while suit is OFF to enter menu          //
// - Hold POWER (medium) to navigate forward through settings          //
// - Hold AUX (medium) to navigate backward through settings           //
// - Single-click POWER to toggle selected setting                     //
// - Single-click AUX to exit menu                                     //
//                                                                     //
//=====================================================================//

#include "menu_base.h"
#include "bool_setting.h"
#include "menu_list.h"
#include "hev_tracks.h"

namespace mode {

// Forward declarations
class HevProp;

inline void StopCurrentMenuSounds();

// Button-based menu navigation mode (no rotation required)
// Uses HELD_MEDIUM events for forward/back navigation
template<class SPEC>
struct ButtonSteppedMode : public SPEC::SelectCancelMode {
  virtual void next() = 0;
  virtual void prev() = 0;
  virtual void update() {}

  bool mode_Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, 0)) {
      case EVENTID(BUTTON_POWER, EVENT_HELD_MEDIUM, 0):
        next();
        update();
        return true;

      case EVENTID(BUTTON_AUX, EVENT_HELD_MEDIUM, 0):
        prev();
        update();
        return true;
    }
    return SPEC::SelectCancelMode::mode_Event2(button, event, modifiers);
  }

  bool mode_Parse(const char *cmd, const char* arg) override {
#ifndef DISABLE_DIAGNOSTIC_COMMANDS
    if (!strcmp(cmd, "next") || !strcmp(cmd, "n")) {
      next();
      update();
      return true;
    }
    if (!strcmp(cmd, "prev") || !strcmp(cmd, "p")) {
      prev();
      update();
      return true;
    }
#endif
    return SPEC::SelectCancelMode::mode_Parse(cmd, arg);
  }
};

// Helper function to stop currently playing menu sounds
// This prevents audio overlap when toggling settings or navigating
// Note: Requires wav_players global array from sound.h to be available
inline void StopCurrentMenuSounds() {
  static constexpr float MENU_SOUND_FADE_TIME = 0.05f;  // 50ms
  for (size_t unit = 0; unit < NELEM(wav_players); unit++) {
    if (wav_players[unit].isPlaying() && wav_players[unit].refs() == 0) {
      wav_players[unit].set_fade_time(MENU_SOUND_FADE_TIME);
      wav_players[unit].FadeAndStop();
    }
  }
}

// Button-based menu base class
template<class SPEC>
struct ButtonMenuBase : public ButtonSteppedMode<SPEC> {
  virtual void say() = 0;
  virtual uint16_t size() = 0;

  void exit() override {
    getSL<SPEC>()->SayCancel();
    popMode();
  }
  
  void select() override {
    getSL<SPEC>()->SaySelect();
    popMode();
  }
  
  void mode_activate(bool onreturn) override {
    say();
  }
  
  void fadeout(float len) {
    getSL<SPEC>()->fadeout(len);
  }
  
  void next() override {
    StopCurrentMenuSounds();
    pos_ = MOD(pos_ + 1, size());
    say();
  }
  void prev() override {
    StopCurrentMenuSounds();
    pos_ = MOD(pos_ - 1, size());
    say();
  }

  uint16_t pos_;
};

// BoolSetting for enabling/disabling hazards
template<class SPEC>
struct HazardEnabledSetting : public BoolSetting {
  bool get();
  void set(bool value);
  void say() { 
    // This is called to announce the menu item name
    getSL<SPEC>()->SaySelect(); 
  }
};

// Custom menu entry for Hazard toggle with custom on/off sounds
template<class SPEC>
class HevHazardEntry : public MenuEntry {
public:
  void say(int entry) {
    // Play atmospherics_on or atmospherics_off based on current state
    getPtr<HazardEnabledSetting<SPEC>>()->say();
    if (getPtr<HazardEnabledSetting<SPEC>>()->get()) {
      hybrid_font.PlayCommon(&SFX_atmospherics_on);
    } else {
      hybrid_font.PlayCommon(&SFX_atmospherics_off);
    }
  }
  void select(int entry) {
    StopCurrentMenuSounds();
    getPtr<HazardEnabledSetting<SPEC>>()->set(!getPtr<HazardEnabledSetting<SPEC>>()->get());
    say(entry);
  }
};

// BoolSetting for enabling/disabling health alerts
template<class SPEC>
struct HealthAlertsEnabledSetting : public BoolSetting {
  bool get();
  void set(bool value);
  void say() { 
    getSL<SPEC>()->SaySelect();
  }
};

// Custom menu entry for Health Alerts toggle with custom on/off sounds
template<class SPEC>
class HevHealthAlertsEntry : public MenuEntry {
public:
  void say(int entry) {
    // Play vitalsigns_on or vitalsigns_off based on current state
    getPtr<HealthAlertsEnabledSetting<SPEC>>()->say();
    if (getPtr<HealthAlertsEnabledSetting<SPEC>>()->get()) {
      hybrid_font.PlayCommon(&SFX_vitalsigns_on);
    } else {
      hybrid_font.PlayCommon(&SFX_vitalsigns_off);
    }
  }
  void select(int entry) {
    StopCurrentMenuSounds();
    getPtr<HealthAlertsEnabledSetting<SPEC>>()->set(!getPtr<HealthAlertsEnabledSetting<SPEC>>()->get());
    say(entry);
  }
};

// BoolSetting for enabling/disabling armor alerts
template<class SPEC>
struct ArmorAlertsEnabledSetting : public BoolSetting {
  bool get();
  void set(bool value);
  void say() { 
    getSL<SPEC>()->SaySelect();
  }
};

// Custom menu entry for Armor Alerts toggle with custom on/off sounds
template<class SPEC>
class HevArmorAlertsEntry : public MenuEntry {
public:
  void say(int entry) {
    // Play powerarmor_on or powerarmor_off based on current state
    getPtr<ArmorAlertsEnabledSetting<SPEC>>()->say();
    if (getPtr<ArmorAlertsEnabledSetting<SPEC>>()->get()) {
      hybrid_font.PlayCommon(&SFX_powerarmor_on);
    } else {
      hybrid_font.PlayCommon(&SFX_powerarmor_off);
    }
  }
  void select(int entry) {
    StopCurrentMenuSounds();
    getPtr<ArmorAlertsEnabledSetting<SPEC>>()->set(!getPtr<ArmorAlertsEnabledSetting<SPEC>>()->get());
    say(entry);
  }
};

// BoolSetting for enabling/disabling clash damage
template<class SPEC>
struct ClashDamageEnabledSetting : public BoolSetting {
  bool get();
  void set(bool value);
  void say() { 
    getSL<SPEC>()->SaySelect();
  }
};

// Custom menu entry for Clash Damage toggle with custom on/off sounds
// Note: Using automedic sounds as user indicated morphine/antidotes
template<class SPEC>
class HevClashDamageEntry : public MenuEntry {
public:
  void say(int entry) {
    // Play automedic_on or automedic_off based on current state
    getPtr<ClashDamageEnabledSetting<SPEC>>()->say();
    if (getPtr<ClashDamageEnabledSetting<SPEC>>()->get()) {
      hybrid_font.PlayCommon(&SFX_automedic_on);
    } else {
      hybrid_font.PlayCommon(&SFX_automedic_off);
    }
  }
  void select(int entry) {
    StopCurrentMenuSounds();
    getPtr<ClashDamageEnabledSetting<SPEC>>()->set(!getPtr<ClashDamageEnabledSetting<SPEC>>()->get());
    say(entry);
  }
};

// Main HEV Settings Menu - combines all setting entries
template<class SPEC>
struct HevSettingsMenu : public MenuEntryMenu<SPEC,
  HevHazardEntry<SPEC>,
  HevHealthAlertsEntry<SPEC>,
  HevArmorAlertsEntry<SPEC>,
  HevClashDamageEntry<SPEC>
> {
  typedef MenuEntryMenu<SPEC,
    HevHazardEntry<SPEC>,
    HevHealthAlertsEntry<SPEC>,
    HevArmorAlertsEntry<SPEC>,
    HevClashDamageEntry<SPEC>> BaseMenu;
  
  void mode_activate(bool onreturn) override {
    hev_settings::in_settings_menu = true;
    BaseMenu::mode_activate(onreturn);
  }
  
  void mode_deactivate() override {
    hev_settings::in_settings_menu = false;
    BaseMenu::mode_deactivate();
  }
  void exit() override {
    StopCurrentMenuSounds();
    STDOUT.println("Exiting HEV Settings menu. Have a safe day!");
    if (random(100) < 50) hybrid_font.PlayCommon(&SFX_safe_day);
    getSL<SPEC>()->SayExit();
    popMode();
  }
};

// HEV Menu Specification (button-based, no rotation)
template<class SPEC>
struct HevMenuSpec {
  typedef mode::SelectCancelMode SelectCancelMode;
  typedef mode::ButtonSteppedMode<SPEC> SteppedModeBase;
  typedef mode::ButtonSteppedMode<SPEC> SteppedMode;
  typedef mode::ButtonMenuBase<SPEC> MenuBase;
  typedef SoundLibraryV2 SoundLibrary;
  typedef mode::HevSettingsMenu<SPEC> HevSettingsMenu;
  typedef mode::HevTrackMenu<SPEC> HevTrackMenu;
};

}  // namespace mode

#endif // MODES_HEV_MENU_H
