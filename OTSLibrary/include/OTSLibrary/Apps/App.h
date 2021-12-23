//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_APP_H
#define OPENTRADINGSYSTEM_APP_H

#include <string>

namespace OTSLibrary
{
    enum class AppState    {
        PAUSED,
        RUNNING,
        DELETED
    };

    class App    {
    public:
        virtual std::string GetVersion() { return { "Unknown version" }; };
        virtual std::string GetName() = 0;
        virtual void HandleRun() = 0;
        virtual void HandlePause() = 0;
        virtual void HandleDelete() = 0;

        void SetState(AppState state_) {
            state = state_;
        }

        [[nodiscard]]
        AppState GetState() const {
            return state;
        }
    private:
        AppState state = AppState::PAUSED;
    };
}

#define REGISTER_PLUGIN(x) static boost::shared_ptr<App> create() { return boost::shared_ptr<x>(new x()); }\
                        std::string GetName() override { return #x; }

#endif //OPENTRADINGSYSTEM_APP_H
