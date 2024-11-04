VERSION = `date +"%Y.%m.%d"`
ARCHIVE = 3DViewer-$(VERSION)

all: build

build: 
	git submodule update --init
	mkdir -p build
	cmake -S ./ -B build
	cmake --build build

install:
	git submodule update --init
	mkdir -p 3DViewer_2
	cmake -S ./ -B 3DViewer_2
	cmake --build 3DViewer_2

uninstall:
	rm -rf 3DViewer_2
	rm -f 3d_viewer_settings.ini

test: clean
	mkdir tests/build_test
	cmake -S ./ -B tests/build_test -DTESTING=ON
	cmake --build tests/build_test --target check

gcov_report: clean
	mkdir tests/build_test
	mkdir report
	cmake -S ./ -B tests/build_test -DTESTING=ON -DCOVERAGE=ON
	cmake --build tests/build_test --target coverage
	open report/report.html

dist:
	tar -cf $(ARCHIVE).tar controller model view libs tests CMakeLists.txt Makefile Doxyfile dvi.html main.cc

dvi:
	mkdir docs
	doxygen Doxyfile
	mv html latex docs
	open docs/html/index.html

dvi_open:
	open dvi.html

valgrind:
	cd tests/build_test/tests/ && valgrind --leak-czheck=yes --track-origins=yes ./3DViewer_test

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=google -i ./model/*.cc ./model/*.h ./controller/*.cc ./controller/*.h ./view/*.cc ./view/*.h ./tests/*.cc ./tests/*.h
	clang-format -style=google -n ./model/*.cc ./model/*.h ./controller/*.cc ./controller/*.h ./view/*.cc ./view/*.h ./tests/*.cc ./tests/*.h
	rm .clang-format

cpp_check:
	cppcheck --suppress=missingIncludeSystem --language=c++ ./model/*.cc ./model/*.h ./controller/*.cc ./controller/*.h ./view/*.cc ./view/*.h ./tests/*.cc ./tests/*.h

clean: 
	rm -rf report/ docs/ tests/build_test/

realclean: clean
	rm -rf build *.tar

git: realclean clean uninstall
	git add -A
	git commit -m "$m"
	git push origin "$b"

