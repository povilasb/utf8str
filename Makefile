build_type ?= Debug
build_type_lower = ${shell echo ${build_type} | tr "[:upper:]" "[:lower:]"}

build_dir ?= build/${build_type_lower}
cmake_dir := $(CURDIR)

build_tests ?= OFF


all:
	@echo "Usage:"
	@echo -e "\tmake release"
	@echo -e "\tmake debug"
	@echo -e "\tmake test"
	@echo -e "\tmake clean"
.PHONY: all

.PHONY: build
build:
	mkdir -p $(build_dir) && cd $(build_dir) && \
		cmake \
		-D CMAKE_BUILD_TYPE=$(build_type) \
		-D UTF8STR_ENABLE_TESTS=$(build_tests) \
		$(cmake_dir) && make

release:
	build_type=Release $(MAKE) build
.PHONY: release

.PHONY: debug
debug:
	CXX=clang++-4.0 $(MAKE) build

.PHONY: test
test:
	build_tests=ON $(MAKE) build
	$(MAKE) -C $(build_dir) run-tests

.PHONY: clean
clean:
	rm -rf build

# Redirect all undefined targets to cmake.
%:
	make -C $(build_dir) $@
