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
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *data = fopen("data.txt", "r");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen = 0;

    long forward = 0;
    long depth = 0;

    if (data == NULL) {
    	printf("Unable to open data: %s\n", strerror(errno));
    	return -errno;
    }

    while ((linelen = getline(&line, &linecap, data)) > 0) {
	    char *direction;
	    int units;
	    sscanf(line, "%s %d", direction, &units);

	    if (!strcmp(direction, "forward")) {
		    forward += units;
	    } else if (!strcmp(direction, "up")) {
		    depth -= units;
	    } else if (!strcmp(direction, "down")) {
		    depth += units;
	    } else {
		    fprintf(stderr, "Invalid direction: %s\n", direction);
		    return -EINVAL;
	    }
    }

    printf("Moved %ld units forward, depth is %ld; multiplied is %ld.\n", forward, depth, forward * depth);

    return 0;
}
