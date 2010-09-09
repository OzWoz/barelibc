;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

[BITS 64]

extern get_thread_id

global mutex_lock
global mutex_unlock

;mutex_t must be 64 bit wide and volatile

;void mutex_lock(mutex_t *m);
;m: rdi
mutex_lock:
	bt qword [rdi], 0
	jc mutex_lock
	lock bts qword [rdi], 0
	jc mutex_lock
	ret

;unsigned mutex_trylock(mutex_t *m);
;m: rdi
;returns 1 if successful, 0 if failed
mutex_trylock:
	lock bts qword [rdi], 0
	jc fail
	mov rax, 1
	ret
fail:
	xor rax, rax
	ret

;void mutex_unlock(mutex_t *m);
;m: rdi
mutex_unlock:
	btr qword [rdi], 0
	ret

;;;
