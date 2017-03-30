//
//  Created by Robert Segal on 2016-04-07.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "ComScoreSettings.h"
#include "ComScorePrivatePCH.h"

UComScoreSettings::UComScoreSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, C2ID("")
, PublisherSecret("")
, AppName("")
, SecureHttpLoading(false)
{
}
