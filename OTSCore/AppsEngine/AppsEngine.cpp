//
// Created by glebb on 12/23/2021.
//

#include "AppsEngine.h"

#include <pugixml.hpp>
#include <fmt/format.h>
#include <boost/dll/import.hpp>
#include <iostream> //*todo: delete

namespace dll = boost::dll;

void OTSCore::AppsEngine::SetManifestsDirectory(const fs::path &path) {
    std::cout << "Manifest relative dir is " << path.string() << std::endl;
    manifestsDir = path;
}

void OTSCore::AppsEngine::UpdateAppsList() {
    if (manifestsDir.empty())
    {
        std::cout<<"Manifest dir is empty" << std::endl;
        return;
    }


    if (!fs::is_directory(manifestsDir))
    {
        std::cout<<"Manifest dir is not a directory" << std::endl;
        return;
    }

    AppsInfo.clear();

    for (fs::directory_entry& entry : fs::directory_iterator(manifestsDir))
    {
        if (entry.path().extension() != ".xml")
            continue;
        std::cout << "Found App = " << entry.path().string() << std::endl;
        pugi::xml_document doc;

        pugi::xml_parse_result result = doc.load_file(entry.path().string().c_str());
        if (result)
        {
            for (pugi::xml_node tool = doc.first_child(); tool; tool = tool.next_sibling())
            {
                if (strcmp(tool.name(), "App") != 0) continue;

                std::string AppId, AppName, AppPath;

                for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
                {
                    std::string attrName = attr.name();
                    if (attrName == "id") AppId = attr.value();
                    if (attrName == "name") AppName = attr.value();
                    if (attrName == "path") AppPath = attr.value();
                }
                fmt::print("App id = {}, App name = {}, App path = {}\n", AppId, AppName, AppPath);
                if (AppId.empty() || AppName.empty() || AppPath.empty()) continue;

                AppsInfo[AppId] = AppInfo{ AppName, manifestsDir / AppPath };
            }
        }
    }
}

void OTSCore::AppsEngine::UpdateAppsCreators() {
    if (AppsInfo.empty()) return;

    for (const auto& [id, AppInfo] : AppsInfo)
    {
        try
        {
            std::cout << AppInfo.path.string() << std::endl;
            std::cout << AppInfo.path.root_path().string() << std::endl;
            AppsCreators[id] = dll::import_alias<app_api_create_t>(
                    AppInfo.path,
                    "create_app",
                    dll::load_mode::append_decorations
            );
        }
        catch (const boost::system::system_error &err) {
            std::cout << "couldn't create" << err.what() << std::endl;
        }
    }
}

void OTSCore::AppsEngine::DeleteApp(std::string AppInstanceId) {
    if (AppsInstances.count(AppInstanceId) != 0) return;
    AppsInstances.erase(AppInstanceId);
}

void OTSCore::AppsEngine::UpdateApps() {
    UpdateAppsList();
    UpdateAppsCreators();
}

void OTSCore::AppsEngine::PrintInfo() {
    for (const auto& [instanceId, instance] : AppsInstances) {
        fmt::print("App {} of name {} and version {} with state {}\n",
                   instanceId,
                   instance->GetName(),
                   instance->GetVersion(),
                   instance->GetState()
        );
    }
}

void OTSCore::AppsEngine::HandleAppAction(std::string AppInstanceId, AppAction action) {
    auto AppIt = AppsInstances.find(AppInstanceId);
    if (AppIt == AppsInstances.end()) return;

    auto& AppPtr = AppIt->second;
    if (!AppPtr) return;

    switch (action) {
        case AppAction::Run : AppPtr->HandleRun(); break;
        case AppAction::Delete : AppPtr->HandleDelete(); break;
        case AppAction::Pause : AppPtr->HandlePause(); break;
    }
}

void OTSCore::AppsEngine::HandleModify(std::string AppInstanceId, std::string param, int) {

}

void OTSCore::AppsEngine::CreateApp(std::string AppId, std::string AppInstanceId) {
    if (AppsCreators.count(AppId) == 0) return;
    if (AppsInstances.count(AppInstanceId) != 0) return;

    auto& AppInstance = AppsInstances[AppInstanceId];
    AppInstance = AppsCreators[AppId]();

    if (!AppInstance) {
        fmt::print("App {} of type {} was not created\n", AppInstanceId, AppId);
        return;
    }

    fmt::print("App {} of type {} of name {} and version {} was created\n",
               AppInstanceId,
               AppId,
               AppInstance->GetName(),
               AppInstance->GetVersion()
    );
}