#include "ExecutorImpl.hpp"

#include <algorithm>
#include <memory>
#include <unordered_map>

#include "CmderFactory.hpp"
#include "Command.hpp"
#include "Singleton.hpp"

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose, VehicleType type) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, type);
}

ExecutorImpl::ExecutorImpl(const Pose& pose, VehicleType type) noexcept : poseHandler(pose, type)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    CmderFactory cf;
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);
    std::for_each(cmders.begin(), cmders.end(), [this](const Cmder& cmder) noexcept { cmder(poseHandler); });
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}

void ExecutorImpl::SetVehicleType(VehicleType type) noexcept
{
    poseHandler.SetVehicleType(type);
}

}  // namespace adas
