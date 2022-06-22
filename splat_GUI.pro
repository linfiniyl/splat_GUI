QT       += core gui \
            core gui network \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    dat_file.cpp \
    graphics_view_zoom.cpp \
    license.cpp \
    lrp_file.cpp \
    main.cpp \
    mainwindow.cpp \
    qth_file.cpp \
    settings.cpp \
    udt_file.cpp

HEADERS += \
    about.h \
    dat_file.h \
    graphics_view_zoom.h \
    license.h \
    lrp_file.h \
    mainwindow.h \
    qth_file.h \
    settings.h \
    udt_file.h

FORMS += \
    about.ui \
    dat_file.ui \
    license.ui \
    lrp_file.ui \
    mainwindow.ui \
    qth_file.ui \
    settings.ui \
    udt_file.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    black.png \
    language/language_en.qm \
    language/language_en.ts \
    language/language_ru.qm \
    language/language_ru.ts \
    language_ru.qm \
    stylesheet/branch_closed.svg \
    stylesheet/branch_closed_hover.svg \
    stylesheet/branch_end.svg \
    stylesheet/branch_end_arrow.svg \
    stylesheet/branch_more.svg \
    stylesheet/branch_more_arrow.svg \
    stylesheet/branch_open.svg \
    stylesheet/branch_open_hover.svg \
    stylesheet/calendar_next.svg \
    stylesheet/calendar_previous.svg \
    stylesheet/checkbox_checked.svg \
    stylesheet/checkbox_checked_disabled.svg \
    stylesheet/checkbox_indeterminate.svg \
    stylesheet/checkbox_indeterminate_disabled.svg \
    stylesheet/checkbox_unchecked.svg \
    stylesheet/checkbox_unchecked_disabled.svg \
    stylesheet/clear_text.svg \
    stylesheet/close.svg \
    stylesheet/close_hover.svg \
    stylesheet/close_pressed.svg \
    stylesheet/computer.svg \
    stylesheet/desktop.svg \
    stylesheet/dialog_cancel.svg \
    stylesheet/dialog_close.svg \
    stylesheet/dialog_discard.svg \
    stylesheet/dialog_help.svg \
    stylesheet/dialog_no.svg \
    stylesheet/dialog_ok.svg \
    stylesheet/dialog_open.svg \
    stylesheet/dialog_reset.svg \
    stylesheet/dialog_save.svg \
    stylesheet/disc_drive.svg \
    stylesheet/down_arrow.svg \
    stylesheet/down_arrow_disabled.svg \
    stylesheet/down_arrow_hover.svg \
    stylesheet/file.svg \
    stylesheet/file_dialog_contents.svg \
    stylesheet/file_dialog_detailed.svg \
    stylesheet/file_dialog_end.svg \
    stylesheet/file_dialog_info.svg \
    stylesheet/file_dialog_list.svg \
    stylesheet/file_dialog_start.svg \
    stylesheet/file_link.svg \
    stylesheet/floppy_drive.svg \
    stylesheet/folder.svg \
    stylesheet/folder_link.svg \
    stylesheet/folder_open.svg \
    stylesheet/hard_drive.svg \
    stylesheet/help.svg \
    stylesheet/hmovetoolbar.svg \
    stylesheet/home_directory.svg \
    stylesheet/hseptoolbar.svg \
    stylesheet/left_arrow.svg \
    stylesheet/left_arrow_disabled.svg \
    stylesheet/left_arrow_hover.svg \
    stylesheet/maximize.svg \
    stylesheet/menu.svg \
    stylesheet/message_critical.svg \
    stylesheet/message_information.svg \
    stylesheet/message_question.svg \
    stylesheet/message_warning.svg \
    stylesheet/minimize.svg \
    stylesheet/network_drive.svg \
    stylesheet/radio_checked.svg \
    stylesheet/radio_checked_disabled.svg \
    stylesheet/radio_unchecked.svg \
    stylesheet/radio_unchecked_disabled.svg \
    stylesheet/restore.svg \
    stylesheet/right_arrow.svg \
    stylesheet/right_arrow_disabled.svg \
    stylesheet/right_arrow_hover.svg \
    stylesheet/shade.svg \
    stylesheet/sizegrip.svg \
    stylesheet/stylesheet.qss \
    stylesheet/transparent.svg \
    stylesheet/trash.svg \
    stylesheet/undock.svg \
    stylesheet/undock_hover.svg \
    stylesheet/undock_hover_pressed.svg \
    stylesheet/unshade.svg \
    stylesheet/up_arrow.svg \
    stylesheet/up_arrow_disabled.svg \
    stylesheet/up_arrow_hover.svg \
    stylesheet/vline.svg \
    stylesheet/vmovetoolbar.svg \
    stylesheet/vseptoolbar.svg \
    stylesheet/window_close.svg

RESOURCES += \
    icon.qrc \
    language.qrc \
    style.qrc
TRANSLATIONS += \
     language/language_en.ts \
     language/language_ru.ts

