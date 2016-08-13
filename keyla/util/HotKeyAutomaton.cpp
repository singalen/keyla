//
// To understand this, look at the `hotkey.png` file in the `diagrams` folder
//

#include "../common.h"
#include "HotKeyAutomaton.h"

void HotKeyAutomaton::postEvent(WPARAM wparam, LPARAM lparam) {

	/* Decode wparam and lparam */

	const KBDLLHOOKSTRUCT * p = reinterpret_cast<const KBDLLHOOKSTRUCT *>(lparam);
	assert(p != 0);	

	unsigned int vk = p->vkCode;
	bool extended = ((p->flags & LLKHF_EXTENDED) != 0);

	/* Get event information */

	bool pressed;
	if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
		pressed = true;
	else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
		pressed = false;
	else {
		assert(false);
		callbackNoop();
		return;
	}

	bool commandKey =
		/* Shift, Ctrl, Alt */
		vk >= VK_LSHIFT && vk <= VK_RMENU ||
		/* Winkeys */
		vk == VK_LWIN || vk == VK_RWIN;

	/* Handle the event */

	Event event = pressed
		? (commandKey ? P_com : P_smb)
		: (commandKey ? R_com : R_smb);

	tstring trace;
	unsigned int tempModifiers;
	switch (m_state) {
		case StateA:
			switch(event) {
				case P_smb:
					trace = L"StateA trigger: ";
					OutputDebugString((trace + getHotKeyWithSymbolKey(vk, extended).text() + L"\n").c_str());
					callbackHotKey(getHotKeyWithSymbolKey(vk, extended));
				break;
				case P_com:
					m_state = StateB;
					updateCommandKeys(true, vk);
					trace = L"StateA progress: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
					callbackProgress(HotKey(0, m_modifiers));
				break;
				case R_smb:
					trace = L"StateA release SMB: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
					break;
				case R_com:
					trace = L"StateA release COM: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
					break;
				default:
					callbackNoop();
			}
		break;
		case StateB:
			switch(event) {
				case P_smb:
					m_state = StateC;
					trace = L"StateB trigger: ";
					OutputDebugString((trace + getHotKeyWithSymbolKey(vk, extended).text() + L"\n").c_str());
					callbackHotKey(getHotKeyWithSymbolKey(vk, extended));
				break;
				case P_com:
					updateCommandKeys(true, vk);
					trace = L"StateB progress: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
					callbackProgress(HotKey(0, m_modifiers));
				break;
				case R_com:
					tempModifiers = m_modifiers;
					updateCommandKeys(false, vk);
					if (m_modifiers) {
						trace = L"StateB trigger -> C: ";
						OutputDebugString((trace + HotKey(0, tempModifiers).text() + L"\n").c_str());
						m_state = StateC;
						callbackHotKey(HotKey(0, tempModifiers));
					}
					else {
						trace = L"StateB trigger -> A: ";
						OutputDebugString((trace + HotKey(0, tempModifiers).text() + L"\n").c_str());
						m_state = StateA;
						callbackHotKey(HotKey(0, tempModifiers));
					}
				case R_smb:
					trace = L"StateB release SMB: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
				break;
				default:
					callbackNoop();
			}
		break;
		case StateC:
			switch(event) {
				case P_smb:
					trace = L"StateC trigger: ";
					OutputDebugString((trace + getHotKeyWithSymbolKey(vk, extended).text() + L"\n").c_str());
					callbackHotKey(getHotKeyWithSymbolKey(vk, extended));
				break;
				case P_com:
					updateCommandKeys(true, vk);
					trace = L"StateC progress: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
					callbackProgress(HotKey(0, m_modifiers));
				break;
				case R_com:
					tempModifiers = m_modifiers;
					trace = L"StateC release: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
					updateCommandKeys(false, vk);
					if (m_modifiers)
						m_state = StateC;
					else
						m_state = StateA;
					callbackNoop();
				break;
				case R_smb:
					trace = L"StateC release SMB: ";
					OutputDebugString((trace + HotKey(0, m_modifiers).text() + L"\n").c_str());
				break;
				default:
					callbackNoop();
			}
		break;
		default:
			assert(false);
			return;
	}
}

void HotKeyAutomaton::updateCommandKeys(bool pressed, unsigned int vk) {
	if (pressed)
		switch(vk) {
			case VK_LSHIFT:
				m_modifiers |= HotKey::LShift;
				break;
			case VK_RSHIFT:
				m_modifiers |= HotKey::RShift;
				break;
			case VK_LCONTROL:
				m_modifiers |= HotKey::LControl;
				break;
			case VK_RCONTROL:
				m_modifiers |= HotKey::RControl;
				break;
			case VK_LMENU:
				m_modifiers |= HotKey::LAlt;
				break;
			case VK_RMENU:
				m_modifiers |= HotKey::RAlt;
				break;
			case VK_LWIN:
				m_modifiers |= HotKey::LWin;
				break;
			case VK_RWIN:
				m_modifiers |= HotKey::RWin;
				break;
			default:
				assert(false);
				return;
		}
	else
		switch(vk) {
			case VK_LSHIFT:
				m_modifiers &= ~HotKey::LShift;
				break;
			case VK_RSHIFT:
				m_modifiers &= ~HotKey::RShift;
				break;
			case VK_LCONTROL:
				m_modifiers &= ~HotKey::LControl;
				break;
			case VK_RCONTROL:
				m_modifiers &= ~HotKey::RControl;
				break;
			case VK_LMENU:
				m_modifiers &= ~HotKey::LAlt;
				break;
			case VK_RMENU:
				m_modifiers &= ~HotKey::RAlt;
				break;
			case VK_LWIN:
				m_modifiers &= ~HotKey::LWin;
				break;
			case VK_RWIN:
				m_modifiers &= ~HotKey::RWin;
				break;
			default:
				assert(false);
				return;
		}

	/* Too slow

	m_modifiers = ((GetKeyState(VK_LSHIFT  ) < 0) ? HotKey::LShift   : 0) |
		          ((GetKeyState(VK_RSHIFT  ) < 0) ? HotKey::RShift   : 0) |
		          ((GetKeyState(VK_LCONTROL) < 0) ? HotKey::LControl : 0) |
		          ((GetKeyState(VK_RCONTROL) < 0) ? HotKey::RControl : 0) |
		          ((GetKeyState(VK_LMENU   ) < 0) ? HotKey::LAlt     : 0) |
		          ((GetKeyState(VK_RMENU   ) < 0) ? HotKey::RAlt     : 0);
	*/
}

HotKey HotKeyAutomaton::getHotKeyWithSymbolKey(unsigned int vk, bool extended) const {
	return HotKey(vk, m_modifiers | (extended ? HotKey::Extended : 0));
}
