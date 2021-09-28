# Modern C++ development with vcpkg dependency manager - boilerplate application

My motivation to create this repository is that, it's still very difficult (in 2021) to use a good cross-plattform dependency manager, if you like working with C++.
First I tried the Conan dependency manager, but I experienced a lot of compatibility problems even on the same OS, when I tried to move the project to an other developer machine.

Nowadays I tried to use vcpkg, I love it because it is using a similar json file like in javascript projects, to describe dependecies. 

**Pros:**

- to use vcpkg, you do not need any installer or third party tools, just you can download the source from github
- after a 2 minutes installation you are able to compile from source a tons of third party packages. This process will create a vcpkg.cmake file, which you can set on user level or application level. (user level is more general approach)

This project dependecies were defined in the following form:
```
{
    "name": "cmake-vcpkg-opencl",
    "version-string": "0.1.0",
    "dependencies": [
        "opencv",
        "eigen3",
        "gtest"
    ]
}
```
I think it is a very compact, self-evident description.

As an example, a simple PDE solver has been presented, solving the Heating differencial equation wih the classical Euler's method.

## Example: PDE solver with Euler's method

## Installation steps

**1.) Clone repository**

**2.) Install vcpkg**

Clone the official repository somewhere:
```
git clone https://github.com/Microsoft/vcpkg.git
```

Run the bootstrap script to build vcpkg:
```
.\vcpkg\bootstrap-vcpkg.bat
```

On Windows: using vcpkg with MSBuild
```
vcpkg integrate install
```

Open settings.json in VC Code and add:

```
"cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "[VCPKG_INSTALLATION_DIR]/scripts/buildsystems/vcpkg.cmake"
    },
```

Select 'Build' on toolbar.
