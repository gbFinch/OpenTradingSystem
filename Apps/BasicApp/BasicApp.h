//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_BASICAPP_H
#define OPENTRADINGSYSTEM_BASICAPP_H

#include <OTSLibrary/Apps/App.h>
#include <git.h>
#include <boost/dll/alias.hpp>
#include <memory>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <string>

#include <fmt/format.h>

namespace OTSApps
{
    class BasicApp : public OTSLibrary::App {
    public:
        void HandleRun() override {
            fmt::print("Plugin {} of version [{}] is {}\n", GetName(), GetVersion(), "running");
            SetState(OTSLibrary::AppState::RUNNING);
        };
        void HandlePause() override {
            fmt::print("Plugin {} of version [{}] is {}\n", GetName(), GetVersion(), "paused");
            SetState(OTSLibrary::AppState::PAUSED);
        };
        void HandleDelete() override {
            fmt::print("Plugin {} of version [{}] is {}\n", GetName(), GetVersion(), "deleted");
            SetState(OTSLibrary::AppState::DELETED);
        };

        REGISTER_PLUGIN(BasicApp)
        REGISTER_VERSION()
    };
}

BOOST_DLL_ALIAS(OTSApps::BasicApp::create, create_app)


#endif //OPENTRADINGSYSTEM_BASICAPP_H
