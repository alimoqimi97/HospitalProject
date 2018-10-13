#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T16:47:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += sql

TARGET = hospital_project
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11


INCLUDEPATH  += C:\MySQL\include


TEMPLATE = app


SOURCES += main.cpp \
    patient.cpp \
    visit_time.cpp \
    doctor.cpp \
    section.cpp \
    hospital.cpp \
    linklist.cpp \
    pharmacy.cpp \
    prescription.cpp \
    assurance.cpp \
    medicine.cpp \
    user.cpp \
    t_database.cpp \
    manager.cpp \
    doctorvisittime.cpp \
    patientvisittime.cpp

HEADERS += \
    patient.h \
    visit_time.h \
    doctor.h \
    section.h \
    hospital.h \
    linklist.h \
    pharmacy.h \
    prescription.h \
    assurance.h \
    medicine.h \
    user.h \
    t_database.h \
    manager.h \
    doctorvisittime.h \
    patientvisittime.h
