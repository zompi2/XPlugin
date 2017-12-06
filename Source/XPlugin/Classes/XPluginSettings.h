#pragma once

#include "XPluginSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class XPLUGIN_API UXPluginSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UXPluginSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, Category = "Basic", meta = (DisplayName = "Enable XPlugin"))
	bool bEnableXPlugin;

	UPROPERTY(Config, EditAnywhere, Category = "Complex", meta = (EditCondition = bEnableXPlugin, DisplayName = "XPlugin Some String Setting"))
	FString StringSetting;

	UPROPERTY(Config, EditAnywhere, Category = "Complex", meta = (EditCondition = bEnableXPlugin, DisplayName = "XPlugin Some int Setting"))
	int32 IntSetting;
};
