#include "PoseHandler.hpp"
namespace adas
{
PoseHandler::PoseHandler(const Pose& pose, VehicleType type) noexcept : pose(pose), vehicleType(type)
{
}

void PoseHandler::SetVehicleType(VehicleType type) noexcept
{
    vehicleType = type;
}

VehicleType PoseHandler::GetVehicleType() const noexcept
{
    return vehicleType;
}

void PoseHandler::Move() noexcept
{
    if (reverse) {
        Backward();
    } else {
        Forward();
    }
}
void PoseHandler::TurnLeft() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    }
}
void PoseHandler::TurnRight() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'E';
    }
}
Pose PoseHandler::Query() const noexcept
{
    return pose;
}
void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}
void PoseHandler::Fast() noexcept
{
    fast = !fast;
}
bool PoseHandler::IsFast() const noexcept
{
    return fast;
}
void PoseHandler::Forward(void) noexcept
{
    auto moveOneStep = [this]() {
        if (pose.heading == 'E')
            ++pose.x;
        else if (pose.heading == 'W')
            --pose.x;
        else if (pose.heading == 'N')
            ++pose.y;
        else if (pose.heading == 'S')
            --pose.y;
    };

    switch (vehicleType) {
    case VehicleType::SportsCar:
        // 跑车：根据状态执行不同的移动
        if (fast) {
            moveOneStep();
            moveOneStep();
            moveOneStep();
            moveOneStep();  // 快速模式下前进4格
        } else {
            moveOneStep();
            moveOneStep();  // 普通模式下前进2格
        }
        break;
    case VehicleType::Bus:
        // 公交车：每次前进1格
        moveOneStep();
        break;
    case VehicleType::Normal:
    default:
        // 普通车：每次前进1格
        moveOneStep();
        break;
    }
}

void PoseHandler::Backward(void) noexcept
{
    auto moveOneStep = [this]() {
        if (pose.heading == 'E')
            --pose.x;
        else if (pose.heading == 'W')
            ++pose.x;
        else if (pose.heading == 'N')
            --pose.y;
        else if (pose.heading == 'S')
            ++pose.y;
    };

    switch (vehicleType) {
    case VehicleType::SportsCar:
        // 跑车：根据状态执行不同的移动
        if (fast) {
            moveOneStep();
            moveOneStep();
            moveOneStep();
            moveOneStep();  // 快速模式下后退4格
        } else {
            moveOneStep();
            moveOneStep();  // 普通模式下后退2格
        }
        break;
    case VehicleType::Bus:
        // 公交车：每次后退1格
        moveOneStep();
        break;
    case VehicleType::Normal:
    default:
        // 普通车：每次后退1格
        moveOneStep();
        break;
    }
}
}  // namespace adas