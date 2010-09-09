;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

[BITS 64]

;MSB                                                          LSB
;|                                                              |
;sccccccccccccccccccccccccccccccctttttttttttttttttttttttttttttttt
;||                             ||                              |
;|\------------v----------------/\----------------v-------------/
;|             |                                  |
;spinlock    counter                    owner (threadid+1 or 0)

; lower 32 bit is thread id + 1 (or 0 if not locked), the uppermost 1 bit is spinlock, the other 31 bit between them is counter

global reentrant_mutex_lock
global reentrant_mutex_trylock
global reentrant_mutex_unlock
extern thread_current_id

;reentrant_mutex_t must be 64 bit wide and volatile

;void reentrant_mutex_lock(reentrant_mutex_t *m);
;m: rdi
reentrant_mutex_lock:
	call thread_current_id ;eax contains threadid
	inc eax ;+1
	xor rcx, rcx
	not rcx
retry_spin_lock: ;acquire spinlock
	bt qword [rdi], 63
	jc retry_spin_lock
	lock bts qword [rdi], 63
	jc retry_spin_lock
	;we locked spinlock now
	mov rdx, [rdi] ;mov mutex to rdx
	test edx, edx ;test if lower 32 bit is 0
	jz ok_copy ;it's not locked
	cmp edx, eax ;someone has locked it, check if it was this thread
	je ok
	btr qword [rdi], 63 ;someone else has locked it
wait_until_empty:
	test qword [rdi], rcx
	jnz wait_until_empty
	jmp retry_spin_lock ;we retry the whole procedure
ok_copy:
	mov edx, eax ;we copy our threadid to lower 32 bit
ok:	
	mov rcx, 0x0000000100000000
	add rdx, rcx ;increment counter (it will crash after 2billion locks by the same thread..)
	btr rdx, 63 ;release spinlock
	mov [rdi], rdx ;copy back to memory
	ret

;unsigned reentrant_mutex_trylock(reentrant_mutex_t *m);

;m: rdi
;returns 1 if successful, 0 if failed
reentrant_mutex_trylock:
	call thread_current_id ;eax contains threadid
	inc eax ;+1
retry_spin_lock_2: ;acquire spinlock
	bt qword [rdi], 63
	jc retry_spin_lock_2
	lock bts qword [rdi], 63
	jc retry_spin_lock_2
	;we locked spinlock now
	mov rdx, [rdi] ;mov mutex to rdx
	test edx, edx ;test if lower 32 bit is 0
	jz ok_copy_2 ;it's not locked
	cmp edx, eax ;someone has locked it, check if it was this thread
	je ok_2
	btr qword [rdi], 63 ;someone else has locked it
	xor rax, rax
	ret
ok_copy_2:
	mov edx, eax ;we copy our threadid to lower 32 bit
ok_2:	
	mov rcx, 0x0000000100000000
	add rdx, rcx ;increment counter (it will crash after 2billion locks by the same thread..)
	btr rdx, 63 ;release spinlock
	mov [rdi], rdx ;copy back to memory
	mov rax, 1
	ret

;void reentrant_mutex_unlock(reentrant_mutex_t *m);
;m: rdi
reentrant_mutex_unlock:
	bt qword [rdi], 63 ;acquire spinlock
	jc reentrant_mutex_unlock
	lock bts qword [rdi], 63
	jc reentrant_mutex_unlock
	;we locked spinlock now
	mov rdx, [rdi] ;mov mutex to rdx
	mov rcx, 0x0000000100000000
	sub rdx, rcx ;decrement counter (it is assumed that we previosly locked it..)
	mov rcx, 0x7fffffff00000000
	test rdx, rcx ;test if counter is 0
	jnz more
	xor edx, edx ;if counter is 0 then we clear threadid from mutex
more:
	btr rdx, 63 ;release spinlock
	mov [rdi], rdx ;copy back to memory
	ret

;;;
