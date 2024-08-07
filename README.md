<p align="right">
  English / <a href="./README.zh-CN.md">简体中文</a>
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
[![GitHub Release](https://img.shields.io/github/v/release/xj63/PID?include_prereleases&style=flat-square&label=%F0%9F%93%A6%20Release&color=purple)](https://github.com/xj63/PID/releases)

</div>

## 👋 Introduction

A collection of PID implementations.

- Unified call interface, no need to worry about specific PID implementations
- Static memory allocation, no dependencies, suitable for microcontrollers
- Easy to extend, supports running multiple PID controllers simultaneously
- Includes analysis, testing, and simulation tools (TODO)
- Comes with [documentation](https://xj63.github.io/PID-docs) and [examples](./examples)

## 🚀 Features

- [x] default
- [x] integral decay
- [x] integral clamp
- [x] integral separation
- [x] integral sliding window

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

## 📦 Add to project

It is recommended to download pid directly from [GitHub Release](https://github.com/xj63/PID/releases)
(remove the `example` `test` `simulate` folders) and unzip it to the project directory,
add the code files under `pid` to the project and you can use it.

You can also use `git clone` to the project directory.

```sh
$ git clone https://github.com/xj63/PID -o pid  # clone to local
```

## Contributing

Welcome contributions to add new features and improve this PID controller implementation!

## Star History

<a href="https://star-history.com/#xj63/PID&Date">
 <picture>
   <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=xj63/PID&type=Date&theme=dark" />
   <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=xj63/PID&type=Date" />
   <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=xj63/PID&type=Date" />
 </picture>
</a>
