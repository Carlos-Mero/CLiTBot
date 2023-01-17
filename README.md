# CLiTBot

![](https://cdn.jsdelivr.net/gh/Yellow-GGG/Pics@main/save.bmp)

![](https://cdn.jsdelivr.net/gh/Yellow-GGG/Pics@main/r9S7Re.png)

本仓库是北京某高校2022-2023学年秋季学期wyp老师的《程序设计基础》课程的小组作业项目。

本次小组作业项目名为“CLiTBot”，期望能够实现一个类似于机器人点灯的小游戏。
---

### 编译策略

目前我们采用CMake实现跨平台构建方案，其中使用到了外部库[raylib](https://github.com/raysan5/raylib)实现图形绘制，并应用pkg-config进行库管理。在开始构建项目前需要首先安装raylib游戏引擎（约2MB）以及pkg-config。

对于macOS用户而言，这一过程可以通过Homebrew完成，只需在终端中依次执行如下指令即可：

```shell
brew install cmake
brew install raylib
brew install pkg-config
```

Linux系统已内置有pkg-config（不过也分很多情况），还需要安装CMake以及raylib。我们尚未针对Linux系统进行测试，具体操作方案可以参考raylib官方的[环境配置指导](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)。

在相关依赖安装完毕后，我们可以在此项目文件夹中打开终端，依次输入：

```shell
mkdir build
cd build && cmake ..
make
```

由此即可完成项目构建。

对于Windows平台，我们可以采用vcpkg替代pkg-config进行库管理。首先安装好vcpkg，然后在终端中输入：

```
vcpkg install raylib
```

进入到项目根目录中的build文件夹下，使用

```
cmake .. -G "Visual Studio 16 2019" -A x64
```

生成VS工程文件，此后就可以进入VS进行项目构建了。

此外，本项目的release页面也有macOS版本的预编译程序可供下载游玩（ARM64架构）。

### 备注/已知问题

本游戏中的地图绘制功能采用.bmp格式输出且未经压缩，占用存储较大，不建议在游戏过程中频繁使用。这项功能更多仅用作测试用途。

已知本游戏已知在macOS下直接运行会出现寻址异常……无法定位到游戏工作文件夹位置。暂时可以采取替代方案，在游戏文件夹中打开终端，并输入：

```shell
./CLiTBot
```

指令运行游戏可以解决这一问题。我们还在寻找解决方案。

本游戏仅作为大作业项目提交，并无长期运营的打算，也因为后期赶工（确信），在代码的拓展性与可维护性上有不少缺憾，不过这应该不会对游戏内容造成过多影响。

最后，因为项目开发时间以及制作者能力有限，大作业最终效果尚且相当粗糙，还望体谅。