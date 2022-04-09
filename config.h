#ifndef CONFIG_H
#define CONFIG_H

const char pc_backlight_sys_patch[] 						= "/sys/class/backlight/intel_backlight";
const char pc_backlight_brightness_filename[] 			= "brightness";
const char pc_backlight_actual_brightness_filename[] 	= "actual_brightness";
const char pc_backlight_max_brightness_filename[] 		= "max_brightness";

const float f_brightness_step_percentage 					= 0.1;
const float f_brightness_minimum_percentage 				= 0.05;

#endif
