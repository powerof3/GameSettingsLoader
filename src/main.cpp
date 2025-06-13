#include "GameSettingLoader.h"

void MessageHandler(OBSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case OBSE::MessagingInterface::kPostLoad:
		GameSettingLoader::GetSingleton()->ReadConfigs();
		break;
	case OBSE::MessagingInterface::kDataLoaded:
		GameSettingLoader::GetSingleton()->ApplyGameSettings();
		break;
	default:
		break;
	}
}

OBSE_EXPORT constinit auto OBSEPlugin_Version = []() noexcept {
	OBSE::PluginVersionData v{};
	v.PluginVersion({ Version::MAJOR, Version::MINOR, Version::PATCH, 0 });
	v.PluginName("GameSettingLoader");
	v.AuthorName("powerofthree");
	v.UsesAddressLibrary(true);
	v.UsesSigScanning(false);
	v.IsLayoutDependent(true);
	v.HasNoStructUse(false);
	v.CompatibleVersions({ OBSE::RUNTIME_LATEST });
	return v;
}();

OBSE_PLUGIN_LOAD(const OBSE::LoadInterface* a_obse)
{
	OBSE::Init(a_obse, { .logName = Version::PROJECT.data(), .logPattern = "[%T.%e] [%L] %v", .trampoline = true });
	OBSE::GetMessagingInterface()->RegisterListener(MessageHandler);
	return true;
}
