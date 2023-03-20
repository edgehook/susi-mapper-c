# SUSI-Mapper-c
该项目是针对研华AppHub解决方案，在设备端开发的一个对接研华SUSI SDK的插件，通过该插件，可以通过无代码的方式，将SUSI采集的信息接入到AppHub中，并且对这些数据进行监控管理。该插件公开，客户也可以参考该插件，去开发对接其他SDK的AppHub 插件。开发之前你需要先熟悉研华AppHub和ithings 物模型协议。
当前支持 Linux & windows，windows 还在验证阶段。
当前值对接了SUSI中Board information， Hardware monitor， GPIO三个功能。
## 1. 源码目录架构
 - 3rdparty：第三方库源码，当前主要为MQTT 源码
 - susi-mapper ：基于susi sdk  mapper 的实现，当前是一个非常简单的mapper 的实现。
 - include： sdk include 的文件夹
 - lib: 第三方链接库的存放路径
 - susi-library:存放SUSI库
 - src：开发客户mapper 是的基础SDK， 通常客户不需要更改。

## 2. 编译运行
1. 编译&运行
该工程为cmake工程，可以使用cmake 进行编译，为了简化编译流程，我们提供了单独的编译脚本用于编译。 
```bash
$ ./build.sh 
# 编译完成后 demo/下回有叫demo 的二进制文件生成
$ ./susi-mapper/susi-mapper 即可开启mapper 的执行。
```
mapper 的运行前，需要先开启Apphub Agent 1.0.5 之后的版本。Apphub Agent 需要开启eventbus 总线。具体开启方式，请参照Apphub Agent 的相关说明文档进行。等Apphub Agent 开启后，修改susi-mapper.c 中对应的broker 地址信息，完成编译后，即可开启susi mapper的使用。 如果你的Apphub Agent 和susi mapper 在同一个机器上，则一般不需要修改源码就可以直接运行。

## 3. Mapper 开发
Mapper 的开发可以参考susi-mapper路径下的源码实现。susi-mapper.c 里已经比较清晰地注释了，开发的基本逻辑结构。同时 SDK 里提供了大量的基础组件可供开发这参考，例如基础的链表，队列，则塞队列，跨平台的线程，互斥锁，信号量，条件变量， 线程池，事件观察器，uuid， log 机制 等诸多组件。

## 4. 关于贡献
本项目为开源项目，欢迎各位的贡献。贡献方式为pull-request 机制。


