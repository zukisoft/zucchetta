cmd_/home/djp952/external-kernelheaders/linux-4.4.5//include/linux/spi/.install := /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/spi ./include/uapi/linux/spi spidev.h; /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/spi ./include/linux/spi ; /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/spi ./include/generated/uapi/linux/spi ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/spi/$$F; done; touch /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/spi/.install