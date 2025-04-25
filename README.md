# Game Settings Loader

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibOB64](https://github.com/shad0wshayd3-TES4/CommonLibOB64)
	* Add this as as an environment variable `CommonLibOB64Path`

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/powerof3/GameSettingsLoader.git
cd GameSettingsLoader
cmake --preset vs2022-windows-vcpkg-ob64
cmake --build build --config Release
```

## License
[GPL](LICENSE)
