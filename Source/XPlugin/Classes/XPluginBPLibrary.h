// (c) 2017 Damian Nowakowski

#pragma once
 
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "XPluginBPLibrary.generated.h"
 
UCLASS()
class XPLUGIN_API UXPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "XPlugin", DisplayName = "TestXPlugin")
	static void TestXPlugin_BP();
};

// Declaration of the "Dynamic Multicast Delegate Type". It accepts the Http Status Code as a parameter.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishedRequestHttp, int32, StatusCode);
 
UCLASS()
class XPLUGIN_API UXPluginHttpRequestProxy : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
 
	// This is Blueprint Assignable Delegate which will run when the Async Task will finish with success.
	UPROPERTY(BlueprintAssignable)
	FOnFinishedRequestHttp OnSuccess;
 
	// This is Blueprint Assignable Delegate which will run when the Async Task will finish with failure.
	UPROPERTY(BlueprintAssignable)
	FOnFinishedRequestHttp OnFailure;
 
	// This is the Async Blueprint Function for calling the request. It receives automatically the World Context from the Engine when it is called.
	UFUNCTION(BlueprintCallable, Category = "XPlugin", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "XPlugin Request For Cats"))
	static UXPluginHttpRequestProxy* XPluginRequestForCats(UObject* WorldContextObject);
 
	// The UBlueprintAsyncActionBase function to override - runs when the request becomes Active.
	virtual void Activate() override;
 
private:
 
	// The function which will run when the Http request finishes.
	void OnHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	
	// The pointer to the WorldContext. We simply need it.
	UObject* WorldContextObject;
};