cmd_/home/djp952/external-kernelheaders/linux-4.4.5//include/linux/caif/.install := /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/caif ./include/uapi/linux/caif caif_socket.h if_caif.h; /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/caif ./include/linux/caif ; /bin/bash scripts/headers_install.sh /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/caif ./include/generated/uapi/linux/caif ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/caif/$$F; done; touch /home/djp952/external-kernelheaders/linux-4.4.5//include/linux/caif/.install