# PDE solver with Euler's method

# Installation steps

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
