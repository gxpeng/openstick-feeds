/*
 * LED monitor For MF32(4 battery leds)
 * v2023.10.15 By Phang
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>

#define MAX_BUFFER_SIZE 4096

char* catFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(fileSize + 1);
    fread(content, sizeof(char), fileSize, file);
    content[fileSize] = '\0';

    fclose(file);
    return content;
}

char* runShell(const char* command) {
    char* buffer = NULL;
    FILE* fp = popen(command, "r");
    
    if (fp == NULL) {
        perror("popen");
        return NULL;
    }
    
    buffer = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
    if (buffer == NULL) {
        perror("malloc");
        pclose(fp);
        return NULL;
    }
    
    size_t bytesRead = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, fp);
    if (bytesRead == 0) {
        if (ferror(fp)) {
            perror("fread");
        }
    } else {
		if (buffer[bytesRead - 1] == '\n') {
            buffer[bytesRead - 1] = '\0';
        } else {
			buffer[bytesRead] = '\0';
		}
		return buffer;
    }

    pclose(fp);
}

bool led_set_attr(const char* ledName, const char* attrName, const char* value) {
    char command[256];
	char *re = NULL;
	sprintf(command, "echo %s >/sys/class/leds/%s/%s", value, ledName, attrName);
	re = runShell(command);
	if( re ){
		free(re);
		return true;
	} else{
		return false;
	}
}

bool led_on(const char* ledName) {
    if (led_set_attr(ledName, "trigger", "none") && led_set_attr(ledName, "brightness", "1")) {
        return true;
    } else {
        return false;
    }
}

bool led_off(const char* ledName) {
    if (led_set_attr(ledName, "trigger", "none") && led_set_attr(ledName, "brightness", "0")) {
        return true;
    } else {
        return false;
    }
}

bool led_timer(const char* ledName, const char* delayOn, const char* delayOff) {
    if (led_set_attr(ledName, "trigger", "timer") && 
        led_set_attr(ledName, "delay_on", delayOn) && 
        led_set_attr(ledName, "delay_off", delayOff)) {
        return true;
    } else {
        return false;
    }
}

void led_set_bat(const char* led1, const char* led2, const char* led3, const char* led4, const char* delayOn, const char* delayOff) {

	char *status_bat_1 = NULL;
    char *delay_on_1 = NULL;
    char *delay_off_1 = NULL;

    status_bat_1 = runShell("cat /sys/class/leds/bat_1/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_bat_1 && strcmp(status_bat_1, "timer") == 0) {
		delay_on_1 = runShell("cat /sys/class/leds/bat_1/delay_on");
		delay_off_1 = runShell("cat /sys/class/leds/bat_1/delay_off");
    } else {
		char *brightness_1 = runShell("cat /sys/class/leds/bat_1/brightness");
		if (strcmp(brightness_1, "1") == 0) {
			status_bat_1 = "on";
		} else {
			status_bat_1 = "off";
		}
    }

	char *status_bat_2 = NULL;
    char *delay_on_2 = NULL;
    char *delay_off_2 = NULL;

    status_bat_2 = runShell("cat /sys/class/leds/bat_2/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_bat_2 && strcmp(status_bat_2, "timer") == 0) {
		delay_on_2 = runShell("cat /sys/class/leds/bat_2/delay_on");
		delay_off_2 = runShell("cat /sys/class/leds/bat_2/delay_off");
    } else {
		char *brightness_2 = runShell("cat /sys/class/leds/bat_2/brightness");
		if (strcmp(brightness_2, "1") == 0) {
			status_bat_2 = "on";
		} else {
			status_bat_2 = "off";
		}
    }

	char *status_bat_3 = NULL;
    char *delay_on_3 = NULL;
    char *delay_off_3 = NULL;

    status_bat_3 = runShell("cat /sys/class/leds/bat_3/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_bat_3 && strcmp(status_bat_3, "timer") == 0) {
		delay_on_3 = runShell("cat /sys/class/leds/bat_3/delay_on");
		delay_off_3 = runShell("cat /sys/class/leds/bat_3/delay_off");
    } else {
		char *brightness_3 = runShell("cat /sys/class/leds/bat_3/brightness");
		if (strcmp(brightness_3, "1") == 0) {
			status_bat_3 = "on";
		} else {
			status_bat_3 = "off";
		}
    }

	char *status_bat_4 = NULL;
    char *delay_on_4 = NULL;
    char *delay_off_4 = NULL;

    status_bat_4 = runShell("cat /sys/class/leds/bat_4/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_bat_4 && strcmp(status_bat_3, "timer") == 0) {
		delay_on_4 = runShell("cat /sys/class/leds/bat_4/delay_on");
		delay_off_4 = runShell("cat /sys/class/leds/bat_4/delay_off");
    } else {
		char *brightness_4 = runShell("cat /sys/class/leds/bat_4/brightness");
		if (strcmp(brightness_4, "1") == 0) {
			status_bat_4 = "on";
		} else {
			status_bat_4 = "off";
		}
    }


    if (led1 && strcmp(led1, "timer") == 0) {
        if (strcmp(led1, status_bat_1) != 0 || strcmp(delayOn, delay_on_1) != 0 || strcmp(delayOff, delay_off_1) != 0) {
            led_timer("bat_1", delayOn, delayOff);
        }
    } else if (led1 && strcmp(led1, status_bat_1) != 0) {
        if (strcmp(led1, "on") == 0) {
            led_on("bat_1");
        } else if (strcmp(led1, "off") == 0) {
            led_off("bat_1");
        }
    }

    if (led2 && strcmp(led2, "timer") == 0) {
        if (strcmp(led2, status_bat_2) != 0 || strcmp(delayOn, delay_on_2) != 0 || strcmp(delayOff, delay_off_2) != 0) {
            led_timer("bat_2", delayOn, delayOff);
        }
    } else if (led2 && strcmp(led2, status_bat_2) != 0) {
        if (strcmp(led2, "on") == 0) {
            led_on("bat_2");
        } else if (strcmp(led2, "off") == 0) {
            led_off("bat_2");
        }
    }

    if (led3 && strcmp(led3, "timer") == 0) {
        if (strcmp(led3, status_bat_3) != 0 || strcmp(delayOn, delay_on_3) != 0 || strcmp(delayOff, delay_off_3) != 0) {
            led_timer("bat_3", delayOn, delayOff);
        }
    } else if (led3 && strcmp(led3, status_bat_3) != 0) {
        if (strcmp(led3, "on") == 0) {
            led_on("bat_3");
        } else if (strcmp(led3, "off") == 0) {
            led_off("bat_3");
        }
    }

    if (led4 && strcmp(led4, "timer") == 0) {
        if (strcmp(led4, status_bat_4) != 0 || strcmp(delayOn, delay_on_4) != 0 || strcmp(delayOff, delay_off_4) != 0) {
            led_timer("bat_4", delayOn, delayOff);
        }
    } else if (led4 && strcmp(led4, status_bat_4) != 0) {
        if (strcmp(led4, "on") == 0) {
            led_on("bat_4");
        } else if (strcmp(led4, "off") == 0) {
            led_off("bat_4");
        }
    }

	free(status_bat_1);
    free(delay_on_1);
    free(delay_off_1);

	free(status_bat_2);
    free(delay_on_2);
    free(delay_off_2);

	free(status_bat_3);
    free(delay_on_3);
    free(delay_off_3);

	free(status_bat_4);
    free(delay_on_4);
    free(delay_off_4);

}

void led_set_mmc(const char* status, const char* delayOn, const char* delayOff) {

	char *status_mmc_blue = NULL;
    char *delay_on_mmc_blue = NULL;
    char *delay_off_mmc_blue = NULL;

    status_mmc_blue = runShell("cat /sys/class/leds/blue:wan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_mmc_blue && strcmp(status_mmc_blue, "timer") == 0) {
		delay_on_mmc_blue = runShell("cat /sys/class/leds/blue:wan/delay_on");
		delay_off_mmc_blue = runShell("cat /sys/class/leds/blue:wan/delay_off");
    } else {
		char *brightness_mmc_blue = runShell("cat /sys/class/leds/blue:wan/brightness");
		if (strcmp(brightness_mmc_blue, "1") == 0) {
			status_mmc_blue = "on";
		} else {
			status_mmc_blue = "off";
		}
    }

	char *status_mmc_green = NULL;
    char *delay_on_mmc_green = NULL;
    char *delay_off_mmc_green = NULL;

    status_mmc_green = runShell("cat /sys/class/leds/green:wlan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_mmc_green && strcmp(status_mmc_green, "timer") == 0) {
		delay_on_mmc_green = runShell("cat /sys/class/leds/green:wlan/delay_on");
		delay_off_mmc_green = runShell("cat /sys/class/leds/green:wlan/delay_off");
    } else {
		char *brightness_mmc_green = runShell("cat /sys/class/leds/green:wlan/brightness");
		if (strcmp(brightness_mmc_green, "1") == 0) {
			status_mmc_green = "on";
		} else {
			status_mmc_green = "off";
		}
    }

	char *status_mmc_red = NULL;
    char *delay_on_mmc_red = NULL;
    char *delay_off_mmc_red = NULL;

    status_mmc_red = runShell("cat /sys/class/leds/red:power/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_mmc_red && strcmp(status_mmc_red, "timer") == 0) {
		delay_on_mmc_red = runShell("cat /sys/class/leds/red:power/delay_on");
		delay_off_mmc_red = runShell("cat /sys/class/leds/red:power/delay_off");
    } else {
		char *brightness_mmc_red = runShell("cat /sys/class/leds/red:power/brightness");
		if (strcmp(brightness_mmc_red, "1") == 0) {
			status_mmc_red = "on";
		} else {
			status_mmc_red = "off";
		}
    }

    if (status && strcmp(status, "on") == 0) {
        if (strcmp("timer", status_mmc_blue) != 0 || strcmp(delayOn, delay_on_mmc_blue) != 0 || strcmp(delayOff, delay_off_mmc_blue) != 0) {
            led_timer("blue:wan", delayOn, delayOff);
        }
	if (strcmp("off", status_mmc_green) != 0) {
            led_off("green:wlan");
        }
	if (strcmp("off", status_mmc_red) != 0) {
            led_off("red:power");
        }
    } else if (status && strcmp(status, "reg") == 0) {
        if (strcmp("timer", status_mmc_green) != 0 || strcmp(delayOn, delay_on_mmc_green) != 0 || strcmp(delayOff, delay_off_mmc_green) != 0) {
            led_timer("green:wlan", delayOn, delayOff);
        }
	if (strcmp("off", status_mmc_red) != 0) {
            led_off("red:power");
        }
	if (strcmp("off", status_mmc_blue) != 0) {
            led_off("blue:wan");
        }
    } else if (status && strcmp(status, "off") == 0) {
        if (strcmp("timer", status_mmc_red) != 0 || strcmp(delayOn, delay_on_mmc_red) != 0 || strcmp(delayOff, delay_off_mmc_red) != 0) {
            led_timer("red:power", delayOn, delayOff);
        }
	if (strcmp("off", status_mmc_blue) != 0) {
            led_off("blue:wan");
        }
	if (strcmp("off", status_mmc_green) != 0) {
            led_off("green:wlan");
        }
    }

	free(status_mmc_blue);
    free(delay_on_mmc_blue);
    free(delay_off_mmc_blue);

	free(status_mmc_green);
    free(delay_on_mmc_green);
    free(delay_off_mmc_green);

	free(status_mmc_red);
    free(delay_on_mmc_red);
    free(delay_off_mmc_red);

}

void led_set_wifi(const char* status, const char* delayOn, const char* delayOff) {

	char *status_wifi = NULL;
    char *delay_on_wifi = NULL;
    char *delay_off_wifi = NULL;

    status_wifi = runShell("cat /sys/class/leds/blue:wlan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (status_wifi && strcmp(status_wifi, "timer") == 0) {
		delay_on_wifi = runShell("cat /sys/class/leds/blue:wlan/delay_on");
		delay_off_wifi = runShell("cat /sys/class/leds/blue:wlan/delay_off");
    } else {
		char *brightness_wifi= runShell("cat /sys/class/leds/blue:wlan/brightness");
		if (strcmp(brightness_wifi, "1") == 0) {
			status_wifi = "on";
		} else {
			status_wifi = "off";
		}
    }

    if (status && strcmp(status, "on") == 0) {
		if (strcmp(status, status_wifi) != 0) {
            led_on("blue:wlan");
        }
    } else if (status && strcmp(status, "off") == 0) {
		if (strcmp(status, status_wifi) != 0) {
            led_off("blue:wlan");
        }
    }

	free(status_wifi);
    free(delay_on_wifi);
    free(delay_off_wifi);
}

void reset_led_monitor() {
	led_set_bat("off", "off", "off", "off", "1000", "1000");
	led_off("blue:wlan");
	led_on("red:power");
	led_on("blue:wan");
	led_on("green:wlan");	
}

void led_on_all() {
	led_set_bat("on", "on", "on", "on", "1000", "1000");
	led_on("blue:wlan");
	led_on("red:power");
	led_on("blue:wan");
	led_on("green:wlan");	
}

void led_off_all() {
	led_set_bat("off", "off", "off", "off", "1000", "1000");
	led_off("blue:wlan");
	led_off("red:power");
	led_off("blue:wan");
	led_off("green:wlan");	
}

void led_timer_red() {
	led_timer("red:power", "200", "200");
}

void led_timer_blue() {
	led_timer("blue:wan", "200", "200");	
}

void led_timer_green() {
	led_timer("green:wlan", "200", "200");	
}

void led_timer_wifi() {
	led_timer("blue:wlan", "200", "200");	
}

void led_timer_mmc() {
	char *mmc_led = NULL;
    char *mmc_trigger = NULL;

    mmc_trigger = runShell("cat /sys/class/leds/blue:wan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
    if (mmc_trigger && strcmp(mmc_trigger, "timer") == 0) {
		mmc_led = "blue:wan";
    } else {
		mmc_trigger = runShell("cat /sys/class/leds/green:wlan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
		if (mmc_trigger && strcmp(mmc_trigger, "timer") == 0) {
			mmc_led = "green:wlan";
		} else {
			mmc_led = "red:power";
		}
    }

	led_timer(mmc_led, "200", "200");	

	free(mmc_led);
    free(mmc_trigger);
}

void run_led_monitor() {
	char *enabled = NULL;
	char *capacity = NULL;
	char *status = NULL;
	char *mmc = NULL;
	char *wifi = NULL;
	while (1) {
		// 检查是否启用 Battery LED 设置
		enabled = runShell("uci get ledmonitor.main.battery");
		if (enabled != NULL && strcmp(enabled, "1") == 0) {
			capacity = runShell("cat /sys/class/power_supply/pm8916-bms-vm/capacity");
			//capacity = atoi(result);
			status = runShell("cat /sys/class/power_supply/pm8916-bms-vm/status | tr A-Z a-z");
			if (atoi(capacity) == 100) {
				led_set_bat("on", "on", "on", "on", "1000", "1000");
			} else if (atoi(capacity) >= 75) {
				if (strcasecmp(status, "full") == 0) {
					led_set_bat("on", "on", "on", "on", "1000", "1000");
				} else if (strcasecmp(status, "charging") == 0) {
					led_set_bat("on", "on", "on", "timer", "1000", "1000");
				} else {
					led_set_bat("on", "on", "on", "off", "1000", "1000");
				}
			} else if (atoi(capacity) >= 50) {
				if (strcasecmp(status, "charging") == 0) {
					led_set_bat("on", "on", "timer", "off", "1000", "1000");
				} else {
					led_set_bat("on", "on", "off", "off", "1000", "1000");
				}
			} else if (atoi(capacity) >= 25) {
				if (strcasecmp(status, "charging") == 0) {
					led_set_bat("on", "timer", "off", "off", "1000", "1000");
				} else {
					led_set_bat("on", "off", "off", "off", "1000", "1000");
				}
			} else {
				if (strcasecmp(status, "charging") == 0) {
					led_set_bat("timer", "off", "off", "off", "1000", "1000");
				} else {
					led_set_bat("timer", "off", "off", "off", "100", "1000");
				}
			}

			free(capacity);
			free(status);
		}
		free(enabled);

		// 检查是否启用 4G LED 设置
		enabled = runShell("uci get ledmonitor.main.4g");
		if (enabled != NULL && strcmp(enabled, "1") == 0) {
			mmc = runShell("mmcli -m 0 | grep -m 1 'state:' | grep -o 'connected'");
			if (mmc != NULL && strcmp(mmc, "connected") == 0) {
				led_set_mmc("on", "1000", "1000");
			} else {
				mmc = runShell("mmcli -m 0 | grep -m 1 'state:' | grep -o 'registered'");
				if (mmc != NULL && strcmp(mmc, "registered") == 0) {
					led_set_mmc("reg", "1000", "1000");
				} else {
					led_set_mmc("off", "1000", "1000");
				}
			}
			free(mmc);
		}
		free(enabled);

		// 检查是否启用 WiFi LED 设置
		enabled = runShell("uci get ledmonitor.main.wifi");
		if (enabled != NULL && strcmp(enabled, "1") == 0) {
			wifi = runShell("iwinfo phy0-ap0 info | grep -c 'Signal'");
			if (wifi != NULL && strcmp(wifi, "1") == 0) {
				led_set_wifi("on", "1000", "1000");
			} else {
				led_set_wifi("off", "1000", "1000");
			}
			free(wifi);
		}
		free(enabled);

		// 休眠 5 秒
		sleep(5);
	}
}

void show_version() {
	printf("%s\n", "LED monitor For MF32(4 battery leds)");
	printf("%s\n", "v2023.10.15 By Phang");
}

int main(int argc, char* argv[]) {
	if (argc == 2) {
		if (strcmp(argv[1], "run_led_monitor") == 0) {
			run_led_monitor();
		} else if (strcmp(argv[1], "reset_led_monitor") == 0) {
			reset_led_monitor();
		} else if (strcmp(argv[1], "led_on_all") == 0) {
			led_on_all();
		} else if (strcmp(argv[1], "led_off_all") == 0) {
			led_off_all();
		} else if (strcmp(argv[1], "led_timer_red") == 0) {
			led_timer_red();
		} else if (strcmp(argv[1], "led_timer_blue") == 0) {
			led_timer_blue();
		} else if (strcmp(argv[1], "led_timer_green") == 0) {
			led_timer_green();
		} else if (strcmp(argv[1], "led_timer_wifi") == 0) {
			led_timer_wifi();
		} else if (strcmp(argv[1], "led_timer_mmc") == 0) {
			led_timer_mmc();
		} else if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0 ) {
			show_version();
		}
	}
	return 0;
}
