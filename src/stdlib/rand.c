// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <smp.h>

#define N 4096
#define A 18782UL
#define R 0xfffffffeUL

#define m_q __rand_m_state
#define m_carry __rand_m_state[N]
#define m_index __rand_m_state[N+1]

static volatile unsigned __rand_m_state[N+2];
static mutex_t __rand_mutex = 0;

void srand(unsigned seed)
{
	unsigned i;
	mutex_lock(&__rand_mutex);
	m_q[0] = seed;
	for (i = 1; i < N; ++i) {
		m_q[i] = 1812433253UL * (m_q[i - 1] ^ (m_q[i - 1] >> 30)) + i;
	}
	m_carry = m_q[N-1] % 61137367UL;
	m_index = N - 1;
	mutex_unlock(&__rand_mutex);
}

unsigned urand(void)
{
	unsigned long long temp;
	unsigned x, ret;

	mutex_lock(&__rand_mutex);

	m_index = (m_index + 1) & 4095;
	temp = (unsigned long long)A * (unsigned long long)m_q[m_index] + (unsigned long long)m_carry;
	m_carry = (unsigned)(temp >> 32);
	x = (unsigned)temp + m_carry;

	if (x < m_carry)
	{
		x++;
		m_carry++;
	}
	ret = m_q[m_index] = R - x;

	mutex_unlock(&__rand_mutex);

	return ret;
}

int rand(void)
{
	return (int)(urand()>>1);
}

///
