//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_APP_H
#define OPENTRADINGSYSTEM_APP_H

#include <string>

namespace OTSLibrary
{
    enum class StrategyState    {
        PAUSED,
        RUNNING,
        DELETED
    };

    class Strategy    {
    public:
        virtual std::string GetVersion() = 0;
        virtual std::string GetName() = 0;
        virtual void HandleRun() = 0;
        virtual void HandlePause() = 0;
        virtual void HandleDelete() = 0;

        void SetState(StrategyState state_) {
            state = state_;
        }

        [[nodiscard]]
        StrategyState GetState() const {
            return state;
        }
    private:
        StrategyState state = StrategyState::PAUSED;
    };
}

#define REGISTER_PLUGIN(x) static boost::shared_ptr<Strategy> create() { return boost::shared_ptr<x>(new x()); }\

#endif //OPENTRADINGSYSTEM_APP_H
