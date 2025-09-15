# quicktype cpp

## Install

1.  Install `nlohmann/json`, `python-yaml`, `quicktype`

For example: ArchLinux

```sh
sudo pacman -S nlohmann-json python-yaml quicktype
```

## Usage

Build proto:

```sh
./qtcpp/qtcpp build --proto_root example/include/json_proto --all
./qtcpp/qtcpp build --proto_root example/include/json_proto --proto_dir_name user_profile
```

Get Help:

```sh
./qtcpp/qtcpp --help
./qtcpp/qtcpp build --help
```

config.yaml:

```yaml
schema_conversion:
  additional_args:
    - "--all-properties-optional"
    # Other schema conversion parameters can be added

cpp_conversion:
  additional_args:
    - "--no-boost"
    - "--code-format with-struct"
    # - "--include-location global-include"
    # Other C++ conversion parameters can be added
```

## If the C++ version used is less than `C++17`

config.yaml:

```yaml
cpp_conversion:
  additional_args:
    - "--boost"
```

If your project does not use the Boost library, you can use [bcp](https://github.com/boostorg/bcp) to extract `boost::optional`.
