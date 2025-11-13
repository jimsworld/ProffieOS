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
#define MOUNT_SD_SETTING

#endif

#ifdef CONFIG_PROP
#include "../props/hev.h"
#endif

#ifdef CONFIG_PRESETS
Preset presets[] = {
  { "hev;common_hev", "common_hev/tracks/hl1_ost/10 Valve Theme [Extended].wav",
    StyleNormalPtr<Orange, Blue, 800, 300>(),
  }
};

BladeConfig blades[] = {
// 6 Lights, 3 pixels each, WS281X, RGB.
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

