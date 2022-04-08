## This is a simple amaturelike build script
## Build the kernel
make i386_defconfig && 
make

# Get the compiled kernel
cp arch/x86/boot/bzImage .

## Build the initrd
# We get the source code of busybox and
# This will allow us to have some basic commande
# We compile it in CONFIG_STATIC
# like ls, cd, uname etc ... without the need
# of a libc

cd busybox
make distclean defconfig
sed -i "s/.*CONFIG_STATIC.*/CONFIG_STATIC=y/" .config
make busybox install

# Now we need to create the init process
# this is the first process lunch by the kernel
# this is where the kernel pass execution to
# user space application

# The init process is a simple bash script
cd _install
rm -f linuxrc
mkdir dev proc sys
echo '#!/bin/sh' > init
echo 'dmesg -n 1' >> init
echo 'mount -t devtmpfs none /dev' >> init
echo 'mount -t proc none /proc' >> init
echo 'mount -t sysfs none /sys' >> init
echo 'setsid cttyhack /bin/sh' >> init
chmod +x init

# Pack everything and create the initrd
find . | cpio -R root:root -H newc -o | gzip > ../../initrd_rootfs

# Back to root of source tree
cd ../../

# Build the Bootloader

INPUT="./boot/bootloader.asm"
OUTPUT="gaiar_art_sys_v0000"
KERN="./bzImage"
RD="./initrd_rootfs"

#size of kern + ramdisk
K_SZ=`stat -c %s $KERN`
R_SZ=`stat -c %s $RD`

# padding to make it up to a sector
K_PAD=$((512 - $K_SZ % 512))

# -D option is used to pass initRdSizeDef to
# bootloader.asm befor compiling
# Hey, thinking of making it up to GAS
nasm -o $OUTPUT -D initRdSizeDef=$R_SZ $INPUT

cat $KERN >> $OUTPUT

# Fill with zeros until it is up to a sector
if [[ $K_PAD -lt 512 ]]; then
    dd if=/dev/zero bs=1 count=$K_PAD >> $OUTPUT
fi

cat $RD >> $OUTPUT


# To test run

qemu-system-i386 gaiar_art_sys_v0000
