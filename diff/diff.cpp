#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXLEN = 100;
#define max(x, y) ((x) > (y) ? (x) : (y))

char s1[MAXLEN][MAXLEN], s2[MAXLEN][MAXLEN];
int s1_len = 0, s2_len = 0;

void print_diff()
{
	int f[MAXLEN][MAXLEN];
	f[0][0] = 0;
	for (int i = 1; i <= s1_len; ++i) {
		for (int j = 1; j <= s2_len; ++j) {
			char *c1 = s1[i - 1];
			char *c2 = s2[j - 1];
			if (0 == strcmp(c1, c2)) {
				f[i][j] = f[i - 1][j - 1] + 1;
			} else {
				f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			}
		}
	}
	
	bool s1_common[MAXLEN] = { false };
	bool s2_common[MAXLEN] = { false };
	int s1_pos = s1_len;
	int s2_pos = s2_len;
	while (s1_pos + s2_pos > 0) {
		if (0 == strcmp(s1[s1_pos - 1], s2[s2_pos - 1])) {
			s1_common[s1_pos - 1] = s2_common[s2_pos - 1] = true;
			--s1_pos;
			--s2_pos;
		} else if (f[s1_pos - 1][s2_pos] > f[s1_pos][s2_pos - 1]) {
			--s1_pos; 
		} else {
			--s2_pos;
		}
	}
	
	s1_pos = s2_pos = 0;
	while (s1_pos < s1_len && s2_pos < s2_len) {
		
		if (s1_common[s1_pos] && s2_common[s2_pos]) {
			puts("----");
			while (s1_common[s1_pos] && s2_common[s2_pos]) {
				++s1_pos;
				++s2_pos;
			}
			continue;
		}
		
		if (false == s1_common[s1_pos]) {
			puts("<<");
			while (false == s1_common[s1_pos]) {
				puts(s1[s1_pos]);
				++s1_pos;
			}
		}
		if (false == s2_common[s2_pos]) {
			puts(">>");
			while (false == s2_common[s2_pos]) {
				puts(s2[s2_pos]);
				++s2_pos;
			}
		}
	}
	
	if (s1_pos < s1_len)  {
		puts("<<");
		while (s1_pos < s1_len) {
			puts(s1[s1_pos]);
		}
	}

	if (s2_pos < s2_len)  {
		puts(">>");
		while (s2_pos < s2_len) {
			puts(s2[s2_pos]);
		}
	}
	
}

int main(int argc, char *argv[]) 
{
	if (argc < 3) {
		puts("no original or new file");
		return 0;
	}
	FILE *f1 = fopen(argv[1], "r");
	while (fgets(s1[s1_len++], MAXLEN, f1)) {
		s1[s1_len - 1][strlen(s1[s1_len - 1]) - 1] = 0;
	}
	FILE *f2 = fopen(argv[2], "r");
	while (fgets(s2[s2_len++], MAXLEN, f2)) {
		s2[s2_len - 1][strlen(s2[s2_len - 1]) - 1] = 0;
	}
	
	print_diff();
	return 0;
}
