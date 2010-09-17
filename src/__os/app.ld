OUTPUT_FORMAT("binary")
OUTPUT_ARCH("i386:x86-64")
ENTRY(__start)
SECTIONS
{
	. = 0x200000;

	.text ALIGN(4096) :
	{
		*(.text*)
		*(.gnu.linkonce.t*)
	}

	.rodata ALIGN(4096) :
	{
		*(.rodata*)
		*(.gnu.linkonce.r*)
	}

	.data ALIGN(4096) :
	{
		__start_ctors = .;
        *(.ctor*)
        __end_ctors = .;

		__start_dtors = .;
        *(.dtor*)
        __end_dtors = .;

		*(.data*)
		*(.gnu.linkonce.d*)

		QUAD(ADDR(.bss)+SIZEOF(.bss))
	}

	.bss ALIGN(4096) :
	{
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
	}

    /DISCARD/ :
    {
    	*(.comment)
    	*(.eh_frame)
    }
}

/***/
