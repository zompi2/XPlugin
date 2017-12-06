#include "XPluginImpl.h"
#include "Engine/Engine.h"

void FXPluginImpl::TestXPlugin()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("TextPlugin launched from Windows Platform"));
}