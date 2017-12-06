#pragma once

#include "XPluginImplBase.h"

class XPLUGIN_API FXPluginImpl : public FXPluginImplBase
{
public:
	~FXPluginImpl() override {}
	void TestXPlugin() override;
};