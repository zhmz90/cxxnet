#-----------------------------------------------------
#  cxxnet: the configuration compile script
#
#  This is the default configuration setup for cxxnet
#  If you want to change configuration, do the following steps:
#
#  - copy this file to the root folder
#  - modify the configuration you want
#  - type make or make -j n for parallel build
#----------------------------------------------------

# choice of compiler
export CC = gcc
export CXX = g++
export NVCC = nvcc

# whether use CUDA during compile
USE_CUDA = 1

# add the path to CUDA libary to link and compile flag
# if you have already add them to enviroment variable, leave it as NONE
USE_CUDA_PATH = NONE

# whether use opencv during compilation
# you can disable it, however, you will not able to use
# imbin iterator
USE_OPENCV = 1
USE_OPENCV_DECODER = 1
# whether use CUDNN R3 library
USE_CUDNN = 0
# add the path to CUDNN libary to link and compile flag
# if you do not need that, or do not have that, leave it as NONE
USE_CUDNN_PATH = NONE
# whether to build caffe converter
USE_CAFFE_CONVERTER = 0
CAFFE_ROOT =
CAFFE_INCLUDE =
CAFFE_LIB =
#
# choose the version of blas you want to use
# can be: mkl, blas, atlas, openblas
USE_STATIC_MKL = NONE
USE_BLAS = blas
#
# add path to intel libary, you may need it
# for MKL, if you did not add the path to enviroment variable
#
USE_INTEL_PATH = NONE

# whether compile with parameter server
USE_DIST_PS = 0
PS_PATH = NONE
PS_THIRD_PATH = NONE

# whether compile with rabit
USE_RABIT_PS = 0
RABIT_PATH = rabit

# use openmp iterator
USE_OPENMP_ITER = 1
# the additional link flags you want to add
ADD_LDFLAGS = -ljpeg

# the additional compile flags you want to add
ADD_CFLAGS =
#
# If use MKL, choose static link automaticly to fix python wrapper
#
ifeq ($(USE_BLAS), mkl)
	USE_STATIC_MKL = 1
endif

#------------------------
# configuration for DMLC
#------------------------
# whether use HDFS support during compile
# this will allow cxxnet to directly save/load model from hdfs
USE_HDFS = 0

# whether use AWS S3 support during compile
# this will allow cxxnet to directly save/load model from s3
USE_S3 = 0

# path to libjvm.so
LIBJVM=$(JAVA_HOME)/jre/lib/amd64/server
