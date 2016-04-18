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
    
#if PLATFORM_IOS
    const UComScoreSettings* DefaultSettings = GetDefault<UComScoreSettings>();
    
    NSString* C2ID       = DefaultSettings->C2ID.GetNSString();
    NSString* SecretCode = DefaultSettings->SecretCode.GetNSString();
    NSString* AppName    = DefaultSettings->AppName.GetNSString();
    
    if (!C2ID || !SecretCode || !AppName)
    {
        UE_LOG(LogComScore, Error, TEXT("error with c2id, secret code or app name"));
        return;
    }
    
    [CSComScore setAppContext];
    [CSComScore setCustomerC2:C2ID];
    [CSComScore setPublisherSecret:SecretCode];
    [CSComScore setAppName:AppName];
    
#elif PLATFORM_ANDROID
    
#endif

}


void FComScore::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
