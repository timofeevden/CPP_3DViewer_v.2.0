include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

### Проверяем если включено покрытие тестами(gcov), то добавляем флаг компиляции
if(COVERAGE)
add_compile_options("--coverage")
add_link_options("--coverage")
endif()

set(TEST_SRC
    test_affine.cc
    test_main.cc
    test_parcer.cc
    tests.h
)

### Компилируем исполняемый файл теста
add_executable(
    3DViewer_test
    ${TEST_SRC}
)

### Линкуем к исполняемому файлу либу модели и либу GTest
target_link_libraries(3DViewer_test PRIVATE lib_back GTest::gtest_main)

### Линкуем GTets
gtest_discover_tests(3DViewer_test)

### Создаем команду для запуска тестов
add_custom_target(check COMMAND 3DViewer_test)

### Находим gcovr
find_program(GCOVR_EXECUTABLE gcovr)
if(COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

### При включении покрытия тестами добавляем флаг компиляции к либе модели
    target_compile_options(lib_back PRIVATE --coverage)

### Создаем команду для запуска анализа покрытия тестами
    add_custom_target(coverage
        COMMAND
            ${GCOVR_EXECUTABLE}
                --root=${CMAKE_SOURCE_DIR}/model # указываем папку с анализируемыми исходниками
                --object-directory=${CMAKE_BINARY_DIR} # указываем папку с бинарниками
                --html --html-details -o ${CMAKE_SOURCE_DIR}/report/report.html # просим создать отчет в HTML
        DEPENDS # говорим, что данная цель зависит от команды check
            check
    )
elseif(MYLIB_COVERAGE AND NOT GCOVR_EXECUTABLE)
    set(MYLIB_COVERAGE OFF)
    message(WARNING "Для замеров покрытия кода тестами требуется программа gcovr")
endif()