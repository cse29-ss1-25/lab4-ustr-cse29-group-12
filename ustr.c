#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	if (start < 0 || end <= start || start >= s.codepoints || end > s.codepoints) {
		char* empty = "";
		UStr u = new_ustr(empty);
		return u;
	}
	if(s.is_ascii == 1) {
		char* substring = malloc(end - start + 1);
		for (int i = 0; i < end - start; i++) {
			substring[i] = s.contents[i + start];
		}
		UStr u = new_ustr(substring);
		free(substring);
		return u;
	}
	int count = 0;
	int cp_start = 0;
	int cp_end = 0;
	int i = 0;
	while(s.contents[i] != '\0') {
		if (count == start) {
			cp_start = i;
		}
		if (count == end) {
			cp_end = i;
		}
		char c = s.contents[i];

		if ((c & 0x80) == 0x00) {
            		i += 1;
        	} 
		else if ((c & 0xE0) == 0xC0) {
            		i += 2;
        	} 
		else if ((c & 0xF0) == 0xE0) {
            		i += 3;
        	} 
		else if ((c & 0xF8) == 0xF0) {
            		i += 4;
		}
		count++;
	}
	char* substring = malloc(cp_end - cp_start + 1);
        for (int i = 0; i < cp_end - cp_start; i++) {
                substring[i] = s.contents[i + cp_start];
        }
        UStr u = new_ustr(substring);
        return u; 
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this

}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

}

void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

