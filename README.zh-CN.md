<p align="right">
  <a href="./README.md">English</a> / 简体中文
</p>

<div align="center">
  <img src="https://xj63.github.io/PID-docs/pid-logo.svg" width="40%">
</div>

<h1 align="center">PID</h1>

<div align="center">

[![Docs](https://img.shields.io/badge/Docs-PID--docs-blue?style=flat-square&logo=readthedocs&logoColor=green&color=lightgreen)](https://xj63.github.io/PID-docs/)
[![License](https://img.shields.io/github/license/xj63/PID?style=flat-square&label=%E2%9A%96%20License)](./LICENSE)
![Repo Stars](https://img.shields.io/github/stars/xj63/PID?style=flat-square&label=%E2%9C%A8%20Stars)
![Language](https://img.shields.io/badge/Language-C-yellow?style=flat-square&logo=c)
[![Last Commit](https://img.shields.io/github/last-commit/xj63/PID?style=flat-square&label=%F0%9F%94%A5%20Last%20commit&color=orange)](https://github.com/xj63/PID/activity)
[![Tag](https://img.shields.io/github/v/tag/xj63/PID?style=flat-square&label=%F0%9F%8F%B7%EF%B8%8FTag&color=purple)](https://github.com/xj63/PID/tags)

</div>

## 👋 简介

一个PID实现的集合。

- 统一的调用接口，无需关注具体的 PID 实现
- 静态内存分配，无任何依赖，可用于单片机
- 易于扩展，支持同时运行多种 PID 控制器
- 包含分析、测试、模拟工具(TODO)
- 拥有[文档](https://xj63.github.io/PID-docs)和[示例](./examples)

## 🚀 功能

- [x] default （默认）
- [x] integral decay （积分衰减）
- [x] integral clamp （积分限幅）
- [x] integral separation （积分分离）
- [x] integral sliding window （积分滑动窗口，积分有限时间）

## 📖 Example

see more in [examples](./examples)

```c
#include "pid/pid.h"
#include <stdbool.h>

void unknown_control(float thrust);
float unknown_sensor();

int main() {
  struct Pid pid = pid_new(1, 0, 0);
  float target = 0;
  while (true) {
    float actual = unknown_sensor();
    float thrust = pid_update(&pid, target, actual, 0.1);
    unknown_control(thrust);
  }
}
```

## Contributing

欢迎贡献以添加新功能并改进此 PID 控制器的实现！

## Star History

<a href="https://star-history.com/#xj63/PID&Date">
 <picture>
   <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=xj63/PID&type=Date&theme=dark" />
   <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=xj63/PID&type=Date" />
   <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=xj63/PID&type=Date" />
 </picture>
</a>
