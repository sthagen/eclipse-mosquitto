R=../../..
include ${R}/config.mk

.PHONY: all check test-compile test clean

LOCAL_CPPFLAGS+= \
	-I../ \
	-I${R}/include \
	-I${R} \
	-I${R}/lib \
	-I${R}/test/mock

LOCAL_CXXFLAGS+=-std=c++20 -Wall -ggdb -D TEST_SOURCE_DIR='"$(realpath .)"'

MOCK_OBJS = \
	base64_common_mock.o \
	file_common_mock.o \
	libmosquitto_common_mock.o \
	memory_common_mock.o \
	mqtt_common_mock.o \
	password_common_mock.o \
	property_common_mock.o \
	random_common_mock.o \
	strings_common_mock.o \
	time_common_mock.o \
	topic_common_mock.o \
	utf8_common_mock.o

all : test-compile

test-compile: ${MOCK_OBJS}
check : test

# MOCKS

${MOCK_OBJS} : %.o: %.cpp libmosquitto_common_mock.hpp
	$(CROSS_COMPILE)$(CXX) $(LOCAL_CPPFLAGS) $(LOCAL_CXXFLAGS) -c $< -o $@

clean :
	-rm -rf *.o *.gcda *.gcno

install:

uninstall:
