#include <stdio.h>
#include <string.h>
#define NO_SMALL_CH_ERR  -2
#define	NOT_FIND				 -3

int des_summary_array[26];
int src_summary_array[26];

int des_summary(char* des)
{
		int 			i;
		char 			ch;
		int 			index;
		int				len;
		int				ch_count = 0;
		memset(des_summary_array, 0x00, sizeof(des_summary_array));
		len = strlen(des);
		for	(i = 0; i < len; i++){
				ch = 	*des++;
				index = ch - 'a';
				if (index < 0 || index >= 26) {
						return NO_SMALL_CH_ERR;	
				}
				
				if (des_summary_array[index] == 0) {
						ch_count++;	
				}
				
				des_summary_array[index]++;
		}
		
		return ch_count;
}

int src_summary(char *src, char * des, int des_count)
{	
		int i, des_len, src_len;
		char 				ch;
		char 			 *start;
		int 				index;
		int					src_count = 0;
		int					src_idx = 0;
		
		des_len = strlen(des);
		src_len = strlen(src);
		
		if (src_len < des_len) {
				return -1;	
		}
		memset(src_summary_array, 0x00, sizeof(src_summary_array));	
		start = src;
		for (i = 0; i < des_len; i++) {
				ch = *src++;
				index = ch - 'a';
				if (index < 0 || index >= 26) {
						return 	NO_SMALL_CH_ERR;
				}
				
				if (des_summary_array[index]) {
						src_summary_array[index]++;
						if 	(src_summary_array[index] == des_summary_array[index]) {
								src_count++;	
						}
				}
		}
		
		if (src_count == des_count) {
				return src_idx;	
		}
		
		src_idx++;
//		start++;
		for (; i < src_len; i++, src_idx++) {
				ch = *start++;
				index = ch - 'a';
				if (index < 0 || index >= 26) {
						return 	NO_SMALL_CH_ERR;
				}
				
				if (des_summary_array[index]) {
						if 	(src_summary_array[index] == des_summary_array[index]) {
								src_count--;	
						}
						src_summary_array[index]--;
				}
				
				ch = *src++;
				index = ch - 'a';
				if (index < 0 || index >= 26) {
						return 	NO_SMALL_CH_ERR;
				}
				
				if (des_summary_array[index]) {
						src_summary_array[index]++;
						if 	(src_summary_array[index] == des_summary_array[index]) {
								src_count++;	
						}
				}	
				
				if (src_count == des_count) {
						return src_idx;	
				}
		}
		
		return NOT_FIND;
}

int main(int argc, char *argv[]) 
{
		int 					ret;
		char				 *dest;
		char 				 *src; 
		int 					dst_count;
		int						sub_idx;
		if (argc < 3) {
				printf("usage: ./sub_full_permutation <src> <dst>\n");
				return -1;	
		}	
		
		src = argv[1];
		dest = argv[2];
		dst_count = des_summary(dest);
		if (dst_count <= 0) {
				printf("error des_summary return %d\n", dst_count);	
		}
		
		sub_idx = src_summary(src, dest, dst_count);
		
		if (sub_idx < 0) {
				printf("error src_summary return %d\n", sub_idx);	
				return -1;	
		}
		
		printf("sub_len:\t%d\n sub_data:\n%s\n", strlen(dest), src + sub_idx);
		return 0;
}