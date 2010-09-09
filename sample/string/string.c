// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
	char s1[100], s2[100];

	assert(strcmp("apple", "pie") < 0);
	assert(strcmp("foo", "bar") > 0);
	assert(strcmp("foo", "bar") > 0);
	assert(strcmp("foobar", "foobar") == 0);
	assert(strcmp("foobar ", "foobar") > 0);

	strcpy(s1, "hello");
	assert(strcmp(s1, "hello") == 0);

	strcpy(s2, "world");
	assert(strcmp(s2, "world") == 0);
	assert(strcmp(s1, s2) < 0);
	strcpy(s1, s2);
	assert(strcmp(s1, s2) == 0);
	puts("all tests ok\n");
	return 0;
}

///

