#!/bin/bash

# ln -sv /Users/Shared/Epic\ Games/UE_4.16 /Users/Shared/UnrealEngine/4.16

UE_VERSION=$1
if [[ $# -eq 0 ]]; then
    UE_VERSION="4.13"
fi

UE_PATH="/Users/Shared/UnrealEngine/"${UE_VERSION}"/Engine/"
UAT_PATH="Build/BatchFiles/"

echo "Building Plugin for UnrealEngine " ${UE_VERSION}

CURR_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

${UE_PATH}${UAT_PATH}RunUAT.sh BuildPlugin -Plugin="${CURR_PATH}/XPlugin.uplugin" -TargetPlatforms=Mac+IOS -Package="${CURR_PATH}/output"

# cp -R "${CURR_PATH}/output/Binaries" "${CURR_PATH}/Plugins/SDKBOX/chartboost/"
