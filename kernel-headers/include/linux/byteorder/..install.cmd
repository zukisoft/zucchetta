cmd_/home/djp952/external-kernelheaders/linux-4.4.5//include/linux/byteorder/.install := /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/byteorder ./include/uapi/linux/byteorder big_endian.h little_endian.h; /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/byteorder ./include/linux/byteorder ; /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/byteorder ./include/generated/uapi/linux/byteorder ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/byteorder/$$F; done; touch /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/byteorder/.install
