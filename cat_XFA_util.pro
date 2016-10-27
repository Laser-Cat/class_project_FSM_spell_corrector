#-------------------------------------------------
#This is a time-space balanced automaton framework
#we are going to apply it as a DFA toolkit
#by Laser Cat ^_<
#E-mail:lasercat@sina.com
#-------------------------------------------------

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test_src/main.cpp \
    src/cat_abstract_automa.cpp \
    src/cat_xfa_defines.cpp \
    src/cat_xfa_factory.cpp \
    src/cat_indexed_sparse_list.cpp \
    src/cat_fsm.cpp \
    src/cat_xfa.cpp \
    src/cat_abstract_automaton.cpp
TARGET=bin/xfa

HEADERS += \
    src/cat_abstract_automa.h \
    src/common_include.h \
    src/cat_xfa_defines.h \
    src/cat_xfa_factory.h \
    src/cat_indexed_sparse_list.h \
    src/cat_fsm.h \
    src/cat_xfa.h \
    src/cat_abstract_automaton.h
