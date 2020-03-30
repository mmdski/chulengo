# Developing on Linux

## Set up the development environment

### Install the required packages
```
$ sudo apt install clang-format-9 gcc libglib2.0-dev python3-pip valgrind
```

### Install the required Python packages
```
$ pip3 install --user requirements.txt
```

## Build the documentation
```
$ python3 setup.py build_sphinx
```

## Configure Meson
```
$ meson -Db_coverage=true build
```

## Run the tests and produce coverage reports
```
$ ninja -C build test coverage
```
