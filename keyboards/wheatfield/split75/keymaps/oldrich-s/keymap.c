#include QMK_KEYBOARD_H

enum layer_names {
  BASE
};

enum custom_keycodes {
    FNKEY = SAFE_RANGE
};

bool isCtrl = false;
bool isFn = false;
bool lAltDown = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LALT && record->event.pressed) {
      lAltDown = true;
      return false;
    }

    if (lAltDown) {
      lAltDown = false;
      if(keycode == KC_LALT) {
        return false;
      } else {
        SEND_STRING(SS_DOWN(X_LALT)SS_DELAY(1));
      }
    }

    if (keycode == KC_LCTL) {
        if (record->event.pressed) isCtrl = true;
        else isCtrl = false;
    } else if (keycode == FNKEY) {
        if (record->event.pressed) isFn = true;
        else isFn = false;
    } else if (isCtrl && keycode >= KC_MS_UP && keycode <= KC_MS_WH_RIGHT) {
        if (!record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL));
            SEND_STRING(SS_DOWN(X_LALT));
            if (keycode == KC_MS_UP) SEND_STRING("1");
            else if (keycode == KC_MS_RIGHT) SEND_STRING("2");
            else if (keycode == KC_MS_LEFT) SEND_STRING("3");
            else if (keycode == KC_MS_DOWN) SEND_STRING("4");
            else if (keycode == KC_MS_WH_UP) SEND_STRING("5");
            else if (keycode == KC_MS_WH_RIGHT) SEND_STRING("6");
            else if (keycode == KC_MS_WH_LEFT) SEND_STRING("7");
            else if (keycode == KC_MS_WH_DOWN) SEND_STRING("8");
            SEND_STRING(SS_UP(X_LALT));
            SEND_STRING(SS_UP(X_LCTRL));
        }
        return false;
    } else if (isFn) {
        if (!record->event.pressed) {
            if (keycode == KC_ENTER) SEND_STRING(SS_DOWN(X_MEDIA_PLAY_PAUSE)SS_DELAY(50)SS_UP(X_MEDIA_PLAY_PAUSE));
            else if (keycode == KC_UP) SEND_STRING(SS_DOWN(X_AUDIO_VOL_UP)SS_DELAY(50)SS_UP(X_AUDIO_VOL_UP));
            else if (keycode == KC_DOWN) SEND_STRING(SS_DOWN(X_AUDIO_VOL_DOWN)SS_DELAY(50)SS_UP(X_AUDIO_VOL_DOWN));
            else if (keycode == KC_LEFT) SEND_STRING(SS_DOWN(X_MEDIA_PREV_TRACK)SS_DELAY(50)SS_UP(X_MEDIA_PREV_TRACK));
            else if (keycode == KC_RIGHT) SEND_STRING(SS_DOWN(X_MEDIA_NEXT_TRACK)SS_DELAY(50)SS_UP(X_MEDIA_NEXT_TRACK));
        }
        return false;
    }

    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base          ,-----------------------------------------.     ,-----------------------------------------------------.
  *                | ESC | F1  | F2  | F3  | F4  | F5  | F6  |     | F7  | F8  | F9  | F10 | F11 | F12 |Print| Ins | Del |
  * ,-----------.  |-----+-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----+-----------+-----|
  * |  8  |  9  |  |  ~  |  1  |  2  |  3  |  4  |  5  |  6  |     |  7  |  8  |  9  |  0  |  -  |  =  | Backspac  | Home|
  * |-----+-----|  |-----------------------------------------'  ,--------------------------------------------------+-----|
  * |  6  |  7  |  | Tab   |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \    | PgUp|
  * |-----+-----|  |---------------------------------------.    `--------------------------------------------------+-----|
  * |  4  |  5  |  | Caps    |  A  |  S  |  D  |  F  |  G  |     |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | PgDn|
  * |-----+-----|  |-----------------------------------------.   `-------------------------------------------------+-----|
  * |  2  |  3  |  | Shift     |  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |   /   |  Shift  | Up  | End |
  * |-----+-----|  |-----------------------------------------'   ,-------------------------------------------+-----+-----|
  * |  0  |  1  |  | Ctrl  |  GUI |  Alt |   Space   |Space|     | Space         |  Alt  |     | Ctrl  | Left| Down|Right|
  * `-----------'  `---------------------------------------'     `-------------------------------------------------------'
  */
  [BASE] = LAYOUT(
//--------------------------------Left Hand-----------------------------------| |--------------------------------Right Hand------------------------------------------------
                                KC_ESC,   KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,  KC_F6,                KC_F7,  KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,   KC_PSCR,  KC_INS,  KC_DEL,
KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_GRAVE, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,                 KC_7,   KC_8,    KC_9,   KC_0,    KC_MINUS, KC_EQUAL, KC_BSPC,           KC_HOME,
KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                 KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_PGUP,
KC_MS_BTN1,     KC_MS_BTN2,     KC_CAPS,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                 KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,  KC_ENTER,                    KC_PGDN,
KC_MS_UP,       KC_MS_RIGHT,    KC_LSFT,  KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,                 KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,                     KC_RSFT,  KC_UP,   KC_END,
KC_MS_LEFT,     KC_MS_DOWN,     KC_LCTL,  KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC,               KC_RALT, FNKEY,  KC_RCTL,               KC_LEFT,  KC_DOWN, KC_RIGHT
  )
};
