;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

[BITS 64]

%INCLUDE "bmdev.asm"

NORMAL_EXIT_CODE equ 123456 ;same as in stdlib.h

;!!!FROM THIS LINE ----- should be deleted when we get normal stack
STACK_SIZE_IN_PAGES equ 1
;!!!UNTIL THIS LINE ----- should be deleted when we get normal stack

MEM_PAGE_SIZE equ 0x200000 ; same as in syscalls/memory.asm (baremetal src)

extern main
extern exit
extern __setjmp
extern __init
global __start
global __exit_buf

;this is the main entry point
__start:
	push rbx

;!!!FROM THIS LINE ----- should be deleted when we get normal stack
	mov rcx, STACK_SIZE_IN_PAGES
	call b_mem_allocate
	test rcx, rcx
	jnz stack_alloc_ok
	mov rax, 0x8000000000000001
	int3
stack_alloc_ok:
	mov rsi, rax
	mov rbx, rsp ;save original rsp

	lea rsp, [rax-8]
	mov rax, MEM_PAGE_SIZE
	mul rcx
	add rsp, rax ;set rsp to rax+rcx*MEM_PAGE_SIZE-8

	push rbx ;save original rsp
	push rsi ;save new stack's bottom (to free it later)
	push rcx ;save number of pages
;!!!UNTIL THIS LINE ----- should be deleted when we get normal stack

	call b_mem_get_free
	call b_mem_allocate
	test rcx, rcx
	jnz heap_alloc_ok
	mov rax, 0x8000000000000002
	int3
heap_alloc_ok:
	push rax
	push rcx
	test rcx, rcx
	jnz heap_ok
	mov rax, 1
	jmp end
heap_ok:
	mov rdi, rax
	mov rax, MEM_PAGE_SIZE
	mul rcx
	mov rsi, rax
	call __init

	mov rdi, __exit_buf ;first parameter of setjmp (env)
	call __setjmp ;setjmp is necessary for exit()
	test eax, eax
	jnz aftermain ;if longjmp was called

	call b_get_argc
	movzx rdi, al ;first parameter of main (argc)
	mov rbx, argv
	xor rax, rax
nextarg:
	cmp al, dil
	je nomorearg
	call b_get_argv
	mov [rbx], rsi
	add rbx, 8
	inc al
	jmp nextarg
nomorearg:	
	mov rsi, argv ;second parameter of main (argv)
	mov rdx, envp ;third parameter of main (envp)

	call main
	mov rdi, rax
	call exit ;proper exit

aftermain:
	cmp eax, NORMAL_EXIT_CODE ;setjmp returns NORMAL_EXIT_CODE in case of exit(0)
	jne end
	xor rax, rax
end:
	mov rdx, 0x00000000ffffffff
	and rdx, rax ;clear upper bits and save exit code to rdx

	pop rcx
	pop rax
	call b_mem_release

;!!!FROM THIS LINE ----- should be deleted when we get normal stack
	pop rcx ;number of pages
	pop rax ;stack's bottom
	pop rbx
	mov rsp, rbx ;restore original rsp
	call b_mem_release
;!!!UNTIL THIS LINE ----- should be deleted when we get normal stack

	mov rax, rdx

	pop rbx
	ret
argv:
	times 256 dq 0 ;we have at most 256 arguments
envp:
	times 1 dq 0 ;it always contains null
__exit_buf:
	times 7 dq 0 ;sizeof(jmp_buf) = 7*sizeof(long long)

;;;
