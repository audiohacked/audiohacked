TARGET           := arm-none-eabi
PREFIX           := $(pwd)/$(TARGET)
BUILD_OPTS       := --enable-interwork --enable-multilib
BUILD_OPTS2      := --with-cpu=cortex-m4 --with-fpu=fpv4-sp-d16
BUILD_OPTS3      := --with-float=hard --with-mode=thumb
binutils_VERSION := binutils-2.25.1
binutils_URL     := ftp://ftp.gnu.org/gnu/binutils/$(binutils_VERSION).tar.gz
binutils_OPTS    := 
gcc_VERSION      := gcc-4.8.5
gcc_URL          := ftp://ftp.gnu.org/gnu/gcc/$(gcc_VERSION)/$(gcc_VERSION).tar.gz
gcc_OPTS         := 
gdb_VERSION      := gdb-7.7
gdb_URL          := ftp://ftp.gnu.org/gnu/gdb/$(gdb_VERSION).tar.gz
gdb_OPTS         := 

prepare_all:
	@mkdir -p source build

download_binutils download_gcc download_gdb: prepare_all
	wget --unlink -c $($(subst download_,,$@)_URL)

prepare_binutils prepare_gcc prepare_gdb:
	make $(subst prepare_,download_,$@)
	tar xzvf $($(subst prepare_,,$@)_VERSION).tar.gz -C source
	mkdir -p build/$($(subst prepare_,,$@)_VERSION)

build_binutils: download_binutils prepare_binutils
	cd build/$(binutils_VERSION) && \
	../../source/$(binutils_VERSION)/configure \
		--target=$(TARGET) \
		--prefix=$(PREFIX) \
		$(BUILD_OPTS) $(BUILD_OPTS2) $(BUILD_OPTS3) $(bintuils_OPTS) \
		--disable-nls
	cd build/$(binutils_VERSION) && \
	make all && \
	make install-strip

bootstrap_gcc: download_gcc prepare_gcc
	cd build/$(gcc_VERSION) && \
	../../source/$(gcc_VERSION)/configure \
		--target=$(TARGET) \
		--prefix=$(PREFIX) \
		$(BUILD_OPTS) $(BUILD_OPTS2) $(BUILD_OPTS3) $(gcc_OPTS) \
		--enable-languages=c \
		--disable-shared \
		--disable-nls
	cd build/$(gcc_VERSION) && \
	make all-gcc && \
	make all-target-libgcc && \
	make install-gcc && \
	make install-target-libgcc

build_gcc: bootstrap_gcc
	cd build/$(gcc_VERSION) && \
	../../source/$(gcc_VERSION)/configure \
		--target=$(TARGET) \
		--prefix=$(PREFIX) \
		$(BUILD_OPTS) $(BUILD_OPTS2) $(BUILD_OPTS3) $(gcc_OPTS) \
		--enable-languages=c,c++ \
		--disable-shared \
		--disable-nls
	cd build/$(gcc_VERSION) && \
	make all-gcc && \
	make install-strip

build_gdb: bootstrap_gcc
	cd build/$(gdb_VERSION) && \
	../../source/$(gdb_VERSION)/configure \
		--target=$(TARGET) \
		--prefix=$(PREFIX) \
		$(BUILD_OPTS) $(BUILD_OPTS2) $(BUILD_OPTS3) $(gdb_OPTS) \
		--disable-nls
	cd build/$(gdb_VERSION) && \
	make all-gcc && \
	make install-strip

everything: build_binutils bootstrap_gcc build_gdb
