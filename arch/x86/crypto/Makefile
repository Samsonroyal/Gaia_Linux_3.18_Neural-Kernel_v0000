#
# Arch-specific CryptoAPI modules.
#

avx_supported := $(call as-instr,vpxor %xmm0$(comma)%xmm0$(comma)%xmm0,yes,no)
avx2_supported := $(call as-instr,vpgatherdd %ymm0$(comma)(%eax$(comma)%ymm1\
				$(comma)4)$(comma)%ymm2,yes,no)

obj-$(CONFIG_CRYPTO_AES_586) += aes-i586.o

aes-i586-y := aes-i586-asm_32.o aes_glue.o
