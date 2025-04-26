#include "GameSettingLoader.h"

struct Hook_DataLoaded
{
	static void MainLoopFunc(std::uintptr_t a_ptr)
	{
		MainLoopFuncHook(a_ptr);

		static std::once_flag once;
		std::call_once(once, [&]() {
			GameSettingLoader::GetSingleton()->ApplyGameSettings();
		});
	}

	static inline REL::Hook MainLoopFuncHook{ REL::Offset(0x65FB250), 0x12CB, MainLoopFunc };
};

void MessageHandler(OBSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case OBSE::MessagingInterface::kPostLoad:
		GameSettingLoader::GetSingleton()->ReadConfigs();
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
	v.UsesAddressLibrary(false);
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
