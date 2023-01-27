sudo pacman -S git gcc xorriso nasm edk2-ovmf mtools qemu virt-manager dnsmasq vde2 bridge-utils openbsd-netcat base-devel bison flex gmp libmpc mpfr texinfo
sudo cp /usr/share/ovmf/x64/OVMF.fd OVMF.fd
git clone https://gitlab.com/bztsrc/bootboot
cd ./bootboot/mkbootimg
make