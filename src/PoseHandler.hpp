#pragma once
#include "Executor.hpp"
namespace adas
{
class PoseHandler final
{
public:
    PoseHandler(const Pose& pose, VehicleType type = VehicleType::Normal) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    void Forward(void) noexcept;
    void Backward(void) noexcept;
    Pose Query(void) const noexcept;
    void SetVehicleType(VehicleType type) noexcept;
    VehicleType GetVehicleType(void) const noexcept;

private:
    Pose pose;
    bool fast{false};
    bool reverse{false};
    VehicleType vehicleType{VehicleType::Normal};
};
}  // namespace adas