// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/* Swedish keys */

#define _______ KC_TRNS
#define SE_HALF KC_GRV
#define SE_PLUS KC_MINS
#define SE_ACUT KC_EQL
#define SE_AO   KC_LBRC
#define SE_CIRC KC_RBRC
#define SE_QUOT KC_BSLS
#define SE_OE   KC_SCLN
#define SE_AE   KC_QUOT
#define SE_MINS KC_SLSH
#define SE_LTGT KC_NUBS
#define SE_LCBR RALT(KC_7)
#define SE_LBRC RALT(KC_8)
#define SE_RBRC RALT(KC_9)
#define SE_RCBR RALT(KC_0)
#define SE_PIPE RALT(SE_LTGT)
#define SE_BSLS RALT(SE_PLUS)
#define SE_LPRN LSFT(KC_8)
#define SE_RPRN LSFT(KC_9)

#define AKC_1   RALT(KC_1)
#define AKC_2   RALT(KC_2)
#define AKC_3   RALT(KC_3)
#define AKC_4   RALT(KC_4)
#define AKC_5   RALT(KC_5)
#define AKC_6   RALT(KC_6)
#define AKC_7   RALT(KC_7)
#define AKC_8   RALT(KC_8)
#define AKC_9   RALT(KC_9)
#define AKC_0   RALT(KC_0)
#define A_TILDE RALT(SE_CIRC)

#define IDE_RUN  RSFT(KC_F10)
#define IDE_BLD  LCTL(KC_F9)
#define IDE_RBLD LSA(KC_M)

#define BASE   0 // default layer
#define SYMB   1 // symbols
#define MEDIA  2 // media keys
#define QWERTY 3 // qwerty layout

enum emoji_codes {
    M_SHRUG = SAFE_RANGE,
    M_TFLIP,
    M_WHY,
};

#define IDLE_TIMEOUT 30000 // 30 seconds
static uint32_t idle_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |      |           |QWERTY|   6  |   7  |   8  |   9  |   0  |   +    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Å  |   Ä  |   Ö  |   P  |   Y  | Re-  |           | Run  |   F  |   G  |   C  |   R  |   L  |   ,    |
 * |--------+------+------+------+------+------| Build|           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   O  |   E  |   U  |   I  |------|           |------|   H  |   D  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+------+------|      |           | Build|------+------+------+------+------+--------|
 * | LShift |   .  |   Q  |   J  |   K  |   B  |      |           |      |   X  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *  | Media |      |      | LAlt | LGui |                                       | Symb | Left | Down |  Up  | Right |
 *  `-----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Insrt| Del  |       | MPrv | MNxt |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |  Ctrl  |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(
        KC_ESC   , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______ ,
        KC_TAB   , SE_AO  , SE_AE  , SE_OE  , KC_P   , KC_Y   , IDE_RBLD,
        KC_LCTRL , KC_A   , KC_O   , KC_E   , KC_U   , KC_I   ,
        KC_LSFT  , KC_DOT , KC_Q   , KC_J   , KC_K   , KC_B   , _______ ,
        MO(MEDIA), _______, _______, KC_LGUI, KC_LALT,
                                                       KC_INS , KC_DEL  ,
                                                                KC_HOME ,
                                              KC_SPC , KC_BSPC, KC_END  ,

        TG(QWERTY), KC_6   , KC_7    , KC_8   , KC_9   , KC_0  , SE_PLUS        ,
        IDE_RUN   , KC_F   , KC_G    , KC_C   , KC_R   , KC_L  , KC_COMM        ,
                    KC_H   , KC_D    , KC_T   , KC_N   , KC_S  , RALT_T(SE_MINS),
        IDE_BLD   , KC_X   , KC_M    , KC_W   , KC_V   , KC_Z  , KC_RSFT        ,
                             MO(SYMB), KC_LEFT, KC_DOWN, KC_UP , KC_RIGHT       ,
        KC_MPRV   , KC_MNXT,
        KC_PGUP   ,
        KC_PGDN   , CTL_T(KC_TAB), KC_ENT
    ),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | ALT1 | ALT2 | ALT3 | ALT4 | ALT5 |      |           |      | ALT6 | ALT7 | ALT8 | ALT9 | ALT10|        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   {  |   |  |  }   |      |      |      |           |      |      |      |      |      |      | Tilde  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   [  |   \  |   ]  |   '  |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  <>  |  ¨^  |      |      |  `´  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |FlipTb|       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Shrug|       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |   Why|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
       _______, AKC_1  , AKC_2  , AKC_3  , AKC_4  , AKC_5  , _______,
       _______, SE_LCBR, SE_PIPE, SE_RCBR, _______, _______, _______,
       _______, SE_LBRC, SE_BSLS, SE_RBRC, SE_QUOT, _______,
       _______, SE_LTGT, SE_CIRC, _______, _______, SE_ACUT, _______,
       _______, _______, _______, _______, _______,
                                           _______, M_TFLIP,
                                                    M_SHRUG,
                                  _______, _______, M_WHY  ,

       _______, AKC_6  , AKC_7  , AKC_8  , AKC_9  , AKC_0  , _______,
       _______, _______, _______, _______, _______, _______, A_TILDE,
                _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),

/* Keymap 2: Media Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |  `´  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |BlStep|Pl/Pa |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Bl+  |       | Vol+ |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      | Bl-  |       | Vol- |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MEDIA] = LAYOUT_ergodox(
       _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           BL_STEP, KC_MPLY,
                                                    BL_INC ,
                                  _______, _______, BL_DEC ,

       _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
       _______, _______, _______, _______, _______, _______, KC_F12 ,
                _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       KC_VOLU,
       KC_VOLD, _______, _______
),

/* Keymap 3: Qwerty layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   +    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   -  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *  | Media |      |      | LAlt | LGui |                                       | Symb | Left | Down |  Up  | Right |
 *  `-----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Insrt| Del  |       | MPrv | MNxt |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |  Ctrl  |      |
 *                                 `--------------------'       `----------------------'
 */
[QWERTY] = LAYOUT_ergodox(
        _______, _______, KC_2   , KC_3   , KC_4   , KC_5   , _______,
        _______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______,
        _______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,
        _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,
        _______, _______, _______, _______, _______,
                                                     _______, _______,
                                                              _______,
                                           _______ , _______, _______,

        _______, _______, _______, _______, _______, _______, _______,
        _______, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_AO  ,
                 KC_H   , KC_J   , KC_K   , KC_L   , SE_OE  , SE_AE  ,
        _______, KC_N   , KC_M   , KC_COMM, KC_DOT , SE_MINS, _______,
                          _______, _______, _______, _______, _______,
        _______, _______,
        _______,
        _______, _______, _______
    ),

};

const uint16_t PROGMEM fn_actions[] = {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    idle_timer = timer_read32();

    if (led_matrix_get_mode() != LED_MATRIX_SOLID) {
        led_matrix_mode_noeeprom(LED_MATRIX_SOLID);
    }

    switch (keycode) {
    case M_SHRUG:
        if (record->event.pressed) {
            send_unicode_string("ლ(ಠ益ಠლ)");
        }
        return false;
    case M_TFLIP:
        if (record->event.pressed) {
            send_unicode_string("(ノಠ益ಠ)ノ彡┻━┻");
        }
        return false;
    case M_WHY:
        if (record->event.pressed) {
            send_unicode_string("¯\\_(ツ)_/¯");
        }
        return false;
    }
    return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
    case 0:
        if (record->event.pressed) {
            register_code(KC_RSFT);
        } else {
            unregister_code(KC_RSFT);
        }
        break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    if (timer_elapsed32(idle_timer) > IDLE_TIMEOUT && led_matrix_get_mode() != LED_MATRIX_BREATHING) {
        led_matrix_mode_noeeprom(LED_MATRIX_BREATHING);
    }

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
    case 1:
        ergodox_right_led_1_on();
        break;
    case 2:
        ergodox_right_led_2_on();
        break;
    default:
        break;
    }
};
