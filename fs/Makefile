obj-y :=	open.o read_write.o file_table.o super.o \
		char_dev.o stat.o exec.o pipe.o namei.o fcntl.o \
		ioctl.o readdir.o select.o dcache.o inode.o \
		attr.o bad_inode.o file.o filesystems.o namespace.o \
		seq_file.o xattr.o libfs.o fs-writeback.o \
		pnode.o splice.o sync.o utimes.o \
		stack.o fs_struct.o statfs.o fs_pin.o

ifeq ($(CONFIG_BLOCK),y)
obj-y +=	buffer.o block_dev.o direct-io.o mpage.o
else
obj-y +=	no-block.o
endif

obj-$(CONFIG_PROC_FS) += proc_namespace.o

obj-y				+= notify/
obj-$(CONFIG_EPOLL)		+= eventpoll.o
obj-$(CONFIG_ANON_INODES)	+= anon_inodes.o
obj-$(CONFIG_SIGNALFD)		+= signalfd.o
obj-$(CONFIG_TIMERFD)		+= timerfd.o
obj-$(CONFIG_EVENTFD)		+= eventfd.o
obj-$(CONFIG_AIO)               += aio.o
obj-$(CONFIG_FILE_LOCKING)      += locks.o
obj-$(CONFIG_COMPAT)		+= compat.o compat_ioctl.o
obj-$(CONFIG_BINFMT_AOUT)	+= binfmt_aout.o
obj-$(CONFIG_BINFMT_EM86)	+= binfmt_em86.o
obj-$(CONFIG_BINFMT_MISC)	+= binfmt_misc.o
obj-$(CONFIG_BINFMT_SCRIPT)	+= binfmt_script.o
obj-$(CONFIG_BINFMT_ELF)	+= binfmt_elf.o
obj-$(CONFIG_COMPAT_BINFMT_ELF)	+= compat_binfmt_elf.o
obj-$(CONFIG_BINFMT_ELF_FDPIC)	+= binfmt_elf_fdpic.o
obj-$(CONFIG_BINFMT_SOM)	+= binfmt_som.o
obj-$(CONFIG_BINFMT_FLAT)	+= binfmt_flat.o

obj-$(CONFIG_FS_MBCACHE)	+= mbcache.o
obj-$(CONFIG_FS_POSIX_ACL)	+= posix_acl.o
obj-$(CONFIG_COREDUMP)		+= coredump.o
obj-$(CONFIG_SYSCTL)		+= drop_caches.o

obj-$(CONFIG_FHANDLE)		+= fhandle.o

obj-y				+= quota/

obj-$(CONFIG_PROC_FS)		+= proc/
obj-$(CONFIG_KERNFS)		+= kernfs/
obj-$(CONFIG_SYSFS)		+= sysfs/
obj-y				+= devpts/

obj-$(CONFIG_PROFILING)		+= dcookies.o
 
# Do not add any filesystems before this line
obj-$(CONFIG_EXT4_FS)		+= ext4/
obj-$(CONFIG_JBD2)		+= jbd2/
obj-y				+= ramfs/
obj-$(CONFIG_NLS)		+= nls/
obj-$(CONFIG_XFS_FS)		+= xfs/
obj-$(CONFIG_DEBUG_FS)		+= debugfs/
obj-y				+= exofs/ # Multiple modules
