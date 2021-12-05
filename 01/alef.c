/*
 * Copyright (c) 2021 Síle Ekaterin Liszka All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

long parse_int(const char *str, size_t length) {
    // the longest possible signed long is 17+NUL characters
    long val = 0;
    errno = 0;

    for (size_t i = 0; i < length; i++) {
        val *= 10;
        if ((str[i] > '9') || (str[i] < '0')) {
            errno = EINVAL;
            return -1;
        }
        val += str[i] - '0';
    }

    return val;
}

int main(void) {
	FILE *data = fopen("data.txt", "r");
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	long previous = 0;
	int inc = 0;

	if (data == NULL) {
		printf("Unable to open data: %s\n", strerror(errno));
		return -errno;
	}

	while ((linelen = getline(&line, &linecap, data)) > 0) {
		long num = parse_int(line, linelen - 1);
		if (num > previous) {
			inc++;
		}
		previous = num;
	}

	printf("Depth has increased %d times.\n", inc - 1);

	return 0;
}
