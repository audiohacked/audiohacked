#!/bin/bash

## Set Bash Scripting
set -o errexit
set -o nounset 

## Set Variables for use
echo "Using \$MANGOS_DESTDIR = ${MANGOS_DESTDIR:=/opt/mangos}"
echo "Using \$SD2_PATCH = ${SD2_PATCH:=MaNGOS-2008-12-22-ScriptDev2.patch}"

## Enter Source Directory
if [ -d "mangos" ]; then
	cd mangos
	git pull -u
else
	echo "MaNGOS is not present; checking out Mangos"
	git clone git://github.com/mangos/mangos.git
	cd mangos
fi

## update Source
if [ -d "src/bindings/ScriptDev2" ]; then
	svn up src/bindings/ScriptDev2
else
	echo "ScriptDev2 is not present; checking out Mangos"
	mkdir src/bindings/ScriptDev2
	svn co https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2 src/bindings/ScriptDev2
	git apply src/bindings/ScriptDev2/patches/$SD2_PATCH
fi

if [ -d "objdir" ]; then
	rm -rf objdir
fi

## create build system
autoreconf --install --force || { echo "autoreconf died"; exit 1; }
aclocal || { echo "aclocal died"; exit 1; }
autoheader || { echo "autoheader died"; exit 1; }
autoconf || { echo "autoconf died"; exit 1; }
automake --add-missing || { echo "automake died"; exit 1; }
automake src/bindings/ScriptDev2/Makefile || { echo "2nd automake died"; exit 1; }

## configure MaNGOS
mkdir objdir || true
cd objdir
../configure \
	--prefix=$MANGOS_DESTDIR \
	--sysconfdir=$MANGOS_DESTDIR/etc \
	--enable-cli \
	--enable-ra \
	--datadir=$MANGOS_DESTDIR \
	|| { echo "configure failed!"; exit 1; }
make || { echo "Make failed!"; exit 1; }
#sudo make install || { echo "Make Install failed!"; exit 1; }

## Clean up
#make clean
#cd ..
#rm -r objdir

## Unset Bash Scripting
set +o errexit
set +o nounset
