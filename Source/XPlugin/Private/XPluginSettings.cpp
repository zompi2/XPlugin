#include "XPluginSettings.h"

// Just default values
UXPluginSettings::UXPluginSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bEnableXPlugin(false)
	, StringSetting("")
	, IntSetting(0)
{
}
