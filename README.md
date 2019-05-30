# sanchi_driver ROS package

> 该 package 为改进后的"三弛惯性 100D2"型号 AHRS 的 ROS 下的驱动

## 一.依赖项:

1. boost库版本 >= 1.58

2. 可视化阶段需要安装`rviz_imu_plugin` :

   ```shell
   sudo apt-get install ros-kinetic-rviz-imu-plugin
   ```

## 二.放入工作空间中并编译

## 三.启动文件

启动imu:

```shell
roslaunch sanchi_driver imu_100D2.launch
```

启动rviz可视化:

```shell
roslaunch sanchi_driver rviz.launch
```

后面会继续更新README.md
