// (c) 2017 Damian Nowakowski

using UnrealBuildTool;

public class XPlugin : ModuleRules
{
    public XPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        // This parameter enabled the Include-What-You-Use principle in the Engine for this plugin.
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Add basic public and private include paths so the plugin and game will be able to locate include files.
        PublicIncludePaths.Add("XPlugin/Public");
        PrivateIncludePaths.Add("XPlugin/Private");

        // Add Settings to Private Include Path Module Names to safely use Settings module.
        PrivateIncludePathModuleNames.Add("Settings");

        // Add basic dependency modules. You can add some more modules here if you need them.
        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Http" });

        // For every supported platform add the proper directory to private include paths so the plugin will know where to look for platform specific includes.
        // Also it is a good practice to add a Definition that tells us if the plugin is implemented, so we can disable or enable parts of code in the game dependent on if the plugin is on or off.
        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PrivateIncludePaths.Add("XPlugin/Private/IOS");
            Definitions.Add("WITH_XPLUGIN=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateIncludePaths.Add("XPlugin/Private/Android");
            Definitions.Add("WITH_XPLUGIN=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateIncludePaths.Add("XPlugin/Private/Windows");
            Definitions.Add("WITH_XPLUGIN=1");
        }
        else
        {
            Definitions.Add("WITH_XPLUGIN=0");
        }
    }
}