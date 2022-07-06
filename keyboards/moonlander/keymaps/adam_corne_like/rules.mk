COMBO_ENABLE = yes

# Enabling link-time optimization saves about 3 kilobytes.
# https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
EXTRAFLAGS += -flto

SRC += swapper.c
SRC += oneshot.c
