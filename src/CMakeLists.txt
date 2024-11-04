cmake_minimum_required(VERSION 3.5)

project(CPP_3DViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Задаем флаги компиляции
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
add_compile_options(
    -Wall
    -Wextra
    -Wno-deprecated #флаг игнорирующий ошибку устаревших функций
    -Wpedantic
)
endif()

set(QT_OPENGL_WIDGETS_MODULE "OpenGLWidgets")

if(QT_MAJOR_VERSION EQUAL 5)
    find_package(Qt5OpenGLWidgets QUIET)
    if(NOT Qt5OpenGLWidgets_FOUND)
        set(QT_OPENGL_WIDGETS_MODULE "OpenGL")
    endif()
endif()

#Задааем переменную для тестирования и выключаем тестирование по дефолту
option(TESTING "Модульное тестирование" OFF)

#Задааем переменную для покрытия тестами и выключаем тестирование по дефолту
option(COVERAGE "Покрытие тестами" OFF)

#Задаем исходники модели
set(MODEL_SRC
    model/affine.cc
    model/affine.h
    model/model.cc
    model/model.h
    model/parser.cc
    model/parser.h
)

#Создаем либу модели
add_library(
    lib_back
    STATIC
    ${MODEL_SRC}
)

if(TESTING) ### проверяем включено ли модульное тестирование
    add_subdirectory(tests) ### если да, то собираем тесты и покрытие при необходимости
else() ### если нет, то собираем проект
    message(STATUS "Тестирование проекта CPP_3DViewer выключено")
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    #Устанавливаем путь до компонентов Qt
    set(CMAKE_PREFIX_PATH "/Users/Anonymous/Qt/6.5.0/macos/lib/cmake")

    #Находим и подключаем необходимые пакеты для OpenGL
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets ${QT_OPENGL_WIDGETS_MODULE})
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets ${QT_OPENGL_WIDGETS_MODULE})

    #Находим и подключаем необходимые кьютишные пакеты
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

    add_subdirectory(libs/QtGifImage)

    #Задаем исходники контроллера
        set(CONTR_SRC
            controller/controller_object.cc
            controller/controller_object.h
        )

        #Задаем исходники интерфейса
        set(VIEW_SRC
            view/mainwindow.cc
            view/mainwindow.h
            view/mainwindow.ui
            view/glwidget.cc
            view/glwidget.h
            view/recorder.cc
            view/recorder.h
            view/settings.cc
            view/settings.h
        )

        #Создаем либу контроллера
        add_library(
            lib_controller
            STATIC
            ${CONTR_SRC}
        )

        #Создаем либу интерфейса
        add_library(
            lib_view
            STATIC
            ${VIEW_SRC}
        )

        #Создаем кьютишный таргет сборки
        if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
            qt_add_executable(CPP_3DViewer
                MANUAL_FINALIZATION
                main.cc
            )

        #Настройки под сборку на андройде

        # Define target properties for Android with Qt 6 as:
        #    set_property(TARGET CPP_3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
        #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
        # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
        else()
            if(ANDROID)
                add_library(CPP_3DViewer SHARED
                    ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
            else()
                add_executable(CPP_3DViewer
                    ${PROJECT_SOURCES}
                )
            endif()
        endif()

        #Говорим, что для либы вью нужна обязательна либа модели и контроллера, и что снаружи вью недоступны все методы бэка
        target_link_libraries(lib_view PRIVATE lib_back lib_controller)

        #Говорим, что для либы вью нужны обязательна либы кьюта, и что снаружи вью они недоступны
        target_link_libraries(lib_view PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
        target_link_libraries(lib_view PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
	    target_link_libraries(lib_view PRIVATE Qt${QT_VERSION_MAJOR}::${QT_OPENGL_WIDGETS_MODULE})
        target_link_libraries(lib_view PRIVATE QtGifImage::QtGifImage)

        #Говорим, что для таргета билда обязательна либа вью, и что снаружи ее методы недоступны
        target_link_libraries(CPP_3DViewer PRIVATE lib_view)
        
        #Говорим, что для таргета билда обязательны Qt::widgets, QtGifImage и либа OpenGL 
        target_link_libraries(CPP_3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
        target_link_libraries(CPP_3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::${QT_OPENGL_WIDGETS_MODULE})
        target_link_libraries(CPP_3DViewer PRIVATE QtGifImage::QtGifImage)

        #Настройки системы
        set_target_properties(CPP_3DViewer PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
        )

        install(TARGETS CPP_3DViewer
            BUNDLE DESTINATION .
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

        if(QT_VERSION_MAJOR EQUAL 6)
            qt_finalize_executable(CPP_3DViewer)
        endif()
endif()
