// (c) 2017 Damian Nowakowski

#include "XPluginBPLibrary.h"
#include "XPlugin.h"

void UXPluginBPLibrary::TestXPlugin_BP()
{
	FXPluginModule::Get()->TestXPlugin();
}

// The call function actually creates the Proxy - an object of it's own type - and returns it to the Blueprint Context.
UXPluginHttpRequestProxy* UXPluginHttpRequestProxy::XPluginRequestForCats(UObject* WorldContextObject)
{
	UXPluginHttpRequestProxy* Proxy = NewObject<UXPluginHttpRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}
 
// The Proxy is Activeted shortly after it's creation. We can launch the Http request here.
void UXPluginHttpRequestProxy::Activate()
{
	TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UXPluginHttpRequestProxy::OnHttpRequestComplete);
	HttpRequest->SetURL(TEXT("http://thecatapi.com/api/images/get?format=src&type=png"));
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->ProcessRequest();
}
 
// Here we've received the Http response. We can launch the OnSuccess and OnFailure delegate dependent on if the request finished with success.
void UXPluginHttpRequestProxy::OnHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded == true)
	{
		OnSuccess.Broadcast(HttpResponse->GetResponseCode());
	}
	else
	{
		OnFailure.Broadcast(HttpResponse->GetResponseCode());
	}
}