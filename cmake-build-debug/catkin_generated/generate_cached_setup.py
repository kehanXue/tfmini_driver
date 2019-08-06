# -*- coding: utf-8 -*-
from __future__ import print_function
import argparse
import os
import stat
import sys

# find the import for catkin's python package - either from source space or from an installed underlay
if os.path.exists(os.path.join('/opt/ros/kinetic/share/catkin/cmake', 'catkinConfig.cmake.in')):
    sys.path.insert(0, os.path.join('/opt/ros/kinetic/share/catkin/cmake', '..', 'python'))
try:
    from catkin.environment_cache import generate_environment_script
except ImportError:
    # search for catkin package in all workspaces and prepend to path
    for workspace in "/home/kehan/focus_ws/devel;/home/kehan/kehan_ws/devel_isolated/realsense_gazebo_plugin;/home/kehan/kehan_ws/devel_isolated/local_planner;/home/kehan/kehan_ws/devel_isolated/global_planner;/home/kehan/kehan_ws/devel_isolated/vwbot_bringup;/home/kehan/kehan_ws/devel_isolated/zed_wrapper;/home/kehan/kehan_ws/devel_isolated/zed_video_sub_tutorial;/home/kehan/kehan_ws/devel_isolated/zed_tracking_sub_tutorial;/home/kehan/kehan_ws/devel_isolated/zed_rtabmap_example;/home/kehan/kehan_ws/devel_isolated/zed_ros;/home/kehan/kehan_ws/devel_isolated/zed_nodelet_example;/home/kehan/kehan_ws/devel_isolated/zed_display_rviz;/home/kehan/kehan_ws/devel_isolated/zed_depth_sub_tutorial;/home/kehan/kehan_ws/devel_isolated/zed_ar_track_alvar_example;/home/kehan/kehan_ws/devel_isolated/turtlebot3_teleop;/home/kehan/kehan_ws/devel_isolated/turtlebot3_navigation;/home/kehan/kehan_ws/devel_isolated/turtlebot3_msgs;/home/kehan/kehan_ws/devel_isolated/test_mavros;/home/kehan/kehan_ws/devel_isolated/sanchi_driver;/home/kehan/kehan_ws/devel_isolated/rviz_imu_plugin;/home/kehan/kehan_ws/devel_isolated/rplidar_ros;/home/kehan/kehan_ws/devel_isolated/mavros_extras;/home/kehan/kehan_ws/devel_isolated/mavros;/home/kehan/kehan_ws/devel_isolated/keyboard_ctrl;/home/kehan/kehan_ws/devel_isolated/mavros_msgs;/home/kehan/kehan_ws/devel_isolated/libmavconn;/home/kehan/kehan_ws/devel_isolated/imu_tools;/home/kehan/kehan_ws/devel_isolated/imu_filter_madgwick;/home/kehan/kehan_ws/devel_isolated/imu_complementary_filter;/home/kehan/kehan_ws/devel_isolated/cartographer_rviz;/home/kehan/kehan_ws/devel_isolated/cartographer_ros;/home/kehan/kehan_ws/devel_isolated/cartographer_ros_msgs;/home/kehan/Autoware/ros/devel;/opt/ros/kinetic".split(';'):
        python_path = os.path.join(workspace, 'lib/python2.7/dist-packages')
        if os.path.isdir(os.path.join(python_path, 'catkin')):
            sys.path.insert(0, python_path)
            break
    from catkin.environment_cache import generate_environment_script

code = generate_environment_script('/home/kehan/focus_ws/src/tfmini_driver/cmake-build-debug/devel/env.sh')

output_filename = '/home/kehan/focus_ws/src/tfmini_driver/cmake-build-debug/catkin_generated/setup_cached.sh'
with open(output_filename, 'w') as f:
    #print('Generate script for cached setup "%s"' % output_filename)
    f.write('\n'.join(code))

mode = os.stat(output_filename).st_mode
os.chmod(output_filename, mode | stat.S_IXUSR)
