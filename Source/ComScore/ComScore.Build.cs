//
//  Created by Robert Segal on 2016-04-07.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class ComScore : ModuleRules
	{
		public ComScore(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					"../../../../Source/Runtime/Core/Public",
					"../../../../Source/Runtime/Launch/Public"
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"ComScore/Private"
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
				
			PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"Settings"
			}
			);

			PublicIncludePathModuleNames.Add("Launch");


			if (Target.Platform == UnrealTargetPlatform.IOS) {

				var LibDir = Path.Combine(ModuleDirectory,"..","..","lib","iOS");
				PrivateIncludePaths.Add(LibDir);

				PublicAdditionalLibraries.Add(Path.Combine(LibDir,"libcomScore.a"));

				PublicFrameworks.AddRange( 
					new string[] 
					{ 
						"SystemConfiguration",
						"Security"
					}
				);
			}
			else if(Target.Platform == UnrealTargetPlatform.Android)
			{
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "ComScore_APL.xml")));
			}
		}
	}
}
