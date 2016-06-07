//
//  Created by Robert Segal on 2016-04-07.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "ComScoreSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UComScoreSettings : public UObject
{
	GENERATED_BODY()
	
    public:
        UComScoreSettings(const FObjectInitializer& ObjectInitializer);
        
        UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="C2ID"))
        FString C2ID;
        
        UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Secret Code"))
        FString SecretCode;
        
        UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="App Name"))
        FString AppName;
    
        UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Secure HTTP Loading"))
        bool SecureHttpLoading;
};
