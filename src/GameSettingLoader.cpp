#include "GameSettingLoader.h"

void GameSettingLoader::ReadConfigs()
{
	REX::INFO("{:*^30}", "CONFIGS");
	
	const std::filesystem::directory_entry folder{ "OBSE\\Plugins\\GameSettings" };

	std::error_code ec;
	if (!folder.exists(ec)) {
		REX::WARN("GameSettings folder not found");
		return;
	}

	std::vector<std::string> configs{};

	for (const auto iterator = std::filesystem::directory_iterator(folder); const auto& entry : iterator) {
		if (entry.exists()) {
			if (const auto& path = entry.path(); !path.empty() && (path.extension() == ".ini"sv || path.extension() == ".INI"sv)) {
				configs.push_back(entry.path().string());
			}
		}
	}

	if (configs.empty()) {
		REX::WARN("No .ini files found inside GameSettings folder.");
		return;
	}

	std::ranges::sort(configs);

	for (auto& path : configs) {
		REX::INFO("INI : {}", path);

		CSimpleIniA ini;
		ini.SetUnicode();
		ini.SetMultiKey();

		if (const auto rc = ini.LoadFile(path.c_str()); rc < 0) {
			REX::WARN("\tcouldn't read INI");
			continue;
		}

		if (auto values = ini.GetSection("GameSettings"); values) {
			REX::INFO("\t{} setting(s)", values->size());
			for (auto& [key, entry] : *values) {
				REX::INFO("\t\t{} = {}", key.pItem, entry);
				gmstMap.insert_or_assign(key.pItem, entry);
			}
		}
	}
}

void GameSettingLoader::ApplyGameSettings()
{
	auto gmstCollection = RE::GameSettingCollection::GetSingleton();

	if (!gmstCollection || gmstMap.empty()) {
		return;
	}

	REX::INFO("{:*^30}", "APPLYING GAME SETTINGS");

	for (auto& [settingName, value] : gmstMap) {
		if (auto setting = gmstCollection->GetSetting(settingName.c_str())) {
			switch (setting->GetType()) {
			case RE::Setting::Type::kBool:
				{
					auto oldValue = setting->data.b;
					setting->data.b = string::iequals(value, "true");
					REX::INFO("{} = {} -> {}", settingName, oldValue, setting->data.b);
				}
				break;
			case RE::Setting::Type::kFloat:
				{
					auto oldValue = setting->data.f;
					setting->data.f = string::to_num<float>(value);
					REX::INFO("{} = {} -> {}", settingName, oldValue, setting->data.f);
				}
				break;
			case RE::Setting::Type::kSignedInteger:
				{
					auto oldValue = setting->data.i;
					setting->data.i = string::to_num<std::int32_t>(value);
					REX::INFO("{} = {} -> {}", settingName, oldValue, setting->data.i);
				}
				break;
			case RE::Setting::Type::kColor:
				{
					auto oldValue = setting->data.r;
					setting->data.r = string::to_num<std::uint32_t>(value);
					REX::INFO("{} = {} -> {}", settingName, oldValue, setting->data.r);
				}
				break;
			case RE::Setting::Type::kString:
				{
					auto oldValue = setting->data.s;
					setting->SetString(value.c_str());
					REX::INFO("{} = {} -> {}", settingName, oldValue, setting->data.s);
				}
				break;
			case RE::Setting::Type::kUnsignedInteger:
				{
					auto oldValue = setting->data.u;
					setting->data.u = string::to_num<std::uint32_t>(value);
					REX::INFO("{} = {} -> {}", settingName, oldValue, setting->data.u);
				}
				break;
			default:
				break;
			}
		} else {
			REX::WARN("Couldn't find setting {}", settingName);
		}
	}
}
