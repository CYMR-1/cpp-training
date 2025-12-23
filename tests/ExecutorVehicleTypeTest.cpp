#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// 测试普通车的默认行为
TEST(ExecutorVehicleTypeTest, should_use_normal_vehicle_as_default)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    // when
    executor->Execute("M");
    // then
    const Pose target({1, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车的移动规则
TEST(ExecutorVehicleTypeTest, sports_car_should_move_2_steps_given_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("M");
    // then
    const Pose target({2, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, sports_car_should_turn_left_and_move_1_step_given_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("L");
    // then
    const Pose target({0, 1, 'N'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, sports_car_should_turn_right_and_move_1_step_given_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("R");
    // then
    const Pose target({0, -1, 'S'});
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车的移动规则
TEST(ExecutorVehicleTypeTest, bus_should_move_1_step_given_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("M");
    // then
    const Pose target({1, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, bus_should_move_1_step_and_turn_left_given_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("L");
    // then
    const Pose target({1, 0, 'N'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, bus_should_move_1_step_and_turn_right_given_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("R");
    // then
    const Pose target({1, 0, 'S'});
    ASSERT_EQ(target, executor->Query());
}

// 测试车辆类型切换功能
TEST(ExecutorVehicleTypeTest, should_switch_to_sports_car_from_normal)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Normal));
    // when
    executor->Execute("M");  // 普通车移动1格
    executor->SetVehicleType(VehicleType::SportsCar);
    executor->Execute("M");  // 跑车移动2格
    // then
    const Pose target({3, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, should_switch_to_bus_from_sports_car)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("M");  // 跑车移动2格
    executor->SetVehicleType(VehicleType::Bus);
    executor->Execute("M");  // 公交车移动1格
    // then
    const Pose target({3, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, should_switch_to_normal_from_bus)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("M");  // 公交车移动1格
    executor->SetVehicleType(VehicleType::Normal);
    executor->Execute("M");  // 普通车移动1格
    // then
    const Pose target({2, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试车辆类型切换后的转向行为
TEST(ExecutorVehicleTypeTest, should_use_different_turn_rules_when_switching_vehicle_types)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when 使用普通车转向
    executor->SetVehicleType(VehicleType::Normal);
    executor->Execute("L");
    const Pose normal_turn_result = executor->Query();

    // 重置位置
    executor.reset(Executor::NewExecutor({0, 0, 'E'}));

    // when 使用跑车转向
    executor->SetVehicleType(VehicleType::SportsCar);
    executor->Execute("L");
    const Pose sports_car_turn_result = executor->Query();

    // 重置位置
    executor.reset(Executor::NewExecutor({0, 0, 'E'}));

    // when 使用公交车转向
    executor->SetVehicleType(VehicleType::Bus);
    executor->Execute("L");
    const Pose bus_turn_result = executor->Query();

    // then 验证不同车辆类型的转向行为不同
    ASSERT_EQ(Pose({0, 0, 'N'}), normal_turn_result);      // 普通车：只转向
    ASSERT_EQ(Pose({0, 1, 'N'}), sports_car_turn_result);  // 跑车：转向+前进
    ASSERT_EQ(Pose({1, 0, 'N'}), bus_turn_result);         // 公交车：前进+转向
}

// 测试跑车在快速模式下的移动
TEST(ExecutorVehicleTypeTest, sports_car_should_move_4_steps_given_fast_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("FM");
    // then
    const Pose target({4, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在快速模式下的左转命令
TEST(ExecutorVehicleTypeTest, sports_car_should_turn_left_and_move_2_steps_given_fast_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("FL");
    // then
    const Pose target({0, 2, 'N'});  // 快速模式下：左转90度(向东→向北)，前进2步
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在快速模式下的右转命令
TEST(ExecutorVehicleTypeTest, sports_car_should_turn_right_and_move_2_steps_given_fast_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("FR");
    // then
    const Pose target({0, -2, 'S'});  // 快速模式下：右转90度(向东→向南)，前进2步
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在快速模式下的移动
TEST(ExecutorVehicleTypeTest, bus_should_move_2_steps_given_fast_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("FM");
    // then
    const Pose target({2, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在快速模式下的左转命令
TEST(ExecutorVehicleTypeTest, bus_should_move_2_steps_and_turn_left_given_fast_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("FL");
    // then
    const Pose target({2, 0, 'N'});  // 快速模式下：前进2步，左转90度(向东→向北)
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在快速模式下的右转命令
TEST(ExecutorVehicleTypeTest, bus_should_move_2_steps_and_turn_right_given_fast_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("FR");
    // then
    const Pose target({2, 0, 'S'});  // 快速模式下：前进2步，右转90度(向东→向南)
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在反向模式下的移动
TEST(ExecutorVehicleTypeTest, sports_car_should_move_backward_2_steps_given_reverse_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("BM");
    // then
    const Pose target({0, 0, 'E'});  // 反向移动2步
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在反向模式下的左转命令
TEST(ExecutorVehicleTypeTest, sports_car_should_turn_right_and_move_backward_1_step_given_reverse_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("BL");
    // then
    const Pose target({0, -1, 'S'});  // 反向模式下L命令：右转90度(向东→向南)，后退1步
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在反向模式下的右转命令
TEST(ExecutorVehicleTypeTest, sports_car_should_turn_left_and_move_backward_1_step_given_reverse_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("BR");
    // then
    const Pose target({0, 1, 'N'});  // 反向模式下R命令：左转90度(向东→向北)，后退1步
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在反向模式下的移动
TEST(ExecutorVehicleTypeTest, bus_should_move_backward_1_step_given_reverse_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({1, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("BM");
    // then
    const Pose target({0, 0, 'E'});  // 反向移动1步
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在反向模式下的左转命令
TEST(ExecutorVehicleTypeTest, bus_should_move_backward_1_step_and_turn_right_given_reverse_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("BL");
    // then
    const Pose target({-1, 0, 'S'});  // 反向模式下L命令：后退1步，右转90度(向东→向南)
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在反向模式下的右转命令
TEST(ExecutorVehicleTypeTest, bus_should_move_backward_1_step_and_turn_left_given_reverse_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("BR");
    // then
    const Pose target({-1, 0, 'N'});  // 反向模式下R命令：后退1步，左转90度(向东→向北)
    ASSERT_EQ(target, executor->Query());
}

// 测试普通车在反向模式下的移动（作为参考）
TEST(ExecutorVehicleTypeTest, normal_vehicle_should_move_backward_1_step_given_reverse_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({1, 0, 'E'}, VehicleType::Normal));
    // when
    executor->Execute("BM");
    // then
    const Pose target({0, 0, 'E'});  // 反向移动1步
    ASSERT_EQ(target, executor->Query());
}

// 测试普通车在反向模式下的左转命令（作为参考）
TEST(ExecutorVehicleTypeTest, normal_vehicle_should_turn_right_given_reverse_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Normal));
    // when
    executor->Execute("BL");
    // then
    const Pose target({0, 0, 'S'});  // 反向模式下L命令：右转90度(向东→向南)，不移动
    ASSERT_EQ(target, executor->Query());
}

// 测试普通车在反向模式下的右转命令（作为参考）
TEST(ExecutorVehicleTypeTest, normal_vehicle_should_turn_left_given_reverse_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Normal));
    // when
    executor->Execute("BR");
    // then
    const Pose target({0, 0, 'N'});  // 反向模式下R命令：左转90度(向东→向北)，不移动
    ASSERT_EQ(target, executor->Query());
}

// 测试快速+反向模式下不同车辆类型的移动
TEST(ExecutorVehicleTypeTest, sports_car_should_move_backward_4_steps_given_fast_reverse_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({4, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("BFM");
    // then
    const Pose target({0, 0, 'E'});  // 快速+反向模式下，跑车移动4步
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在快速+反向模式下的左转命令
TEST(ExecutorVehicleTypeTest, sports_car_should_turn_right_and_move_backward_2_steps_given_fast_reverse_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("BFL");
    // then
    const Pose target({0, 2, 'S'});  // 快速+反向模式下L命令：右转90度(向东→向南)，向后移动2步
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车在快速+反向模式下的右转命令
TEST(ExecutorVehicleTypeTest, sports_car_should_turn_left_and_move_backward_2_steps_given_fast_reverse_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    // when
    executor->Execute("BFR");
    // then
    const Pose target({0, -2, 'N'});  // 快速+反向模式下R命令：左转90度(向东→向北)，向后移动2步
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, bus_should_move_backward_2_steps_given_fast_reverse_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("BFM");
    // then
    const Pose target({0, 0, 'E'});  // 快速+反向模式下，公交车移动2步
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在快速+反向模式下的左转命令
TEST(ExecutorVehicleTypeTest, bus_should_move_backward_2_steps_and_turn_right_given_fast_reverse_and_command_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("BFL");
    // then
    const Pose target({0, 0, 'S'});  // 快速+反向模式下L命令：后退2步，右转90度(向东→向南)
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车在快速+反向模式下的右转命令
TEST(ExecutorVehicleTypeTest, bus_should_move_backward_2_steps_and_turn_left_given_fast_reverse_and_command_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 0, 'E'}, VehicleType::Bus));
    // when
    executor->Execute("BFR");
    // then
    const Pose target({0, 0, 'N'});  // 快速+反向模式下R命令：后退2步，左转90度(向东→向北)
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorVehicleTypeTest, normal_vehicle_should_move_backward_1_step_given_fast_reverse_and_command_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({1, 0, 'E'}, VehicleType::Normal));
    // when
    executor->Execute("BFM");
    // then
    const Pose target({0, 0, 'E'});  // 快速+反向模式下，普通车移动1步
    ASSERT_EQ(target, executor->Query());
}

// 测试车辆类型切换后在反向模式下的行为
TEST(ExecutorVehicleTypeTest, should_use_correct_reverse_behavior_after_switching_vehicle_type)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({4, 0, 'E'}, VehicleType::Normal));

    // when 使用普通车反向移动1步
    executor->Execute("BM");

    // when 切换到跑车
    executor->SetVehicleType(VehicleType::SportsCar);
    executor->Execute("BM");

    // when 切换到公交车
    executor->SetVehicleType(VehicleType::Bus);
    executor->Execute("BM");

    // then 验证总移动距离：普通车(-1) + 跑车(-2) + 公交车(-1) = -4步
    const Pose target({0, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试车辆类型切换后在快速模式下的行为
TEST(ExecutorVehicleTypeTest, should_use_correct_fast_behavior_after_switching_vehicle_type)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when 使用普通车快速移动2步
    executor->SetVehicleType(VehicleType::Normal);
    executor->Execute("FM");

    // when 切换到跑车快速移动4步
    executor->SetVehicleType(VehicleType::SportsCar);
    executor->Execute("FM");

    // when 切换到公交车快速移动2步
    executor->SetVehicleType(VehicleType::Bus);
    executor->Execute("FM");

    // then 验证总移动距离：普通车(+2) + 跑车(+4) + 公交车(+2) = +8步
    const Pose target({8, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试车辆类型切换后在快速+反向模式下的行为
TEST(ExecutorVehicleTypeTest, should_use_correct_fast_reverse_behavior_after_switching_vehicle_type)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({7, 0, 'E'}));

    // when 使用普通车快速+反向移动1步
    executor->SetVehicleType(VehicleType::Normal);
    executor->Execute("BFM");

    // when 切换到跑车快速+反向移动4步
    executor->SetVehicleType(VehicleType::SportsCar);
    executor->Execute("BFM");

    // when 切换到公交车快速+反向移动2步
    executor->SetVehicleType(VehicleType::Bus);
    executor->Execute("BFM");

    // then 验证总移动距离：普通车(-1) + 跑车(-4) + 公交车(-2) = -7步
    const Pose target({0, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas