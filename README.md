# tfmini_driver ROS package

> 该 package 为 tfmini 激光模块在ROS下的驱动

## 使用

启动tfmini_driver节点:

```shell
roslaunch tfmini_driver tfmini.launch
```

tfmini.launch文件参数说明:

- 默认串口号: `/dev/ttyUSB0`

- model: 默认为 `tfmini` (目前仅为tfmini, 暂不支持tfmini_plus)
- baud: 默认波特率为 `115200`
- frame_id: 默认为 `tfmini_link`, 但该参数目前无意义, TODO
- msg_length: tfmini一帧的数据长度, 默认为 `9`
- publish_rate: 话题中消息的发布频率, 默认为 `100Hz`

其他可选参数:

- dist_topic: 输出dist信息的topic名称, 默认为 `/tfmini_driver_node/dist`
- strength_topic: 输出strength信息的topic名称 `/tfmini_driver_node/strength`
- mode_topic: 输出mode信息的topic名称 `/tfmini_driver_node/mode`

## 接口说明

tfmini模块可以输出三种消息, 分别为距离前方障碍物的距离dist, 当前激光的强度值strength以及当前模块所处的测距档位mode. 

ROS topics:

- /tfmini_driver_node/dist: 话题中数据类型为 `std_msgs/Float32` , 消息中数据为tfmini距离前方障碍物的距离dist的值, 单位由tfmini模块而定, 其出厂默认单位为cm. dist数据范围为30cm-1200cm, 当障碍物距离小于30cm时, 会一直输出30cm, 大于1200cm时同理.  //TODO, 消息中数据类型可采用std_msgs/Int16
- /tfmini_driver_node/strength: 话题中数据类型为 `std_msgs/Int32`,  消息中数据为当前激光的强度值. 默认输出值会在0-3000之间, 当strength数据小于20的时候, 认为此时dist数据不可信. 20-2000之间一般认为数据可信, 具体可根据实际来调整.
- /tfmini_driver_node/mode: 话题中数据类型为`std_msgs/Int8`, 消息中数据为当前模块所处的测距档位. 默认有02和07两种档位. 02档为近距离挡, 07档为远距离档, 具体切换细节见tfmini用户手册/[淘宝商家链接](https://m.tb.cn/h.eVXx8B1?sm=662002). 