#pragma once
#include <functional>

#include "ExecutorImpl.hpp"
namespace adas
{

class MoveCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        auto type = poseHandler.GetVehicleType();

        // 根据车辆类型执行不同的移动规则
        switch (type) {
        case VehicleType::SportsCar:
            // 跑车：正常模式下前进2格，快速模式下前进4格
            if (poseHandler.IsFast()) {
                if (poseHandler.IsReverse()) {
                    poseHandler.Backward();
                } else {
                    poseHandler.Forward();
                }
            }
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
            break;
        case VehicleType::Bus:
            // 公交车：正常模式下前进1格，快速模式下前进2格
            if (poseHandler.IsFast()) {
                if (poseHandler.IsReverse()) {
                    poseHandler.Backward();
                    poseHandler.Backward();
                } else {
                    poseHandler.Forward();
                    poseHandler.Forward();
                }
            } else {
                if (poseHandler.IsReverse()) {
                    poseHandler.Backward();
                } else {
                    poseHandler.Forward();
                }
            }
            break;
        case VehicleType::Normal:
        default:
            // 普通车：正常模式下前进1格，快速模式下前进2格
            if (poseHandler.IsFast()) {
                if (poseHandler.IsReverse()) {
                    poseHandler.Backward();
                    poseHandler.Backward();
                } else {
                    poseHandler.Forward();
                    poseHandler.Forward();
                }
            } else {
                if (poseHandler.IsReverse()) {
                    poseHandler.Backward();
                } else {
                    poseHandler.Forward();
                }
            }
            break;
        }
    }
};

class TurnLeftCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        auto type = poseHandler.GetVehicleType();
        auto isReverse = poseHandler.IsReverse();

        switch (type) {
        case VehicleType::SportsCar:
            // 跑车：左转90度，再前进1格
            if (isReverse) {
                poseHandler.TurnRight();  // 倒车状态下左转变成右转
            } else {
                poseHandler.TurnLeft();
            }
            if (isReverse) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
            break;
        case VehicleType::Bus:
            // 公交车：前进1格，再左转90度
            if (isReverse) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
            if (isReverse) {
                poseHandler.TurnRight();  // 倒车状态下左转变成右转
            } else {
                poseHandler.TurnLeft();
            }
            break;
        case VehicleType::Normal:
        default:
            // 普通车：直接左转90度
            if (isReverse) {
                poseHandler.TurnRight();  // 倒车状态下左转变成右转
            } else {
                poseHandler.TurnLeft();
            }
            break;
        }
    }
};

class TurnRightCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        auto type = poseHandler.GetVehicleType();
        auto isReverse = poseHandler.IsReverse();

        switch (type) {
        case VehicleType::SportsCar:
            // 跑车：右转90度，再前进1格
            if (isReverse) {
                poseHandler.TurnLeft();  // 倒车状态下右转变成左转
            } else {
                poseHandler.TurnRight();
            }
            if (isReverse) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
            break;
        case VehicleType::Bus:
            // 公交车：前进1格，再右转90度
            if (isReverse) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
            if (isReverse) {
                poseHandler.TurnLeft();  // 倒车状态下右转变成左转
            } else {
                poseHandler.TurnRight();
            }
            break;
        case VehicleType::Normal:
        default:
            // 普通车：直接右转90度
            if (isReverse) {
                poseHandler.TurnLeft();  // 倒车状态下右转变成左转
            } else {
                poseHandler.TurnRight();
            }
            break;
        }
    }
};
class FastCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    }
};
class ReverseCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    }
};

}  // namespace adas