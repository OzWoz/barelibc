// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

int main(void)
{
	*(char *)(0xffffffffffffffffULL) = 0;
  	return 0;
}

///
