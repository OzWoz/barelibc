;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

[BITS 64]

global __setjmp 
global __longjmp

;int __setjmp(jmp_buf *env)
__setjmp:
	mov [PARAM1+0x00], rbx
	mov [PARAM1+0x08], rbp
	mov [PARAM1+0x10], r12
	mov [PARAM1+0x18], r13
	mov [PARAM1+0x20], r14
	mov [PARAM1+0x28], r15
	mov [PARAM1+0x30], rsp
	xor rax, rax
	ret

;int __longjmp(jmp_buf *env, int val)
__longjmp:
	mov rbx, [PARAM1+0x00]
	mov rbp, [PARAM1+0x08]
	mov r12, [PARAM1+0x10]
	mov r13, [PARAM1+0x18]
	mov r14, [PARAM1+0x20]
	mov r15, [PARAM1+0x28]
	mov rsp, [PARAM1+0x30]
	mov eax, 1
	test PARAM2_32, PARAM2_32
	cmovnz eax, PARAM2_32
	ret

;;;
