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
    }
};
class TurnLeftCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnRight();  // 倒车状态下左转变成右转
        } else {
            poseHandler.TurnLeft();
        }
    }
};
class TurnRightCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnLeft();
        } else {
            poseHandler.TurnRight();
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