#pragma once
#include <array>

#include <allegro5/allegro.h>

// pressed: if the key is pressed down
// released: if the key is not pressed down
// keydown: if the key has just been clicked
// keyup: if the key has just been released
struct KeyState {
	bool pressed;
	bool released;
	bool keydown;
	bool keyup;
};

class Keyboard {
public:
	// Copied from allegro
	enum KeyCode {
		KEY_A = 0,
		KEY_B = 1,
		KEY_C = 2,
		KEY_D = 3,
		KEY_E = 4,
		KEY_F = 5,
		KEY_G = 6,
		KEY_H = 7,
		KEY_I = 8,
		KEY_J = 9,
		KEY_K = 10,
		KEY_L = 11,
		KEY_M = 12,
		KEY_N = 13,
		KEY_O = 14,
		KEY_P = 15,
		KEY_Q = 16,
		KEY_R = 17,
		KEY_S = 18,
		KEY_T = 19,
		KEY_U = 20,
		KEY_V = 21,
		KEY_W = 22,
		KEY_X = 23,
		KEY_Y = 24,
		KEY_Z = 25,

		KEY_0 = 26,
		KEY_1 = 27,
		KEY_2 = 28,
		KEY_3 = 29,
		KEY_4 = 30,
		KEY_5 = 31,
		KEY_6 = 32,
		KEY_7 = 33,
		KEY_8 = 34,
		KEY_9 = 35,

		KEY_PAD_0 = 36,
		KEY_PAD_1 = 37,
		KEY_PAD_2 = 38,
		KEY_PAD_3 = 39,
		KEY_PAD_4 = 40,
		KEY_PAD_5 = 41,
		KEY_PAD_6 = 42,
		KEY_PAD_7 = 43,
		KEY_PAD_8 = 44,
		KEY_PAD_9 = 45,

		KEY_F1 = 46,
		KEY_F2 = 47,
		KEY_F3 = 48,
		KEY_F4 = 49,
		KEY_F5 = 50,
		KEY_F6 = 51,
		KEY_F7 = 52,
		KEY_F8 = 53,
		KEY_F9 = 54,
		KEY_F10 = 55,
		KEY_F11 = 56,
		KEY_F12 = 57,

		KEY_ESCAPE = 58,
		KEY_TILDE = 59,
		KEY_MINUS = 60,
		KEY_EQUALS = 61,
		KEY_BACKSPACE = 62,
		KEY_TAB = 63,
		KEY_OPENBRACE = 64,
		KEY_CLOSEBRACE = 65,
		KEY_ENTER = 66,
		KEY_SEMICOLON = 67,
		KEY_QUOTE = 68,
		KEY_BACKSLASH = 69,
		KEY_BACKSLASH2 = 70, /* DirectInput calls this DIK_OEM_102: "< > | on UK/Germany keyboards" */
		KEY_COMMA = 71,
		KEY_FULLSTOP = 72,
		KEY_SLASH = 73,
		KEY_SPACE = 74,

		KEY_INSERT = 75,
		KEY_DELETE = 76,
		KEY_HOME = 77,
		KEY_END = 78,
		KEY_PGUP = 79,
		KEY_PGDN = 80,
		KEY_LEFT = 81,
		KEY_RIGHT = 82,
		KEY_UP = 83,
		KEY_DOWN = 84,

		KEY_PAD_SLASH = 85,
		KEY_PAD_ASTERISK = 86,
		KEY_PAD_MINUS = 87,
		KEY_PAD_PLUS = 88,
		KEY_PAD_DELETE = 89,
		KEY_PAD_ENTER = 90,

		KEY_PRINTSCREEN = 91,
		KEY_PAUSE = 92,

		KEY_ABNT_C1 = 93,
		KEY_YEN = 94,
		KEY_KANA = 95,
		KEY_CONVERT = 96,
		KEY_NOCONVERT = 97,
		KEY_AT = 98,
		KEY_CIRCUMFLEX = 99,
		KEY_COLON2 = 100,
		KEY_KANJI = 101,

		KEY_PAD_EQUALS = 102,	/* MacOS X */
		KEY_BACKQUOTE = 103,	/* MacOS X */
		KEY_SEMICOLON2 = 104,	/* MacOS X -- TODO: ask lillo what this should be */
		KEY_COMMAND = 105,	/* MacOS X */

		KEY_BACK = 106,        /* Android back key */
		KEY_VOLUME_UP = 107,
		KEY_VOLUME_DOWN = 108,

		/* Android game keys */
		KEY_SEARCH = 109,
		KEY_DPAD_CENTER = 110,
		KEY_BUTTON_X = 111,
		KEY_BUTTON_Y = 112,
		KEY_DPAD_UP = 113,
		KEY_DPAD_DOWN = 114,
		KEY_DPAD_LEFT = 115,
		KEY_DPAD_RIGHT = 116,
		KEY_SELECT = 117,
		KEY_START = 118,
		KEY_BUTTON_L1 = 119,
		KEY_BUTTON_R1 = 120,
		KEY_BUTTON_L2 = 121,
		KEY_BUTTON_R2 = 122,
		KEY_BUTTON_A = 123,
		KEY_BUTTON_B = 124,
		KEY_THUMBL = 125,
		KEY_THUMBR = 126,

		KEY_UNKNOWN = 127,

		/* All codes up to before KEY_MODIFIERS can be freely
		 * assignedas additional unknown keys, like various multimedia
		 * and application keys keyboards may have.
		 */

		KEY_MODIFIERS = 214,

		KEY_LSHIFT = 214,
		KEY_RSHIFT = 215,
		KEY_LCTRL = 216,
		KEY_RCTRL = 217,
		KEY_ALT = 218,
		KEY_ALTGR = 219,
		KEY_LWIN = 220,
		KEY_RWIN = 221,
		KEY_MENU = 222,
		KEY_SCROLLLOCK = 223,
		KEY_NUMLOCK = 224,
		KEY_CAPSLOCK = 225,

		KEY_MAX
	};

	Keyboard() = delete;

	// Set all key states to the intiailzie state
	// (pressed = 0, released = 0, keydown = 0, keyup = 0)
	static void initialize();

	// Update all the key states
	static void update();

	// Returns a keystate of a certain key code
	static KeyState get(KeyCode code);
private:
	static std::array<KeyState, KeyCode::KEY_MAX> s_states;
	static std::array<KeyState, KeyCode::KEY_MAX> s_lastStates;
};