#pragma once

class GameSettingLoader : public REX::Singleton<GameSettingLoader>
{
public:
	void ReadConfigs();
	void ApplyGameSettings();

private:
	// members
	std::unordered_map<std::string, std::string> gmstMap{};
};
