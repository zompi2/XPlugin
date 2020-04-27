// (c) 2017 Damian Nowakowski

#pragma once
 
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "XPluginComponent.generated.h"
 
// We create an Actor Component that can be spawned inside Blueprints
UCLASS(meta = (BlueprintSpawnableComponent), DisplayName = "XPlugin")
class XPLUGIN_API UXPluginComponent : public UActorComponent
{
	GENERATED_BODY()
 
public:
 
	// These are begin and end methods from UActorComponent. We must override them.
	void OnRegister() override;
	void OnUnregister() override;
 
	// This is declaration of "Static Multicast Delegate".
	// Plugin can broadcast it to other parts of code that has been binded to it.
	DECLARE_MULTICAST_DELEGATE_OneParam(FXPlugin_OnReceivedTestMessageDelegate, const FString&);
	static FXPlugin_OnReceivedTestMessageDelegate OnReceivedTestMessageDelegate;
 
	// This is declaration of "Dynamic Multicast Delegate". 
	// This is the delegate that will be invoking Blueprint Event.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXPlugin_OnReceivedTestMessageDynamicDelegate, const FString&, Message);
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On received XPlugin Test Message"))
	FXPlugin_OnReceivedTestMessageDynamicDelegate OnReceivedTestMessageDynamicDelegate;
 
private:
 
	// This is helper method for launching the Dynamic Multicast Delegate when the Static Multicast Delegate is invoked.
	void OnReceivedTestMessageDelegate_Handler(const FString& Message);
};