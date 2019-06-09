#include "HID.h"

#include <Arduino.h>

const uint8_t HID::scancodes[] = {
  [(int)Scancode::A] = 0x4,
  [(int)Scancode::B] = 0x5,
  [(int)Scancode::C] = 0x6,
  [(int)Scancode::D] = 0x7,
  [(int)Scancode::E] = 0x8,
  [(int)Scancode::F] = 0x9,
  [(int)Scancode::G] = 0xa,
  [(int)Scancode::H] = 0xb,
  [(int)Scancode::I] = 0xc,
  [(int)Scancode::J] = 0xd,
  [(int)Scancode::K] = 0xe,
  [(int)Scancode::L] = 0xf,
  [(int)Scancode::M] = 0x10,
  [(int)Scancode::N] = 0x11,
  [(int)Scancode::O] = 0x12,
  [(int)Scancode::P] = 0x13,
  [(int)Scancode::Q] = 0x14,
  [(int)Scancode::R] = 0x15,
  [(int)Scancode::S] = 0x16,
  [(int)Scancode::T] = 0x17,
  [(int)Scancode::U] = 0x18,
  [(int)Scancode::V] = 0x19,
  [(int)Scancode::W] = 0x1a,
  [(int)Scancode::X] = 0x1b,
  [(int)Scancode::Y] = 0x1c,
  [(int)Scancode::Z] = 0x1d,

  [(int)Scancode::Num1] = 0x1e,
  [(int)Scancode::Num2] = 0x1f,
  [(int)Scancode::Num3] = 0x20,
  [(int)Scancode::Num4] = 0x21,
  [(int)Scancode::Num5] = 0x22,
  [(int)Scancode::Num6] = 0x23,
  [(int)Scancode::Num7] = 0x24,
  [(int)Scancode::Num8] = 0x25,
  [(int)Scancode::Num9] = 0x26,
  [(int)Scancode::Num0] = 0x27,

  [(int)Scancode::Enter] = 0x28,
  [(int)Scancode::Esc] = 0x29,
  [(int)Scancode::BSpace] = 0x2a,
  [(int)Scancode::Tab] = 0x2b,
  [(int)Scancode::Space] = 0x2c,
  [(int)Scancode::Minus] = 0x2d,
  [(int)Scancode::Equal] = 0x2e,
  [(int)Scancode::LBrace] = 0x2f,
  [(int)Scancode::RBrace] = 0x30,
  [(int)Scancode::BSlash] = 0x31,
  [(int)Scancode::Tilde] = 0x32,
  [(int)Scancode::Semicolon] = 0x33,
  [(int)Scancode::SQuote] = 0x34,
  [(int)Scancode::Grave] = 0x35,
  [(int)Scancode::Comma] = 0x36,
  [(int)Scancode::Period] = 0x37,
  [(int)Scancode::Slash] = 0x38,

  [(int)Scancode::F1] = 0x3a,
  [(int)Scancode::F2] = 0x3b,
  [(int)Scancode::F3] = 0x3c,
  [(int)Scancode::F4] = 0x3d,
  [(int)Scancode::F5] = 0x3e,
  [(int)Scancode::F6] = 0x3f,
  [(int)Scancode::F7] = 0x40,
  [(int)Scancode::F8] = 0x41,
  [(int)Scancode::F9] = 0x42,
  [(int)Scancode::F10] = 0x43,
  [(int)Scancode::F11] = 0x44,
  [(int)Scancode::F12] = 0x45,
  [(int)Scancode::Home] = 0x4a,
  [(int)Scancode::PgUp] = 0x4b,
  [(int)Scancode::Del] = 0x4c,
  [(int)Scancode::End] = 0x4d,
  [(int)Scancode::PgDn] = 0x4e,
  [(int)Scancode::Right] = 0x4f,
  [(int)Scancode::Left] = 0x50,
  [(int)Scancode::Down] = 0x51,
  [(int)Scancode::Up] = 0x52
};

const uint8_t HID::modifers[] = {
  [(int)Mod::Ctrl] = 1 << 0,
  [(int)Mod::Alt] = 1 << 2,
  [(int)Mod::Shift] = 1 << 1,
  
  [(int)Mod::LCtrl] = 1 << 0,
  [(int)Mod::LShift] = 1 << 1,
  [(int)Mod::LAlt] = 1 << 2,
  [(int)Mod::LCmd] = 1 << 3,
  [(int)Mod::RCtrl] = 1 << 4,
  [(int)Mod::RShift] = 1 << 5,
  [(int)Mod::RAlt] = 1 << 6,
  [(int)Mod::RCmd] = 1 << 7
};

const HID::KeyInfo HID::scancodeMap[] = {
  [(int)Keymap::Key::A] = { .scancode = Scancode::A, .shift = false },
  [(int)Keymap::Key::B] = { .scancode = Scancode::B, .shift = false },
  [(int)Keymap::Key::C] = { .scancode = Scancode::C, .shift = false },
  [(int)Keymap::Key::D] = { .scancode = Scancode::D, .shift = false },
  [(int)Keymap::Key::E] = { .scancode = Scancode::E, .shift = false },
  [(int)Keymap::Key::F] = { .scancode = Scancode::F, .shift = false },
  [(int)Keymap::Key::G] = { .scancode = Scancode::G, .shift = false },
  [(int)Keymap::Key::H] = { .scancode = Scancode::H, .shift = false },
  [(int)Keymap::Key::I] = { .scancode = Scancode::I, .shift = false },
  [(int)Keymap::Key::J] = { .scancode = Scancode::J, .shift = false },
  [(int)Keymap::Key::K] = { .scancode = Scancode::K, .shift = false },
  [(int)Keymap::Key::L] = { .scancode = Scancode::L, .shift = false },
  [(int)Keymap::Key::M] = { .scancode = Scancode::M, .shift = false },
  [(int)Keymap::Key::N] = { .scancode = Scancode::N, .shift = false },
  [(int)Keymap::Key::O] = { .scancode = Scancode::O, .shift = false },
  [(int)Keymap::Key::P] = { .scancode = Scancode::P, .shift = false },
  [(int)Keymap::Key::Q] = { .scancode = Scancode::Q, .shift = false },
  [(int)Keymap::Key::R] = { .scancode = Scancode::R, .shift = false },
  [(int)Keymap::Key::S] = { .scancode = Scancode::S, .shift = false },
  [(int)Keymap::Key::T] = { .scancode = Scancode::T, .shift = false },
  [(int)Keymap::Key::U] = { .scancode = Scancode::U, .shift = false },
  [(int)Keymap::Key::V] = { .scancode = Scancode::V, .shift = false },
  [(int)Keymap::Key::W] = { .scancode = Scancode::W, .shift = false },
  [(int)Keymap::Key::X] = { .scancode = Scancode::X, .shift = false },
  [(int)Keymap::Key::Y] = { .scancode = Scancode::Y, .shift = false },
  [(int)Keymap::Key::Z] = { .scancode = Scancode::Z, .shift = false },

  [(int)Keymap::Key::Num1] = { .scancode = Scancode::Num1, .shift = false },
  [(int)Keymap::Key::Num2] = { .scancode = Scancode::Num2, .shift = false },
  [(int)Keymap::Key::Num3] = { .scancode = Scancode::Num3, .shift = false },
  [(int)Keymap::Key::Num4] = { .scancode = Scancode::Num4, .shift = false },
  [(int)Keymap::Key::Num5] = { .scancode = Scancode::Num5, .shift = false },
  [(int)Keymap::Key::Num6] = { .scancode = Scancode::Num6, .shift = false },
  [(int)Keymap::Key::Num7] = { .scancode = Scancode::Num7, .shift = false },
  [(int)Keymap::Key::Num8] = { .scancode = Scancode::Num8, .shift = false },
  [(int)Keymap::Key::Num9] = { .scancode = Scancode::Num9, .shift = false },
  [(int)Keymap::Key::Num0] = { .scancode = Scancode::Num0, .shift = false },

  [(int)Keymap::Key::Enter] = { .scancode = Scancode::Enter, .shift = false },
  [(int)Keymap::Key::Esc] = { .scancode = Scancode::Esc, .shift = false },
  [(int)Keymap::Key::BSpace] = { .scancode = Scancode::BSpace, .shift = false },
  [(int)Keymap::Key::Tab] = { .scancode = Scancode::Tab, .shift = false },
  [(int)Keymap::Key::Space] = { .scancode = Scancode::Space, .shift = false },
  [(int)Keymap::Key::Minus] = { .scancode = Scancode::Minus, .shift = false },
  [(int)Keymap::Key::Equal] = { .scancode = Scancode::Grave, .shift = false },
  [(int)Keymap::Key::LBrace] = { .scancode = Scancode::LBrace, .shift = false },
  [(int)Keymap::Key::RBrace] = { .scancode = Scancode::RBrace, .shift = false },
  [(int)Keymap::Key::BSlash] = { .scancode = Scancode::BSlash, .shift = false },
  [(int)Keymap::Key::Tilde] = { .scancode = Scancode::Tilde, .shift = false },
  [(int)Keymap::Key::Semicolon] = { .scancode = Scancode::Semicolon, .shift = false },
  [(int)Keymap::Key::SQuote] = { .scancode = Scancode::SQuote, .shift = false },
  [(int)Keymap::Key::Grave] = { .scancode = Scancode::Grave, .shift = false },
  [(int)Keymap::Key::Comma] = { .scancode = Scancode::Comma, .shift = false },
  [(int)Keymap::Key::Period] = { .scancode = Scancode::Period, .shift = false },
  [(int)Keymap::Key::Slash] = { .scancode = Scancode::Slash, .shift = false },
  [(int)Keymap::Key::Percent] = { .scancode = Scancode::Num5, .shift = true },
  [(int)Keymap::Key::At] = { .scancode = Scancode::Num2, .shift = true },
  [(int)Keymap::Key::LBrack] = { .scancode = Scancode::LBrace, .shift = true },
  [(int)Keymap::Key::RBrack] = { .scancode = Scancode::RBrace, .shift = true },
  [(int)Keymap::Key::Carrot] = { .scancode = Scancode::Num6, .shift = true },
  [(int)Keymap::Key::Pound] = { .scancode = Scancode::Num3, .shift = true },
  [(int)Keymap::Key::Dollar] = { .scancode = Scancode::Num4, .shift = true },
  [(int)Keymap::Key::LParen] = { .scancode = Scancode::Num9, .shift = true },
  [(int)Keymap::Key::RParen] = { .scancode = Scancode::Num0, .shift = true },
  [(int)Keymap::Key::Asterisk] = { .scancode = Scancode::Num8, .shift = true },
  [(int)Keymap::Key::Bang] = { .scancode = Scancode::Num1, .shift = true },
  [(int)Keymap::Key::Plus] = { .scancode = Scancode::Equal, .shift = true },
  [(int)Keymap::Key::Underscore] = { .scancode = Scancode::Minus, .shift = true },
  [(int)Keymap::Key::Ampersand] = { .scancode = Scancode::Num7, .shift = true },
  [(int)Keymap::Key::Pipe] = { .scancode = Scancode::BSlash, .shift = true },
  [(int)Keymap::Key::Question] = { .scancode = Scancode::Slash, .shift = true },

  [(int)Keymap::Key::F1] = { .scancode = Scancode::F1, .shift = false },
  [(int)Keymap::Key::F2] = { .scancode = Scancode::F2, .shift = false },
  [(int)Keymap::Key::F3] = { .scancode = Scancode::F3, .shift = false },
  [(int)Keymap::Key::F4] = { .scancode = Scancode::F4, .shift = false },
  [(int)Keymap::Key::F5] = { .scancode = Scancode::F5, .shift = false },
  [(int)Keymap::Key::F6] = { .scancode = Scancode::F6, .shift = false },
  [(int)Keymap::Key::F7] = { .scancode = Scancode::F7, .shift = false },
  [(int)Keymap::Key::F8] = { .scancode = Scancode::F8, .shift = false },
  [(int)Keymap::Key::F9] = { .scancode = Scancode::F9, .shift = false },
  [(int)Keymap::Key::F10] = { .scancode = Scancode::F10, .shift = false },
  [(int)Keymap::Key::F11] = { .scancode = Scancode::F11, .shift = false },
  [(int)Keymap::Key::F12] = { .scancode = Scancode::F12, .shift = false },
  [(int)Keymap::Key::PrintScr] = { .scancode = Scancode::None, .shift = false },
  [(int)Keymap::Key::ScrollLock] = { .scancode = Scancode::None, .shift = false },
  [(int)Keymap::Key::Pause] = { .scancode = Scancode::None, .shift = false },
  [(int)Keymap::Key::Home] = { .scancode = Scancode::Home, .shift = false },
  [(int)Keymap::Key::PgUp] = { .scancode = Scancode::PgUp, .shift = false },
  [(int)Keymap::Key::Del] = { .scancode = Scancode::Del, .shift = false },
  [(int)Keymap::Key::End] = { .scancode = Scancode::End, .shift = false },
  [(int)Keymap::Key::PgDn] = { .scancode = Scancode::PgDn, .shift = false },
  [(int)Keymap::Key::Right] = { .scancode = Scancode::Right, .shift = false },
  [(int)Keymap::Key::Left] = { .scancode = Scancode::Left, .shift = false },
  [(int)Keymap::Key::Down] = { .scancode = Scancode::Down, .shift = false },
  [(int)Keymap::Key::Up] = { .scancode = Scancode::Up, .shift = false },

  [(int)Keymap::Key::Capslock] = { .scancode = Scancode::Esc, .shift = false },
  [(int)Keymap::Key::Insert] = { .scancode = Scancode::BSlash, .shift = false },
  [(int)Keymap::Key::SL1] = { .scancode = Scancode::Equal, .shift = false },
  [(int)Keymap::Key::SL4] = { .scancode = Scancode::BSpace, .shift = false },
  [(int)Keymap::Key::SR1] = { .scancode = Scancode::Minus, .shift = false },
  [(int)Keymap::Key::SR3] = { .scancode = Scancode::Enter, .shift = false },
  [(int)Keymap::Key::SR4] = { .scancode = Scancode::Space, .shift = false },
};

HID::HID(void)
  : bleDIS(), bleHID() {
  memset(&report, 0, sizeof(report));
}

void HID::begin(void) {
  Bluefruit.begin();
  Bluefruit.setName("FeatherCtrl");
  Bluefruit.setTxPower(-8);
  Bluefruit.autoConnLed(false);

  bleDIS.setManufacturer("TODO");
  bleDIS.setModel("TODO");
  
  bleDIS.begin();
  bleHID.begin();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  Bluefruit.Advertising.addService(bleHID);

  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void HID::sendKeys(
  const Keymap *km
) {  
  auto oldReport = report;
  memset(&report, 0, sizeof(report));

  for (int k = 0, i = 0; k < (int)Keymap::Key::Count && i < 6; k++) {
    auto key = (Keymap::Key)k;
    
    auto pressed = km->pressed(key);
    if (!pressed) continue;
    
    switch (key) {
      case Keymap::Key::Ctrl:
        report.modifier |= modifers[(int)HID::Mod::Ctrl]; break;
      case Keymap::Key::Alt:
        report.modifier |= modifers[(int)HID::Mod::Alt]; break;
      case Keymap::Key::Shift:
        report.modifier |= modifers[(int)HID::Mod::Shift]; break;
      case Keymap::Key::Sym: break;

      case Keymap::Key::SL2:
        report.modifier |= modifers[(int)HID::Mod::LCtrl]; break;
      case Keymap::Key::SL5:
        report.modifier |= modifers[(int)HID::Mod::LAlt]; break;
      case Keymap::Key::LShift:
        report.modifier |= modifers[(int)HID::Mod::LShift]; break;
      case Keymap::Key::SL6:
        report.modifier |= modifers[(int)HID::Mod::LCmd]; break;        
      case Keymap::Key::SR2:
        report.modifier |= modifers[(int)HID::Mod::RAlt]; break;
      case Keymap::Key::RShift:
        report.modifier |= modifers[(int)HID::Mod::RShift]; break;
      case Keymap::Key::SR6:
        report.modifier |= modifers[(int)HID::Mod::RCmd]; break;
      case Keymap::Key::Grave:
        report.modifier |= modifers[(int)HID::Mod::LCtrl]; break;                      
      
      default: {
        auto info = scancodeMap[(int)key];
       
        report.keycode[i++] = scancodes[(int)info.scancode];
        if (info.shift) {
          report.modifier |= 1 << 1;
        }
      }
    }
  }

  if (memcmp(&report, &oldReport, sizeof(report))) {       
    bleHID.keyboardReport(&report);
  }
}
