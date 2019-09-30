// Obligatory includes to make it all work
#include "XPlugin.h"
#include "XPluginImpl.h"
#include "ISettingsModule.h"
#include "XPluginSettings.h"
 
// Generated localization namespace that can be used in the future for plugin localzation
#define LOCTEXT_NAMESPACE "FXPluginModule"
 
// Defining the Log category (declaration was in the header)
DEFINE_LOG_CATEGORY(XPluginLog);
 
// Define singletones of the plugin and plugin implementation so the linker will be satisfied
FXPluginModule*					FXPluginModule::Singleton = nullptr;
TSharedPtr<FXPluginImplBase>	FXPluginModule::ModuleImplPtr = nullptr;
 
// This method is launched after creating the instance of the plugin:
void FXPluginModule::StartupModule()
{
#if WITH_EDITOR
	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "XPlugin",
			LOCTEXT("RuntimeSettingsName", "XPlugin"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the XPlugin plugin"),
			GetMutableDefault<UXPluginSettings>()
		);
	}
#endif

	// Remember the address to this instance of the plugin
	Singleton = this;
 
	// If the plugin is compiled against supported platform - create the implementation of this plugin.
	// If the plugin is compiled against not supported platform - create the empty base implementation of this plugin, so it will compile with success.
#if (PLATFORM_IOS || PLATFORM_ANDROID || PLATFORM_WINDOWS)
	ModuleImplPtr = MakeShareable(new FXPluginImpl());
#else
	ModuleImplPtr = MakeShareable(new FXPluginImplBase());
#endif
}
 
// This method is launched when this instance of plugin is shutting down.
void FXPluginModule::ShutdownModule()
{
#if WITH_EDITOR
	// Unregister settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "XPlugin");
	}
#endif // WITH_EDITOR
	// Null point both singletons. The plugin singleton will be soon deleted by the Engine.
	// The implementation singleton is a shared pointer, so it will be deleted when it's safe.
	Singleton = nullptr;
	ModuleImplPtr = nullptr;
}
 
// This method will give you the instance of the implementation object.
TSharedPtr<FXPluginImplBase> FXPluginModule::Get()
{
	// First of all - check if the module has been loaded and force load it if not.
	// On IOS and Android the plugin is created at the game start. On Windows Editor it is not,
	// so it will be created when first used.
	if (Singleton == nullptr)
	{
		check(IsInGameThread());
		FModuleManager::LoadModuleChecked<FXPluginModule>("XPlugin");
	}
 
	// Sanity check if everything was properly created
	check(Singleton != nullptr);
	check(Singleton->ModuleImplPtr.IsValid() == true);
 
	// Return the pointer to the module implementation.
	return Singleton->ModuleImplPtr;
}
 
// We can end the localization namespace here
#undef LOCTEXT_NAMESPACE
	
// Say the engine that this file describes the implementation of the module
IMPLEMENT_MODULE(FXPluginModule, XPlugin)
