#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"
namespace adas
{
TEST(ExecutorReverseTest, should_return_x_minus_1_given_status_is_back_command_is_M_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("BM");
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, should_facing_S_given_status_is_back_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BL");

    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, should_facing_N_given_status_is_back_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BR");

    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, should_return_normal_status_given_execute_B_twice)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("BBM");
    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, should_return_x_minus_2_given_status_is_bf_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFM");

    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, should_return_x_minus_1_and_facing_S_given_status_is_bf_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFL");

    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, should_return_x_minus_1_and_facing_N_given_status_is_bf_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFR");

    // then
    const Pose target{-1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas