#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose, VehicleType type = VehicleType::Normal) noexcept;
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}, VehicleType type = VehicleType::Normal) noexcept;
    ~ExecutorImpl() noexcept = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query() const noexcept override;
    void SetVehicleType(VehicleType type) noexcept override;

private:
    PoseHandler poseHandler;
};
}  // namespace adas
