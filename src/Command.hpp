#pragma once
#include <functional>

#include "ExecutorImpl.hpp"
namespace adas
{

class MoveCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.Move();
    };
};
class TurnLeftCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnLeft();
    };
};
class TurnRightCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
    };
};
class FastCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        poseHandler.Fast();
    };
};

}  // namespace adas