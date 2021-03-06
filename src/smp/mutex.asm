;BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

[BITS 64]

extern get_thread_id

global mutex_lock
global mutex_unlock

;mutex_t must be 64 bit wide and volatile

;void mutex_lock(mutex_t *m);
mutex_lock:
	bt qword [PARAM1], 0
	jc mutex_lock
	lock bts qword [PARAM1], 0
	jc mutex_lock
	ret

;unsigned mutex_trylock(mutex_t *m);
;returns 1 if successful, 0 if failed
mutex_trylock:
	lock bts qword [PARAM1], 0
	jc fail
	mov rax, 1
	ret
fail:
	xor rax, rax
	ret

;void mutex_unlock(mutex_t *m);
mutex_unlock:
	lock btr qword [PARAM1], 0
	ret

;;;
