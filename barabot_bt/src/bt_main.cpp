#include "behaviortree_cpp_v3/bt_factory.h"
#include <rclcpp/rclcpp.hpp>

#include <barabot_bt/go_to_pose.hpp>

using namespace BT;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("bt_ros2_node");

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<GoToPose>("go_to_pose");

    // 🔥 BUAT BLACKBOARD
    auto blackboard = BT::Blackboard::create();

    // 🔥 MASUKKAN ROS2 NODE KE BLACKBOARD
    blackboard->set<rclcpp::Node::SharedPtr>("node", node);

    // 🔥 CREATE TREE DENGAN BLACKBOARD
    auto tree = factory.createTreeFromFile(
        "/home/bela/gazebo_ws/src/barabot_bt/trees/simple_bt.xml",
        blackboard);

    RCLCPP_INFO(node->get_logger(), "Starting BT Node...");

    BT::NodeStatus status = BT::NodeStatus::RUNNING;
    rclcpp::Rate rate(10);

    while (rclcpp::ok() && status == BT::NodeStatus::RUNNING)
    {
        status = tree.tickRoot();
        rclcpp::spin_some(node);
        rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}