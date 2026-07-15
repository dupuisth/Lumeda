# Lumeda

## Linux

TODO

> Use the scripts

## Windows development with VS Code

The repository provides a short command-line interface that keeps the workflow close to Linux while using the native Windows toolchain: Visual Studio 2022, MSVC, and MSBuild.

### Requirements

- Visual Studio 2022 Community or Build Tools with the **Desktop development with C++** workload;
- Git;
- VS Code with Microsoft's recommended **C/C++** extension.

Run the setup command once after cloning the repository:

```powershell
.\dev.cmd setup
```

The script initializes the Git submodules and generates the solution using the copy of Premake included in the repository.

### Commands

```powershell
.\dev.cmd build debug
.\dev.cmd build release
.\dev.cmd build profiling
.\dev.cmd rebuild debug
.\dev.cmd run debug
.\dev.cmd clean debug
```

The commands work from PowerShell, `cmd.exe`, and Git Bash (`./dev.cmd build debug`). The default configuration is `debug`, so `.\dev.cmd build` is enough for the common case.
