;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

[BITS 64]

global __setjmp 
global __longjmp

;int __setjmp(jmp_buf *env)
;env: rdi
__setjmp:
	mov [rdi+0x00], rbx
	mov [rdi+0x08], rbp
	mov [rdi+0x10], r12
	mov [rdi+0x18], r13
	mov [rdi+0x20], r14
	mov [rdi+0x28], r15
	mov [rdi+0x30], rsp
	xor rax, rax
	ret

;int __longjmp(jmp_buf *env, int val)
;env: rdi, val: esi
__longjmp:
	mov rbx, [rdi+0x00]
	mov rbp, [rdi+0x08]
	mov r12, [rdi+0x10]
	mov r13, [rdi+0x18]
	mov r14, [rdi+0x20]
	mov r15, [rdi+0x28]
	mov rsp, [rdi+0x30]
	mov eax, 1
	test esi, esi
	cmovnz eax, esi
	ret

;;;
