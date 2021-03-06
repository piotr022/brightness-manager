#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
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
	{
		perror("file open");
		exit(1);
	}

	memset(line, 0, sizeof(line));
	if(fgets(line, sizeof(line-1), fd) == NULL) //at least one char must be 0 terminating char
		return NULL;

	fclose(fd);
	return smprintf("%s", line);
}

void overwrite_file_i(const char* base, const char* filename, int i_to_write)
{
	char* patch;
	FILE* const fd = fopen(patch = smprintf("%s/%s", base, filename), "w");
	free(patch);

	if(fd == NULL)
	{
		perror("file open");
		exit(1);
	}

	fprintf(fd, "%i", i_to_write);
	fclose(fd);
}

int main(int argc, char* argv[])
{
	char increase = 0;
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-i") == 0)
			increase = 1;
		else if(strcmp(argv[i], "-d") == 0)
			increase = -1;
	}
	if (increase == 0)
	{
		printf("insert -i parameter to increase\ninsert -d parameter to decrease\n");
		return 0;
	}

	char* const pc_brightness = read_file_line(pc_backlight_sys_patch, pc_backlight_brightness_filename);
	char* const pc_brightness_max = read_file_line(pc_backlight_sys_patch, pc_backlight_max_brightness_filename);
	char* const pc_brightness_actual = read_file_line(pc_backlight_sys_patch, pc_backlight_actual_brightness_filename);

	int i_brightness_max = atoi(pc_brightness_max);
	int i_brightness_actual = atoi(pc_brightness_actual);	
	int step = f_brightness_step_percentage * i_brightness_max;
	int min_value = f_brightness_minimum_percentage * i_brightness_max; 
	
	free(pc_brightness);
	free(pc_brightness_max);
	free(pc_brightness_actual);
	
	i_brightness_actual += step*increase;
	if(i_brightness_actual > i_brightness_max)
		i_brightness_actual = i_brightness_max;
	if(i_brightness_actual < min_value)
		i_brightness_actual = min_value;

	overwrite_file_i(pc_backlight_sys_patch, pc_backlight_brightness_filename, i_brightness_actual);
	
	return 0;
}

