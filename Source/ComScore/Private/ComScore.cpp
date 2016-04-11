//
//  Created by Robert Segal on 2016-04-07.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "ComScorePrivatePCH.h"
#include "ComScoreSettings.h"
#include "ISettingsModule.h"

DEFINE_LOG_CATEGORY(LogComScore);

#define LOCTEXT_NAMESPACE "ComScore"

class FComScore : public IComScore
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FComScore, ComScore )

void FComScore::StartupModule()
{
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "ComScore",
										 LOCTEXT("RuntimeSettingsName", "ComScore"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the ComScore plugin"),
										 GetMutableDefault<UComScoreSettings>()
										 );
	}
}


void FComScore::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
