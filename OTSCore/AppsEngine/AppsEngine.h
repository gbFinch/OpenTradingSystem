//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_APPSENGINE_H
#define OPENTRADINGSYSTEM_APPSENGINE_H

#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <unordered_map>

#include <OTSLibrary/Apps/App.h>

namespace fs = boost::filesystem;

namespace OTSCore {

    struct AppInfo {
        std::string name;
        fs::path path;
    };

    enum class AppAction {
        Pause,
        Run,
        Delete
    };

    class AppsEngine {
    public:
        void SetManifestsDirectory(const fs::path& path);
        void UpdateAppsList();
        void UpdateAppsCreators();
        void UpdateApps();
        void CreateApp(std::string AppId, std::string AppInstanceId);
        void HandleAppAction(std::string AppInstanceId, AppAction action);
        void HandleModify(std::string AppInstanceId, std::string param, int);
        void DeleteApp(std::string AppInstanceId);

        void PrintInfo();
    private:
        typedef boost::shared_ptr<OTSLibrary::App> (app_api_create_t)();

        fs::path manifestsDir;
        std::unordered_map<std::string, AppInfo> AppsInfo;
        std::unordered_map<std::string, boost::function<app_api_create_t>> AppsCreators;
        std::unordered_map<std::string, boost::shared_ptr<OTSLibrary::App>> AppsInstances;
    };
}


#endif //OPENTRADINGSYSTEM_APPSENGINE_H
