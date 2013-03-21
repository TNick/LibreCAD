QT       -= core gui
TEMPLATE = app
CONFIG += console warn_on

# Use common project definitions.
include(../../settings.pro)
include(../../common.pro)

# google test library
LIBS += -lgtest_main -lgtest

SOURCES += \
    tests/DRW_Text_test.cpp

