LINUX_TOOLCHAIN_PATH = /home/autobuild/tools/win32

PathToCairo = contrib/sdk/sources/cairo

install libcairo2.a cairo2.dll clean:
	$(MAKE) -C $(PathToCairo) $@

kos-cairo-dev: libcairo2.a cairo2.dll
	mkdir -p $@$(LINUX_TOOLCHAIN_PATH)/include

	cp -f $(PathToCairo)/src/*.h $@$(LINUX_TOOLCHAIN_PATH)/include
	cp -f $(PathToCairo)/*.a $@$(LINUX_TOOLCHAIN_PATH)/mingw32/lib

	dpkg-deb --build $@ $@.deb
