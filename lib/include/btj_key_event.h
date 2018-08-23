/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_KEY_EVENT_H
#define BTJ_KEY_EVENT_H

#include <bitset>

namespace btj
{

enum class Key
{
    UNKNOWN,
    RETURN,
    ESCAPE,
    BACKSPACE,
    TAB,
    SPACE,
    EXCLAIM,
    QUOTEDBL,
    HASH,
    PERCENT,
    DOLLAR,
    AMPERSAND,
    QUOTE,
    LEFTPAREN,
    RIGHTPAREN,
    ASTERISK,
    PLUS,
    COMMA,
    MINUS,
    PERIOD,
    SLASH,
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
    COLON,
    SEMICOLON,
    LESS,
    EQUALS,
    GREATER,
    QUESTION,
    AT,
    LEFTBRACKET,
    BACKSLASH,
    RIGHTBRACKET,
    CARET,
    UNDERSCORE,
    BACKQUOTE,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    CAPSLOCK,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    PRINTSCREEN,
    SCROLLLOCK,
    PAUSE,
    INSERT,
    HOME,
    PAGEUP,
    DELETE,
    END,
    PAGEDOWN,
    RIGHT,
    LEFT,
    DOWN,
    UP,
    NUMLOCKCLEAR,
    KP_DIVIDE,
    KP_MULTIPLY,
    KP_MINUS,
    KP_PLUS,
    KP_ENTER,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,
    KP_9,
    KP_0,
    KP_PERIOD,
    APPLICATION,
    POWER,
    KP_EQUALS,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    EXECUTE,
    HELP,
    MENU,
    SELECT,
    STOP,
    AGAIN,
    UNDO,
    CUT,
    COPY,
    PASTE,
    FIND,
    MUTE,
    VOLUMEUP,
    VOLUMEDOWN,
    KP_COMMA,
    KP_EQUALSAS400,
    ALTERASE,
    SYSREQ,
    CANCEL,
    CLEAR,
    PRIOR,
    RETURN2,
    SEPARATOR,
    OUT,
    OPER,
    CLEARAGAIN,
    CRSEL,
    EXSEL,
    KP_00,
    KP_000,
    THOUSANDSSEPARATOR,
    DECIMALSEPARATOR,
    CURRENCYUNIT,
    CURRENCYSUBUNIT,
    KP_LEFTPAREN,
    KP_RIGHTPAREN,
    KP_LEFTBRACE,
    KP_RIGHTBRACE,
    KP_TAB,
    KP_BACKSPACE,
    KP_A,
    KP_B,
    KP_C,
    KP_D,
    KP_E,
    KP_F,
    KP_XOR,
    KP_POWER,
    KP_PERCENT,
    KP_LESS,
    KP_GREATER,
    KP_AMPERSAND,
    KP_DBLAMPERSAND,
    KP_VERTICALBAR,
    KP_DBLVERTICALBAR,
    KP_COLON,
    KP_HASH,
    KP_SPACE,
    KP_AT,
    KP_EXCLAM,
    KP_MEMSTORE,
    KP_MEMRECALL,
    KP_MEMCLEAR,
    KP_MEMADD,
    KP_MEMSUBTRACT,
    KP_MEMMULTIPLY,
    KP_MEMDIVIDE,
    KP_PLUSMINUS,
    KP_CLEAR,
    KP_CLEARENTRY,
    KP_BINARY,
    KP_OCTAL,
    KP_DECIMAL,
    KP_HEXADECIMAL,
    LCTRL,
    LSHIFT,
    LALT,
    LGUI,
    RCTRL,
    RSHIFT,
    RALT,
    RGUI,
    MODE,
    AUDIONEXT,
    AUDIOPREV,
    AUDIOSTOP,
    AUDIOPLAY,
    AUDIOMUTE,
    MEDIASELECT,
    WWW,
    MAIL,
    CALCULATOR,
    COMPUTER,
    AC_SEARCH,
    AC_HOME,
    AC_BACK,
    AC_FORWARD,
    AC_STOP,
    AC_REFRESH,
    AC_BOOKMARKS,
    BRIGHTNESSDOWN,
    BRIGHTNESSUP,
    DISPLAYSWITCH,
    KBDILLUMTOGGLE,
    KBDILLUMDOWN,
    KBDILLUMUP,
    EJECT,
    SLEEP,
    APP1,
    APP2,
    AUDIOREWIND,
    AUDIOFASTFORWARD
};

class KeyEvent
{

public:
    KeyEvent() noexcept :
        _key(Key::UNKNOWN)
    {
    }

    Key getKey() const noexcept
    {
        return _key;
    }

    void setKey(Key key) noexcept
    {
        _key = key;
    }

    bool isLeftShiftActive() const noexcept
    {
        return _modifiers[0];
    }

    void setLeftShiftActive(bool active) noexcept
    {
        _modifiers[0] = active;
    }

    bool isRightShiftActive() const noexcept
    {
        return _modifiers[1];
    }

    void setRightShiftActive(bool active) noexcept
    {
        _modifiers[1] = active;
    }

    bool isLeftCtrlActive() const noexcept
    {
        return _modifiers[2];
    }

    void setLeftCtrlActive(bool active) noexcept
    {
        _modifiers[2] = active;
    }

    bool isRightCtrlActive() const noexcept
    {
        return _modifiers[3];
    }

    void setRightCtrlActive(bool active) noexcept
    {
        _modifiers[3] = active;
    }

    bool isLeftAltActive() const noexcept
    {
        return _modifiers[4];
    }

    void setLeftAltActive(bool active) noexcept
    {
        _modifiers[4] = active;
    }

    bool isRightAltActive() const noexcept
    {
        return _modifiers[5];
    }

    void setRightAltActive(bool active) noexcept
    {
        _modifiers[5] = active;
    }

    bool isLeftGuiActive() const noexcept
    {
        return _modifiers[6];
    }

    void setLeftGuiActive(bool active) noexcept
    {
        _modifiers[6] = active;
    }

    bool isRightGuiActive() const noexcept
    {
        return _modifiers[7];
    }

    void setRightGuiActive(bool active) noexcept
    {
        _modifiers[7] = active;
    }

    bool isNumActive() const noexcept
    {
        return _modifiers[8];
    }

    void setNumActive(bool active) noexcept
    {
        _modifiers[8] = active;
    }

    bool isCapsActive() const noexcept
    {
        return _modifiers[9];
    }

    void setCapsActive(bool active) noexcept
    {
        _modifiers[9] = active;
    }

    bool isModeActive() const noexcept
    {
        return _modifiers[10];
    }

    void setModeActive(bool active) noexcept
    {
        _modifiers[10] = active;
    }

private:
    Key _key;
    std::bitset<11> _modifiers;
};

}

#endif
