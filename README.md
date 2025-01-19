# zlib for kolibrios

This is zlib from kolibrios repository.

## Build

### Depends

+ newlib
+ pixman
+ freetype
+ zlib
+ libpng

install depends:
```
sudo mkdir -p /etc/apt/keyrings
sudo curl https://git.kolibrios.org/api/packages/Egor00f/debian/repository.key -o /etc/apt/keyrings/gitea-Egor00f.asc
echo "deb [signed-by=/etc/apt/keyrings/gitea-Egor00f.asc] https://git.kolibrios.org/api/packages/Egor00f/debian bookworm main" | sudo tee -a /etc/apt/sources.list.d/gitea.list
sudo apt update
sudo apt install kos32-gcc kos-newlib kos-pixman-dev kos-freetype-dev kos-zlib-dev kos-libpng-dev
```

### Build targets

static library:
```
make libcairo2.a
```

shared library:
```
make cairo2.dll
```

package:
```
make kos-cairo-dev
```
