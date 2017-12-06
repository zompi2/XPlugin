#pragma once

// These are basic includes needed by the module
#include "CoreMinimal.h"
#include "ModuleManager.h"

// Include the ImplBase so it will be easy accessible from the game by simply including this one header only.
#include "XPluginImplBase.h"

// It is a good practice to declare a Log category for every plugin
DECLARE_LOG_CATEGORY_EXTERN(XPluginLog, Log, All);

// Implementation of the Plugin (must inherit from IModuleInterface)
class XPLUGIN_API FXPluginModule : public IModuleInterface
{
public:

	// IModuleInterface implementation
	// These are implementations of methods which runs when the module (plugin) starts up and shuts down
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// This is a handy method for getting instance of the plugin implementation object from any place in code.
	static TSharedPtr<FXPluginImplBase> Get();

private:

	// Pointer to the only instance of the plugin
	static FXPluginModule* Singleton;

	// Pointer to the platform specific implementation of the plugin
	static TSharedPtr<FXPluginImplBase> ModuleImplPtr;
};