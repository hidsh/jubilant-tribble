APP_DIR = ~/mise-work/zmk-firmware/zmk/app
CONFIG_DIR = config
SRCS = $(shell find $(CONFIG_DIR) -type f)
TARG = ../zmk/app/build/zephyr/zmk.uf2

.PHONY: build clean

build: $(TARG)

$(TARG): $(SRCS)
	west build -p -b seeeduino_xiao_ble -- -DSHIELD=test0

# clean:
# 	rm -fr
