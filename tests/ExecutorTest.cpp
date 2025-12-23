#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
//       测试套            测试用例名，清晰地描述了预期行为和测试的条件，更容易理解测试在验证什么
TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when		测试遵循了 Arrange-Act-Assert (AAA) 模式，这是提高可读性和维护性的好习惯
    // then
    const Pose target({0, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    // then
    const Pose target({0, 0, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// M
TEST(ExecutorTest, should_return_x_plus_1_given_command_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("M");

    // then
    const Pose target({1, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_x_minus_1_given_command_M_and_facing_is_W)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    // when
    executor->Execute("M");

    // then
    const Pose target({-1, 0, 'W'});
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_y_plus_1_given_command_M_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("M");

    // then
    const Pose target({0, 1, 'N'});
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_y_minus_1_given_command_M_and_facing_is_S)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

    // when
    executor->Execute("M");

    // then
    const Pose target({0, -1, 'S'});
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
