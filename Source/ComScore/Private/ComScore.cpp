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
	virtual void StartupModule()  override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FComScore, ComScore )


#if PLATFORM_IOS

#include "CSComScore.h"

@interface ComScoreDelegate : NSObject
{
}

@end

static ComScoreDelegate *cs;

@implementation ComScoreDelegate

+(void)load
{
    if (!cs)
    {
        cs = [[ComScoreDelegate alloc] init];
    }
}

-(id)init
{
    self = [super init];
    
    if (self)
    {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidFinishLaunching:)
                                                     name:UIApplicationDidFinishLaunchingNotification  object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillEnterForeground:)
                                                     name:UIApplicationWillEnterForegroundNotification  object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidEnterBackground:)
                                                     name:UIApplicationDidEnterBackgroundNotification  object:nil];
    }
    
    return self;
}

-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

-(void)applicationDidFinishLaunching:(NSNotification *)n
{
    NSDictionary *dLaunchOptionsUrl = n.userInfo[@"UIApplicationLaunchOptionsURLKey"];
    
    if (!dLaunchOptionsUrl)
    {
        NSDictionary *d = [NSBundle mainBundle].infoDictionary[@"ComScore"];
        
        if (d)
        {
            NSString *C2ID            = d[@"CustomerC2"];
            NSString *PublisherSecret = d[@"PublisherSecret"];
            NSString *AppName         = d[@"AppName"];

            BOOL SecureHttpLoading = [d[@"SecureHttpLoading"] boolValue];
            
            [CSComScore setAppContext];
            
#if UE_BUILD_DEVELOPMENT
            [CSComScore setDebug:YES];
#else
            [CSComScore setDebug:NO];
#endif
            
            [CSComScore setSecure:SecureHTTPLoading];
            [CSComScore setCustomerC2:C2ID];
            [CSComScore setPublisherSecret:PublisherSecret];
            
            if (AppName.length > 0)
            {
                [CSComScore setAppName:AppName];
            }
            else
            {
                UE_LOG(LogComScore, Log, TEXT("No app name specified bundle ID will be used"));
            }
        }
        else
        {
            UE_LOG(LogComScore, Log, TEXT("No 'ComScore' dictionary key specified in info.plist"));
            UE_LOG(LogComScore, Log, TEXT(" - require CustomerC2 key/string value"));
            UE_LOG(LogComScore, Log, TEXT(" - require PublisherSecret key/string value"));
        }
    }
}

-(void)applicationWillEnterForeground:(NSNotification *)n
{
//    [CSComScore onEnterForeground];
}

-(void)applicationDidEnterBackground:(NSNotification *)n
{
  //  [CSComScore onExitForeground];
}

@end

#endif

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
