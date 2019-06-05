# Basalt
a machine-learning project manager

## Environment
Ubuntu 16.04 x64

## Dependencies
The packages below are required to build Basalt.

### Eigen3
Download and install instructions can be found at: http://eigen.tuxfamily.org. Required at least 3.1.0.

### OpenCV3
```
git clone https://github.com/opencv/opencv.git
```
or follow the guidance in https://opencv.org.

### Qt5
Type in a terminal:
```
sudo apt-get install qt5-default qtcreator
```

### yaml-cpp
```
git clone https://github.com/jbeder/yaml-cpp.git
``` 
and build.

## How to build
```
mkdir build \
cd build \
cmake .. \
make \
```
