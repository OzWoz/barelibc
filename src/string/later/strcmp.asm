;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

;/*
; * Written by J.T. Conklin <jtc@acorntoolworks.com>
; * Public domain.
; */

global strcmp

;int strcmp(const char *s1, const char *s2);

strcmp:
	;/*
	; * Align s1 to word boundary.
	; * Consider unrolling loop?
	; */
.Ls1align:
	test dil, 7
	je .Ls1aligned
	mov al, [rdi]
	inc rdi
	mov dl, [rsi]
	inc rsi
	test al, al
	je	.Ldone
	cmp dl, al
	je	.Ls1align
	jmp	.Ldone

	;/*
	; * Check whether s2 is aligned to a word boundry.  If it is, we
	; * can compare by words.  Otherwise we have to compare by bytes.
	; */
.Ls1aligned:
	test sil, 7
	jne .Lbyte_loop

	mov r8, 0x0101010101010101
	sub rdi, 8
	mov r9, 0x8080808080808080
	sub rsi, 8

	align 8
.Lword_loop:
	mov rax, [rdi+8]
	add rdi, 8
	mov rdx, [rsi+8]
	add rsi, 8
	cmp rax, rdx
	jne .Lbyte_loop
	sub rdx, 8
	not rax
	and rdx, rax
	test rdx, r9
	je .Lword_loop

	align 8
.Lbyte_loop:
	mov al, [rdi]
	inc rdi
	mov dl, [rsi]
	inc rsi
	test al, al
	je .Ldone
	cmp dl, al
	je .Lbyte_loop

.Ldone:
	movzx rax, al
	movzx rdx, dl
	sub rax, rdx
	ret

;;;
