/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "../btj_keyboard_backend.h"

#include <cstring>
#include "SDL.h"
#include "btj_key_event.h"
#include "../btj_event.h"

namespace btj
{
namespace KeyboardBackend
{

static_assert(sizeof(SDL_Event) <= sizeof(Event), "");

namespace
{
    KeyEvent getKeyEvent(const SDL_Event& sdlEvent) noexcept
    {
        Key key = Key::UNKNOWN;

        switch(sdlEvent.key.keysym.sym)
        {

        case SDLK_UNKNOWN:
            key = Key::UNKNOWN;
            break;

        case SDLK_RETURN:
            key = Key::RETURN;
            break;

        case SDLK_ESCAPE:
            key = Key::ESCAPE;
            break;

        case SDLK_BACKSPACE:
            key = Key::BACKSPACE;
            break;

        case SDLK_TAB:
            key = Key::TAB;
            break;

        case SDLK_SPACE:
            key = Key::SPACE;
            break;

        case SDLK_EXCLAIM:
            key = Key::EXCLAIM;
            break;

        case SDLK_QUOTEDBL:
            key = Key::QUOTEDBL;
            break;

        case SDLK_HASH:
            key = Key::HASH;
            break;

        case SDLK_PERCENT:
            key = Key::PERCENT;
            break;

        case SDLK_DOLLAR:
            key = Key::DOLLAR;
            break;

        case SDLK_AMPERSAND:
            key = Key::AMPERSAND;
            break;

        case SDLK_QUOTE:
            key = Key::QUOTE;
            break;

        case SDLK_LEFTPAREN:
            key = Key::LEFTPAREN;
            break;

        case SDLK_RIGHTPAREN:
            key = Key::RIGHTPAREN;
            break;

        case SDLK_ASTERISK:
            key = Key::ASTERISK;
            break;

        case SDLK_PLUS:
            key = Key::PLUS;
            break;

        case SDLK_COMMA:
            key = Key::COMMA;
            break;

        case SDLK_MINUS:
            key = Key::MINUS;
            break;

        case SDLK_PERIOD:
            key = Key::PERIOD;
            break;

        case SDLK_SLASH:
            key = Key::SLASH;
            break;

        case SDLK_0:
            key = Key::DIGIT_0;
            break;

        case SDLK_1:
            key = Key::DIGIT_1;
            break;

        case SDLK_2:
            key = Key::DIGIT_2;
            break;

        case SDLK_3:
            key = Key::DIGIT_3;
            break;

        case SDLK_4:
            key = Key::DIGIT_4;
            break;

        case SDLK_5:
            key = Key::DIGIT_5;
            break;

        case SDLK_6:
            key = Key::DIGIT_6;
            break;

        case SDLK_7:
            key = Key::DIGIT_7;
            break;

        case SDLK_8:
            key = Key::DIGIT_8;
            break;

        case SDLK_9:
            key = Key::DIGIT_9;
            break;

        case SDLK_COLON:
            key = Key::COLON;
            break;

        case SDLK_SEMICOLON:
            key = Key::SEMICOLON;
            break;

        case SDLK_LESS:
            key = Key::LESS;
            break;

        case SDLK_EQUALS:
            key = Key::EQUALS;
            break;

        case SDLK_GREATER:
            key = Key::GREATER;
            break;

        case SDLK_QUESTION:
            key = Key::QUESTION;
            break;

        case SDLK_AT:
            key = Key::AT;
            break;

        case SDLK_LEFTBRACKET:
            key = Key::LEFTBRACKET;
            break;

        case SDLK_BACKSLASH:
            key = Key::BACKSLASH;
            break;

        case SDLK_RIGHTBRACKET:
            key = Key::RIGHTBRACKET;
            break;

        case SDLK_CARET:
            key = Key::CARET;
            break;

        case SDLK_UNDERSCORE:
            key = Key::UNDERSCORE;
            break;

        case SDLK_BACKQUOTE:
            key = Key::BACKQUOTE;
            break;

        case SDLK_a:
            key = Key::A;
            break;

        case SDLK_b:
            key = Key::B;
            break;

        case SDLK_c:
            key = Key::C;
            break;

        case SDLK_d:
            key = Key::D;
            break;

        case SDLK_e:
            key = Key::E;
            break;

        case SDLK_f:
            key = Key::F;
            break;

        case SDLK_g:
            key = Key::G;
            break;

        case SDLK_h:
            key = Key::H;
            break;

        case SDLK_i:
            key = Key::I;
            break;

        case SDLK_j:
            key = Key::J;
            break;

        case SDLK_k:
            key = Key::K;
            break;

        case SDLK_l:
            key = Key::L;
            break;

        case SDLK_m:
            key = Key::M;
            break;

        case SDLK_n:
            key = Key::N;
            break;

        case SDLK_o:
            key = Key::O;
            break;

        case SDLK_p:
            key = Key::P;
            break;

        case SDLK_q:
            key = Key::Q;
            break;

        case SDLK_r:
            key = Key::R;
            break;

        case SDLK_s:
            key = Key::S;
            break;

        case SDLK_t:
            key = Key::T;
            break;

        case SDLK_u:
            key = Key::U;
            break;

        case SDLK_v:
            key = Key::V;
            break;

        case SDLK_w:
            key = Key::W;
            break;

        case SDLK_x:
            key = Key::X;
            break;

        case SDLK_y:
            key = Key::Y;
            break;

        case SDLK_z:
            key = Key::Z;
            break;

        case SDLK_CAPSLOCK:
            key = Key::CAPSLOCK;
            break;

        case SDLK_F1:
            key = Key::F1;
            break;

        case SDLK_F2:
            key = Key::F2;
            break;

        case SDLK_F3:
            key = Key::F3;
            break;

        case SDLK_F4:
            key = Key::F4;
            break;

        case SDLK_F5:
            key = Key::F5;
            break;

        case SDLK_F6:
            key = Key::F6;
            break;

        case SDLK_F7:
            key = Key::F7;
            break;

        case SDLK_F8:
            key = Key::F8;
            break;

        case SDLK_F9:
            key = Key::F9;
            break;

        case SDLK_F10:
            key = Key::F10;
            break;

        case SDLK_F11:
            key = Key::F11;
            break;

        case SDLK_F12:
            key = Key::F12;
            break;

        case SDLK_PRINTSCREEN:
            key = Key::PRINTSCREEN;
            break;

        case SDLK_SCROLLLOCK:
            key = Key::SCROLLLOCK;
            break;

        case SDLK_PAUSE:
            key = Key::PAUSE;
            break;

        case SDLK_INSERT:
            key = Key::INSERT;
            break;

        case SDLK_HOME:
            key = Key::HOME;
            break;

        case SDLK_PAGEUP:
            key = Key::PAGEUP;
            break;

        case SDLK_DELETE:
            key = Key::DELETE;
            break;

        case SDLK_END:
            key = Key::END;
            break;

        case SDLK_PAGEDOWN:
            key = Key::PAGEDOWN;
            break;

        case SDLK_RIGHT:
            key = Key::RIGHT;
            break;

        case SDLK_LEFT:
            key = Key::LEFT;
            break;

        case SDLK_DOWN:
            key = Key::DOWN;
            break;

        case SDLK_UP:
            key = Key::UP;
            break;

        case SDLK_NUMLOCKCLEAR:
            key = Key::NUMLOCKCLEAR;
            break;

        case SDLK_KP_DIVIDE:
            key = Key::KP_DIVIDE;
            break;

        case SDLK_KP_MULTIPLY:
            key = Key::KP_MULTIPLY;
            break;

        case SDLK_KP_MINUS:
            key = Key::KP_MINUS;
            break;

        case SDLK_KP_PLUS:
            key = Key::KP_PLUS;
            break;

        case SDLK_KP_ENTER:
            key = Key::KP_ENTER;
            break;

        case SDLK_KP_1:
            key = Key::KP_1;
            break;

        case SDLK_KP_2:
            key = Key::KP_2;
            break;

        case SDLK_KP_3:
            key = Key::KP_3;
            break;

        case SDLK_KP_4:
            key = Key::KP_4;
            break;

        case SDLK_KP_5:
            key = Key::KP_5;
            break;

        case SDLK_KP_6:
            key = Key::KP_6;
            break;

        case SDLK_KP_7:
            key = Key::KP_7;
            break;

        case SDLK_KP_8:
            key = Key::KP_8;
            break;

        case SDLK_KP_9:
            key = Key::KP_9;
            break;

        case SDLK_KP_0:
            key = Key::KP_0;
            break;

        case SDLK_KP_PERIOD:
            key = Key::KP_PERIOD;
            break;

        case SDLK_APPLICATION:
            key = Key::APPLICATION;
            break;

        case SDLK_POWER:
            key = Key::POWER;
            break;

        case SDLK_KP_EQUALS:
            key = Key::KP_EQUALS;
            break;

        case SDLK_F13:
            key = Key::F13;
            break;

        case SDLK_F14:
            key = Key::F14;
            break;

        case SDLK_F15:
            key = Key::F15;
            break;

        case SDLK_F16:
            key = Key::F16;
            break;

        case SDLK_F17:
            key = Key::F17;
            break;

        case SDLK_F18:
            key = Key::F18;
            break;

        case SDLK_F19:
            key = Key::F19;
            break;

        case SDLK_F20:
            key = Key::F20;
            break;

        case SDLK_F21:
            key = Key::F21;
            break;

        case SDLK_F22:
            key = Key::F22;
            break;

        case SDLK_F23:
            key = Key::F23;
            break;

        case SDLK_F24:
            key = Key::F24;
            break;

        case SDLK_EXECUTE:
            key = Key::EXECUTE;
            break;

        case SDLK_HELP:
            key = Key::HELP;
            break;

        case SDLK_MENU:
            key = Key::MENU;
            break;

        case SDLK_SELECT:
            key = Key::SELECT;
            break;

        case SDLK_STOP:
            key = Key::STOP;
            break;

        case SDLK_AGAIN:
            key = Key::AGAIN;
            break;

        case SDLK_UNDO:
            key = Key::UNDO;
            break;

        case SDLK_CUT:
            key = Key::CUT;
            break;

        case SDLK_COPY:
            key = Key::COPY;
            break;

        case SDLK_PASTE:
            key = Key::PASTE;
            break;

        case SDLK_FIND:
            key = Key::FIND;
            break;

        case SDLK_MUTE:
            key = Key::MUTE;
            break;

        case SDLK_VOLUMEUP:
            key = Key::VOLUMEUP;
            break;

        case SDLK_VOLUMEDOWN:
            key = Key::VOLUMEDOWN;
            break;

        case SDLK_KP_COMMA:
            key = Key::KP_COMMA;
            break;

        case SDLK_KP_EQUALSAS400:
            key = Key::KP_EQUALSAS400;
            break;

        case SDLK_ALTERASE:
            key = Key::ALTERASE;
            break;

        case SDLK_SYSREQ:
            key = Key::SYSREQ;
            break;

        case SDLK_CANCEL:
            key = Key::CANCEL;
            break;

        case SDLK_CLEAR:
            key = Key::CLEAR;
            break;

        case SDLK_PRIOR:
            key = Key::PRIOR;
            break;

        case SDLK_RETURN2:
            key = Key::RETURN2;
            break;

        case SDLK_SEPARATOR:
            key = Key::SEPARATOR;
            break;

        case SDLK_OUT:
            key = Key::OUT;
            break;

        case SDLK_OPER:
            key = Key::OPER;
            break;

        case SDLK_CLEARAGAIN:
            key = Key::CLEARAGAIN;
            break;

        case SDLK_CRSEL:
            key = Key::CRSEL;
            break;

        case SDLK_EXSEL:
            key = Key::EXSEL;
            break;

        case SDLK_KP_00:
            key = Key::KP_00;
            break;

        case SDLK_KP_000:
            key = Key::KP_000;
            break;

        case SDLK_THOUSANDSSEPARATOR:
            key = Key::THOUSANDSSEPARATOR;
            break;

        case SDLK_DECIMALSEPARATOR:
            key = Key::DECIMALSEPARATOR;
            break;

        case SDLK_CURRENCYUNIT:
            key = Key::CURRENCYUNIT;
            break;

        case SDLK_CURRENCYSUBUNIT:
            key = Key::CURRENCYSUBUNIT;
            break;

        case SDLK_KP_LEFTPAREN:
            key = Key::KP_LEFTPAREN;
            break;

        case SDLK_KP_RIGHTPAREN:
            key = Key::KP_RIGHTPAREN;
            break;

        case SDLK_KP_LEFTBRACE:
            key = Key::KP_LEFTBRACE;
            break;

        case SDLK_KP_RIGHTBRACE:
            key = Key::KP_RIGHTBRACE;
            break;

        case SDLK_KP_TAB:
            key = Key::KP_TAB;
            break;

        case SDLK_KP_BACKSPACE:
            key = Key::KP_BACKSPACE;
            break;

        case SDLK_KP_A:
            key = Key::KP_A;
            break;

        case SDLK_KP_B:
            key = Key::KP_B;
            break;

        case SDLK_KP_C:
            key = Key::KP_C;
            break;

        case SDLK_KP_D:
            key = Key::KP_D;
            break;

        case SDLK_KP_E:
            key = Key::KP_E;
            break;

        case SDLK_KP_F:
            key = Key::KP_F;
            break;

        case SDLK_KP_XOR:
            key = Key::KP_XOR;
            break;

        case SDLK_KP_POWER:
            key = Key::KP_POWER;
            break;

        case SDLK_KP_PERCENT:
            key = Key::KP_PERCENT;
            break;

        case SDLK_KP_LESS:
            key = Key::KP_LESS;
            break;

        case SDLK_KP_GREATER:
            key = Key::KP_GREATER;
            break;

        case SDLK_KP_AMPERSAND:
            key = Key::KP_AMPERSAND;
            break;

        case SDLK_KP_DBLAMPERSAND:
            key = Key::KP_DBLAMPERSAND;
            break;

        case SDLK_KP_VERTICALBAR:
            key = Key::KP_VERTICALBAR;
            break;

        case SDLK_KP_DBLVERTICALBAR:
            key = Key::KP_DBLVERTICALBAR;
            break;

        case SDLK_KP_COLON:
            key = Key::KP_COLON;
            break;

        case SDLK_KP_HASH:
            key = Key::KP_HASH;
            break;

        case SDLK_KP_SPACE:
            key = Key::KP_SPACE;
            break;

        case SDLK_KP_AT:
            key = Key::KP_AT;
            break;

        case SDLK_KP_EXCLAM:
            key = Key::KP_EXCLAM;
            break;

        case SDLK_KP_MEMSTORE:
            key = Key::KP_MEMSTORE;
            break;

        case SDLK_KP_MEMRECALL:
            key = Key::KP_MEMRECALL;
            break;

        case SDLK_KP_MEMCLEAR:
            key = Key::KP_MEMCLEAR;
            break;

        case SDLK_KP_MEMADD:
            key = Key::KP_MEMADD;
            break;

        case SDLK_KP_MEMSUBTRACT:
            key = Key::KP_MEMSUBTRACT;
            break;

        case SDLK_KP_MEMMULTIPLY:
            key = Key::KP_MEMMULTIPLY;
            break;

        case SDLK_KP_MEMDIVIDE:
            key = Key::KP_MEMDIVIDE;
            break;

        case SDLK_KP_PLUSMINUS:
            key = Key::KP_PLUSMINUS;
            break;

        case SDLK_KP_CLEAR:
            key = Key::KP_CLEAR;
            break;

        case SDLK_KP_CLEARENTRY:
            key = Key::KP_CLEARENTRY;
            break;

        case SDLK_KP_BINARY:
            key = Key::KP_BINARY;
            break;

        case SDLK_KP_OCTAL:
            key = Key::KP_OCTAL;
            break;

        case SDLK_KP_DECIMAL:
            key = Key::KP_DECIMAL;
            break;

        case SDLK_KP_HEXADECIMAL:
            key = Key::KP_HEXADECIMAL;
            break;

        case SDLK_LCTRL:
            key = Key::LCTRL;
            break;

        case SDLK_LSHIFT:
            key = Key::LSHIFT;
            break;

        case SDLK_LALT:
            key = Key::LALT;
            break;

        case SDLK_LGUI:
            key = Key::LGUI;
            break;

        case SDLK_RCTRL:
            key = Key::RCTRL;
            break;

        case SDLK_RSHIFT:
            key = Key::RSHIFT;
            break;

        case SDLK_RALT:
            key = Key::RALT;
            break;

        case SDLK_RGUI:
            key = Key::RGUI;
            break;

        case SDLK_MODE:
            key = Key::MODE;
            break;

        case SDLK_AUDIONEXT:
            key = Key::AUDIONEXT;
            break;

        case SDLK_AUDIOPREV:
            key = Key::AUDIOPREV;
            break;

        case SDLK_AUDIOSTOP:
            key = Key::AUDIOSTOP;
            break;

        case SDLK_AUDIOPLAY:
            key = Key::AUDIOPLAY;
            break;

        case SDLK_AUDIOMUTE:
            key = Key::AUDIOMUTE;
            break;

        case SDLK_MEDIASELECT:
            key = Key::MEDIASELECT;
            break;

        case SDLK_WWW:
            key = Key::WWW;
            break;

        case SDLK_MAIL:
            key = Key::MAIL;
            break;

        case SDLK_CALCULATOR:
            key = Key::CALCULATOR;
            break;

        case SDLK_COMPUTER:
            key = Key::COMPUTER;
            break;

        case SDLK_AC_SEARCH:
            key = Key::AC_SEARCH;
            break;

        case SDLK_AC_HOME:
            key = Key::AC_HOME;
            break;

        case SDLK_AC_BACK:
            key = Key::AC_BACK;
            break;

        case SDLK_AC_FORWARD:
            key = Key::AC_FORWARD;
            break;

        case SDLK_AC_STOP:
            key = Key::AC_STOP;
            break;

        case SDLK_AC_REFRESH:
            key = Key::AC_REFRESH;
            break;

        case SDLK_AC_BOOKMARKS:
            key = Key::AC_BOOKMARKS;
            break;

        case SDLK_BRIGHTNESSDOWN:
            key = Key::BRIGHTNESSDOWN;
            break;

        case SDLK_BRIGHTNESSUP:
            key = Key::BRIGHTNESSUP;
            break;

        case SDLK_DISPLAYSWITCH:
            key = Key::DISPLAYSWITCH;
            break;

        case SDLK_KBDILLUMTOGGLE:
            key = Key::KBDILLUMTOGGLE;
            break;

        case SDLK_KBDILLUMDOWN:
            key = Key::KBDILLUMDOWN;
            break;

        case SDLK_KBDILLUMUP:
            key = Key::KBDILLUMUP;
            break;

        case SDLK_EJECT:
            key = Key::EJECT;
            break;

        case SDLK_SLEEP:
            key = Key::SLEEP;
            break;

        case SDLK_APP1:
            key = Key::APP1;
            break;

        case SDLK_APP2:
            key = Key::APP2;
            break;

        case SDLK_AUDIOREWIND:
            key = Key::AUDIOREWIND;
            break;

        case SDLK_AUDIOFASTFORWARD:
            key = Key::AUDIOFASTFORWARD;
            break;
        }

        SDL_Keymod sdlModState = SDL_GetModState();
        KeyEvent keyEvent;
        keyEvent.setKey(key);
        keyEvent.setLeftShiftActive(sdlModState & KMOD_LSHIFT);
        keyEvent.setRightShiftActive(sdlModState & KMOD_RSHIFT);
        keyEvent.setLeftCtrlActive(sdlModState & KMOD_LCTRL);
        keyEvent.setRightCtrlActive(sdlModState & KMOD_RCTRL);
        keyEvent.setLeftAltActive(sdlModState & KMOD_LALT);
        keyEvent.setRightAltActive(sdlModState & KMOD_RALT);
        keyEvent.setLeftGuiActive(sdlModState & KMOD_LGUI);
        keyEvent.setRightGuiActive(sdlModState & KMOD_LGUI);
        keyEvent.setNumActive(sdlModState & KMOD_NUM);
        keyEvent.setCapsActive(sdlModState & KMOD_CAPS);
        keyEvent.setModeActive(sdlModState & KMOD_MODE);
        return keyEvent;
    }
}

bool init()
{
    // Keyboard is setup in SDL core backend.
    return true;
}

void destroy() noexcept
{
    // Keyboard is setup in SDL core backend.
}

Optional<KeyEvent> getPressedKeyEvent(const Event& event)
{
    SDL_Event sdlEvent;
    std::memcpy(&sdlEvent, &event, sizeof(SDL_Event));
    Optional<KeyEvent> result;

    if(sdlEvent.type == SDL_KEYDOWN)
    {
        result = getKeyEvent(sdlEvent);
    }

    return result;
}

Optional<KeyEvent> getReleasedKeyEvent(const Event& event)
{
    SDL_Event sdlEvent;
    std::memcpy(&sdlEvent, &event, sizeof(SDL_Event));
    Optional<KeyEvent> result;

    if(sdlEvent.type == SDL_KEYUP)
    {
        result = getKeyEvent(sdlEvent);
    }

    return result;
}

void update()
{
}

}
}
