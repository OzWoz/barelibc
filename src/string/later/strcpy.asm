;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

;/*
; * Written by J.T. Conklin <jtc@acorntoolworks.com>
; * Public domain.
; */

;/*
; * This strcpy implementation copies a byte at a time until the
; * source pointer is aligned to a word boundary, it then copies by
; * words until it finds a word containing a zero byte, and finally
; * copies by bytes until the end of the string is reached.
; *
; * While this may result in unaligned stores if the source and
; * destination pointers are unaligned with respect to each other,
; * it is still faster than either byte copies or the overhead of
; * an implementation suitable for machines with strict alignment
; * requirements.
; */

global strcpy

;char *strcpy(char *s1, const char *s2);
strcpy:
	mov rax, rdi
	mov r8, 0x0101010101010101
	mov r9, 0x8080808080808080

	;/*
	; * Align source to a word boundary.
	; * Consider unrolling loop?
	; */
.Lalign:
	test sil, 7
	je .Lword_aligned
	mov dl, [rsi]
	inc rsi
	mov [rdi], dl
	inc rdi
	test dl, dl
	jne .Lalign
	ret

	align 8
.Lloop:
	mov [rdi], rdx
	add rdi, 8
.Lword_aligned:
	mov rdx, [rsi]
	mov rcx, rdx
	add rsi, 8
	sub rcx, r8
	test rcx, r9
	je .Lloop

	;/*
	; * In rare cases, the above loop may exit prematurely. We must
	; * return to the loop if none of the bytes in the word equal 0.
	; */

	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 1st byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 2nd byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 3rd byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 4th byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 5th byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 6th byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 7th byte == 0? */
	je .Ldone

	shr rdx, 8
	mov [rdi], dl
	inc rdi
	test dl, dl ;/* 8th byte == 0? */
	je .Ldone

.Ldone:
	ret

;;;
