//
//  Created by Robert Segal on 2016-04-07.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "ComScorePrivatePCH.h"

#if PLATFORM_IOS
#include "CSComScore.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

#if PLATFORM_IOS

@interface ComScoreFunctionsDelegate : NSObject
@end


@implementation ComScoreFunctionsDelegate

-(void)applicationDidFinishLaunching:(NSNotification *)Notification
{
    const UComScoreSettings* DefaultSettings = GetDefault<UComScoreSettings>();
    
    NSString* c2id       = DefaultSettings->C2ID.GetNSString();
    NSString* secretCode = DefaultSettings->SecretCode.GetNSString();
    NSString* appName    = DefaultSettings->AppName.GetNSString();
    
    if (c2id && secretCode && appName)
    {
        [CSComScore setAppContext];
        
        [CSComScore setCustomerC2:c2id];
        [CSComScore setPublisherSecret:secretCode];
        [CSComScore setAppName:appName];
    }
    else
    {
        UE_LOG(LogComScore, Log, TEXT("Error with c2id, secret code or app name"));
    }
}

@end

#elif PLATFORM_ANDROID

#endif

