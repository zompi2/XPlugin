#include "XPluginComponent.h"
 
// Definition of static variable so the linker will be satisfied.
UXPluginComponent::FXPlugin_OnReceivedTestMessageDelegate UXPluginComponent::OnReceivedTestMessageDelegate;
 
// Register component. Add the Handler method to the Static Multicast Delegate so when it will be invoked the
// Event in Blueprint will be invoked too.
void UXPluginComponent::OnRegister()
{
	Super::OnRegister();
	OnReceivedTestMessageDelegate.AddUObject(this, &UXPluginComponent::OnReceivedTestMessageDelegate_Handler);
}
 
// Unregister component. Simply cleanup any binding of the Static Multicast Delegate.
void UXPluginComponent::OnUnregister()
{
	OnReceivedTestMessageDelegate.RemoveAll(this);
	Super::OnUnregister();
}
 
// When received the invoke from the Static Multicast Delegate - broadcast the Dynamic Multicast Delegate to Blueprint.
// Make sure the call is made on Game Thread.
void UXPluginComponent::OnReceivedTestMessageDelegate_Handler(const FString& Message)
{
	FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
	{
		OnReceivedTestMessageDynamicDelegate.Broadcast(Message);
	}, TStatId(), NULL, ENamedThreads::GameThread);
}