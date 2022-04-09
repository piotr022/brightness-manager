#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "config.h"

#define MAX_READ_BUFFOR_SIZE 512

char* smprintf(char* fmt, ...)
{
   va_list fmtargs;
   char *ret;
   int len;

   va_start(fmtargs, fmt);
   len = vsnprintf(NULL, 0, fmt, fmtargs);
   va_end(fmtargs);

   ret = malloc(++len);
   if (ret == NULL) {
      perror("malloc");
      exit(1);
   }

   va_start(fmtargs, fmt);
   vsnprintf(ret, len, fmt, fmtargs);
   va_end(fmtargs);

   return ret;
}

char* read_file_line(const char* base, const char* filename)
{
	char* patch;
	char  line[MAX_READ_BUFFOR_SIZE];
	FILE* const fd = fopen(patch = smprintf("%s/%s", base, filename), "r");
	free(patch);
	
	if (fd == NULL)
		return NULL;
	
	if(fgets(line, sizeof(line-1), fd) == NULL) //at least one char must be 0 terminating char
		return NULL;

	fclose(fd);
	return smprintf("%s", line);
}

int main(int argc, char* argv[])
{
	char* const pc_brightness = read_file_line(pc_backlight_sys_patch, pc_backlight_brightness_filename);
	char* const pc_brightness_max = read_file_line(pc_backlight_sys_patch, pc_backlight_max_brightness_filename);
	char* const pc_brightness_actual = read_file_line(pc_backlight_sys_patch, pc_backlight_actual_brightness_filename);
	
	int i_brightness = atoi(pc_brightness);
	int i_brightness_max = atoi(pc_brightness_max);
	int i_brightness_actual = atoi(pc_brightness_actual);
	
	free(pc_brightness);
	free(pc_brightness_max);
	free(pc_brightness_actual);

	printf("brightness: %i\nmaximum: %i\nactual: %i\n", i_brightness, i_brightness_max, i_brightness_actual);
	
	
	return 0;
}

