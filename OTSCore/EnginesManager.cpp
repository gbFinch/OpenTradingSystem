//
// Created by glebb on 12/23/2021.
//

#include <iostream>
#include "AppsEngine/AppsEngine.h"
#include <unordered_map>

OTSCore::AppsEngine appsEngine;

int main() {
    appsEngine.SetManifestsDirectory("./Apps/");
    appsEngine.UpdateApps();
    appsEngine.CreateApp("1", "11");
    appsEngine.CreateApp("2", "12");
    appsEngine.HandleAppAction("11", OTSCore::AppAction::Run);
    appsEngine.HandleAppAction("12", OTSCore::AppAction::Run);
    appsEngine.PrintInfo();
    appsEngine.HandleAppAction("11", OTSCore::AppAction::Delete);
    return 0;
}