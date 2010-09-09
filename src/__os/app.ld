OUTPUT_FORMAT("binary")
OUTPUT_ARCH("i386:x86-64")
ENTRY(__start)
SECTIONS
{
	.text 0x0000000000200000 : { *(.text) }
	.data ALIGN(0x08) : { *(.data .rodata) QUAD(ADDR(.bss)+SIZEOF(.bss)) }
	.bss ALIGN(0x08) : { *(.bss) }
}
