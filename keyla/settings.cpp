#include "common.h"
#include "layoutList.h"
#include "res/resource.h"
#include "settings.h"

namespace settings {

	SettingsStruct::SettingsStruct() : mainIcon(MAKEINTRESOURCE(IDI_MAINICON)) {
		// Other members get initialized in load()
	}

	SettingsStruct Settings;

	void load() {

		HKEY hkey;
		if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("software\\keyla"), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0)) {
			assert(false);
			return;
		}

		Settings.mainHotKey.loadFromRegistry(hkey, TEXT("mainHotKey"));

		DWORD data;
		DWORD dataSz = sizeof(data);
		DWORD type;

		LPCTSTR value;
		LONG ret;

		value = TEXT("skipSystemHotKey");
		ret = RegQueryValueEx(hkey, value, 0, &type, reinterpret_cast<BYTE *>(&data), &dataSz);
		if (ret != ERROR_SUCCESS || type != REG_DWORD || dataSz != sizeof(DWORD)) {
			data = Settings.skipSystemHotKey;
			RegSetValueEx(hkey, value, 0, REG_DWORD, reinterpret_cast<const BYTE *>(&data), dataSz);
		} else { 
			Settings.skipSystemHotKey = (data != 0);
		}

		value = TEXT("globalLayout");
		ret = RegQueryValueEx(hkey, value, 0, &type, reinterpret_cast<BYTE *>(&data), &dataSz);
		if (ret != ERROR_SUCCESS || type != REG_DWORD || dataSz != sizeof(DWORD)) {
			data = Settings.globalLayout;
			RegSetValueEx(hkey, value, 0, REG_DWORD, reinterpret_cast<const BYTE *>(&data), dataSz);
		} else { 
			Settings.globalLayout = (data != 0);
		}

		size_t sz = layoutList::LayoutList.size();
		Settings.layoutSettings.resize(sz);
		for (size_t i = 0; i < sz; ++i) {
			tstring subkey = TEXT("layouts\\") + layoutList::layoutLangId( layoutList::LayoutList[i] ) + TEXT("\\");
			Settings.layoutSettings[i].hotKey.loadFromRegistry(hkey, subkey + TEXT("hotKey"));

			ret = RegQueryValueEx(hkey, (subkey + TEXT("useWhenSwitchingCyclically")).c_str(), 0, &type, reinterpret_cast<BYTE *>(&data), &dataSz);
			if (ret != ERROR_SUCCESS || type != REG_DWORD || dataSz != sizeof(DWORD)) {
				data = Settings.layoutSettings[i].useWhenSwitchingCyclically;
				RegSetValueEx(hkey, value, 0, REG_DWORD, reinterpret_cast<const BYTE *>(&data), dataSz);
			} else { 
				Settings.layoutSettings[i].useWhenSwitchingCyclically = (data != 0);
			}
		}

		RegCloseKey(hkey);
	}

	void save() {

		HKEY hkey;
		if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("software\\keyla"), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0)) {
			assert(false);
			return;
		}

		DWORD data;
		LPCTSTR value;

		Settings.mainHotKey.saveToRegistry(hkey, TEXT("mainHotKey"));

		value = TEXT("skipSystemHotKey");
		data = Settings.skipSystemHotKey;
		RegSetValueEx(hkey, value, 0, REG_DWORD, reinterpret_cast<const BYTE *>(&data), sizeof(data));

		value = TEXT("globalLayout");
		data = Settings.globalLayout;
		RegSetValueEx(hkey, value, 0, REG_DWORD, reinterpret_cast<const BYTE *>(&data), sizeof(data));

		size_t sz = layoutList::LayoutList.size();
		Settings.layoutSettings.resize(sz);
		for (size_t i = 0; i < sz; ++i) {
			tstring subkey = TEXT("layouts\\") + layoutList::layoutLangId( layoutList::LayoutList[i] ) + TEXT("\\");
			Settings.layoutSettings[i].hotKey.saveToRegistry(hkey, subkey + TEXT("hotKey"));

			data = Settings.layoutSettings[i].useWhenSwitchingCyclically;
			RegSetValueEx(hkey, (subkey + TEXT("useWhenSwitchingCyclically")).c_str(), 0, REG_DWORD, reinterpret_cast<BYTE *>(&data), sizeof(data));
		}

		RegCloseKey(hkey);
	}

}