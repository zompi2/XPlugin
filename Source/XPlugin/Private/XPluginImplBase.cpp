#include "XPluginImplBase.h"
#include "Engine/Engine.h"

void FXPluginImplBase::TestXPlugin()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("TextPlugin launched from Generic Platform"));
}