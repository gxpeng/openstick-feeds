/*
 * LED monitor For MF32(4 battery leds)
 * v2023.10.22 By Phang
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>

#define MAX_BUFFER_SIZE 4096

char* runShell(const char* command) {
    char* buffer = NULL;
    FILE* fp = NULL;
    
	//printf("%s\n", command);

	fp = popen(command, "r");

	// 若执行出错重复三次
	if (fp == NULL) {
		sleep(1);
		fp = popen(command, "r");
		if (fp == NULL) {
			sleep(1);
			fp = popen(command, "r");
			if (fp == NULL) {
				//perror("popen");
				printf("%s\n", command);
				return NULL;
			}
		}
	}

    buffer = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
    if (buffer == NULL) {
        perror("malloc");
        pclose(fp);
        return NULL;
    }
    
    size_t bytesRead = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, fp);
    if (bytesRead == 0) {
        buffer[bytesRead] = '\0';
    } else {
		if (buffer[bytesRead - 1] == '\n') {
            buffer[bytesRead - 1] = '\0';
        } else {
			buffer[bytesRead] = '\0';
		}
    }
	pclose(fp);
	//printf("%s\n", buffer);
	return buffer;
}

bool led_set_attr(const char* ledName, const char* attrName, const char* value) {
	char command[256];
	char* result = NULL;
    sprintf(command, "echo %s >/sys/class/leds/%s/%s", value, ledName, attrName);
	result = runShell(command);
    if (result != NULL) {
        free(result);
		return true;
    } else {
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

	//printf("bat: %s %s %s %s %s %s\n", led1, led2, led3, led4, delayOn, delayOff);
	
	char command[256];
	char* result = NULL;

	char status_bat_1[8];
	char delay_on_1[8];
	char delay_off_1[8];

	strcpy(command, "cat /sys/class/leds/bat_1/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_bat_1, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_1/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_1, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/bat_1/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_1, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_1/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_bat_1, "on");
				} else {
					strcpy(status_bat_1, "off");
				}
				free(result);
			}
		}
	}

	char status_bat_2[8];
	char delay_on_2[8];
	char delay_off_2[8];

	strcpy(command, "cat /sys/class/leds/bat_2/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_bat_2, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_2/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_2, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/bat_2/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_2, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_2/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_bat_2, "on");
				} else {
					strcpy(status_bat_2, "off");
				}
				free(result);
			}
		}
	}

	char status_bat_3[8];
	char delay_on_3[8];
	char delay_off_3[8];

	strcpy(command, "cat /sys/class/leds/bat_3/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_bat_3, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_3/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_3, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/bat_3/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_3, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_3/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_bat_3, "on");
				} else {
					strcpy(status_bat_3, "off");
				}
				free(result);
			}
		}
	}

	char status_bat_4[8];
	char delay_on_4[8];
	char delay_off_4[8];

	strcpy(command, "cat /sys/class/leds/bat_4/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_bat_4, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_4/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_4, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/bat_4/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_4, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/bat_4/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_bat_4, "on");
				} else {
					strcpy(status_bat_4, "off");
				}
				free(result);
			}
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

}

void led_set_mmc(const char* status, const char* delayOn, const char* delayOff) {

	//printf("mmc: %s %s %s\n", status, delayOn, delayOff);

	char command[256];
	char* result = NULL;

	char status_mmc_blue[8];
	char delay_on_mmc_blue[8];
	char delay_off_mmc_blue[8];

	strcpy(command, "cat /sys/class/leds/blue:wan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_mmc_blue, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/blue:wan/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_mmc_blue, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/blue:wan/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_mmc_blue, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/blue:wan/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_mmc_blue, "on");
				} else {
					strcpy(status_mmc_blue, "off");
				}
				free(result);
			}
		}
	}

	char status_mmc_green[8];
	char delay_on_mmc_green[8];
	char delay_off_mmc_green[8];

	strcpy(command, "cat /sys/class/leds/green:wlan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_mmc_green, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/green:wlan/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_mmc_green, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/green:wlan/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_mmc_green, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/green:wlan/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_mmc_green, "on");
				} else {
					strcpy(status_mmc_green, "off");
				}
				free(result);
			}
		}
	}

	char status_mmc_red[8];
	char delay_on_mmc_red[8];
	char delay_off_mmc_red[8];

	strcpy(command, "cat /sys/class/leds/red:power/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_mmc_red, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/red:power/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_mmc_red, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/red:power/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_mmc_red, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/red:power/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_mmc_red, "on");
				} else {
					strcpy(status_mmc_red, "off");
				}
				free(result);
			}
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
}

void led_set_wifi(const char* status, const char* delayOn, const char* delayOff) {

	printf("wifi: %s\n", status);

	char command[256];
	char* result = NULL;

	char status_wifi[8];
	char delay_on_wifi[8];
	char delay_off_wifi[8];

	strcpy(command, "cat /sys/class/leds/blue:wlan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			strcpy(status_wifi, "timer");
			free(result);
			strcpy(command, "cat /sys/class/leds/blue:wlan/delay_on");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_on_wifi, result);
				free(result);
			}
			strcpy(command, "cat /sys/class/leds/blue:wlan/delay_off");
			result = runShell(command);
			if (result != NULL) {
				strcpy(delay_off_wifi, result);
				free(result);
			}
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/blue:wlan/brightness");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "1") == 0) {
					strcpy(status_wifi, "on");
				} else {
					strcpy(status_wifi, "off");
				}
				free(result);
			}
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
}

void reset_led_monitor() {
	led_set_bat("off", "off", "off", "off", "1000", "1000");
	led_off("blue:wlan");
	led_on("red:power");
	led_off("green:wlan");
	led_off("blue:wan");
}

void led_on_all() {
	led_set_bat("on", "on", "on", "on", "1000", "1000");
	led_on("blue:wlan");
	led_off("red:power");
	led_off("green:wlan");
	led_on("blue:wan");	
}

void led_off_all() {
	led_set_bat("off", "off", "off", "off", "1000", "1000");
	led_off("blue:wlan");
	led_off("red:power");
	led_off("green:wlan");
	led_off("blue:wan");
}

void led_init() {
	led_set_bat("off", "off", "off", "off", "1000", "1000");
	led_off("blue:wlan");
	led_off("red:power");
	led_off("green:wlan");
	led_off("blue:wan");
	sleep(2);

	char command[4096];
	char* result = NULL;
	strcat(command, "echo timer >/sys/class/leds/red:power/trigger");
	strcat(command, "\necho 1000 >/sys/class/leds/red:power/delay_on");
	strcat(command, "\necho 5000 >/sys/class/leds/red:power/delay_off");
	strcat(command, "\nsleep 2");
	strcat(command, "\necho timer >/sys/class/leds/green:wlan/trigger");
	strcat(command, "\necho 1000 >/sys/class/leds/green:wlan/delay_on");
	strcat(command, "\necho 5000 >/sys/class/leds/green:wlan/delay_off");
	strcat(command, "\nsleep 2");
	strcat(command, "\necho timer >/sys/class/leds/blue:wan/trigger");
	strcat(command, "\necho 1000 >/sys/class/leds/blue:wan/delay_on");
	strcat(command, "\necho 5000 >/sys/class/leds/blue:wan/delay_off");
	result = runShell(command);
	if( result != NULL ){
		free(result);
	}
}

void led_sleep() {
	led_set_bat("off", "off", "off", "off", "1000", "1000");
	led_off("blue:wlan");
	led_timer("red:power", "100", "5000");
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
	char command[256];
	char* result = NULL;

	char mmc_led[16];
	
	strcpy(command, "cat /sys/class/leds/blue:wan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
	result = runShell(command);
	if (result != NULL) {
		if (strcmp(result, "timer") == 0) {
			free(result);
			strcpy(mmc_led, "blue:wan");
		} else {
			free(result);
			strcpy(command, "cat /sys/class/leds/green:wlan/trigger | awk -F\"[\" '{print $2}' | awk -F\"]\" '{print $1}'");
			result = runShell(command);
			if (result != NULL) {
				if (strcmp(result, "timer") == 0) {
					free(result);
					strcpy(mmc_led, "green:wlan");
				} else {
					free(result);
					strcpy(mmc_led, "red:power");
				}
			}
		}
	}
    led_timer(mmc_led, "200", "200");	
}

void run_led_monitor() {
	char *enabled = NULL;
	char *capacity = NULL;
	char *status = NULL;
	char *mmc = NULL;
	char *wifi = NULL;
	char *sleeping = NULL;
	while (1) {
		/*
		time_t tNow = time(NULL);
		struct tm *tLocal;
		tLocal = localtime(&tNow);
		printf("%4d-%02d-%02d %02d:%02d:%02d\n", (1900+tLocal->tm_year), (1+tLocal->tm_mon), tLocal->tm_mday, tLocal->tm_hour, tLocal->tm_min, tLocal->tm_sec);
		*/

		// 检查是否设置为睡眠模式
		sleeping = runShell("uci get ledmonitor.main.sleeping");

		// 检查是否启用 Battery LED 设置
		enabled = runShell("uci get ledmonitor.main.battery");
		if (enabled != NULL){
			if (strcmp(enabled, "1") == 0 && strcmp(sleeping, "0") == 0) {
				capacity = runShell("cat /sys/class/power_supply/pm8916-bms-vm/capacity");
				status = runShell("cat /sys/class/power_supply/pm8916-bms-vm/status | tr A-Z a-z");
				if (capacity != NULL && status != NULL) {
					if (atoi(capacity) == 100) {
						led_set_bat("on", "on", "on", "on", "1000", "1000");
					} else if (atoi(capacity) >= 90) {
						if (strcasecmp(status, "full") == 0) {
							led_set_bat("on", "on", "on", "on", "1000", "1000");
						} else if (strcasecmp(status, "charging") == 0) {
							led_set_bat("on", "on", "on", "timer", "1000", "1000");
						} else {
							led_set_bat("on", "on", "on", "on", "1000", "1000");
						}
					} else if (atoi(capacity) >= 75) {
						if (strcasecmp(status, "charging") == 0) {
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
				}
				if ( capacity != NULL ) {
					free(capacity);
				}
				if ( status != NULL ) {
					free(status);
				}
			} else {
				led_set_bat("off", "off", "off", "off", "100", "1000");
			}
			free(enabled);
		} 

		// 检查是否启用 WiFi LED 设置
		enabled = runShell("uci get ledmonitor.main.wifi");
		if ( enabled != NULL ) { 
			if ( strcmp(enabled, "1") == 0 && strcmp(sleeping, "0") == 0 ) {
				wifi = runShell("iwinfo phy0-ap0 info 2>&1 | grep -c 'Signal'");
				if ( wifi != NULL ) {
					if (strcmp(wifi, "1") == 0) {
						led_set_wifi("on", "1000", "1000");
					} else {
						led_set_wifi("off", "1000", "1000");
					}
					free(wifi);
				}
			} else {
				led_set_wifi("off", "1000", "1000");
			}
			free(enabled);
		}

		// 检查是否启用 4G LED 设置
		enabled = runShell("uci get ledmonitor.main.4g");
		if ( enabled != NULL ) {
			if ( strcmp(sleeping, "0") == 0 ) {
				if ( strcmp(enabled, "1") == 0 ) {
					mmc = runShell("mmcli -m 0 2>&1 | grep -m 1 'state:' | grep -o 'connected'");
					if ( mmc != NULL ) {
						if ( strcmp(mmc, "connected") == 0 ) {
							free(mmc);
							led_set_mmc("on", "1000", "1000");
						} else {
							free(mmc);
							mmc = runShell("mmcli -m 0 2>&1 | grep -m 1 'state:' | grep -o 'registered'");
							if ( mmc != NULL ) { 
								if( strcmp(mmc, "registered") == 0 ) {
									led_set_mmc("reg", "1000", "1000");
								} else {
									led_set_mmc("off", "1000", "1000");
								}
								free(mmc);
							}
						}
					}
				} else {
					led_set_mmc("off", "1000", "1000");
				}
			} else {
				if ( strcmp(enabled, "1") == 0 ) {
					mmc = runShell("mmcli -m 0 2>&1 | grep -m 1 'state:' | grep -o 'connected'");
					if ( mmc != NULL ) {
						if ( strcmp(mmc, "connected") == 0 ) {
							free(mmc);
							led_set_mmc("on", "100", "5000");
						} else {
							free(mmc);
							mmc = runShell("mmcli -m 0 2>&1 | grep -m 1 'state:' | grep -o 'registered'");
							if ( mmc != NULL ) { 
								if( strcmp(mmc, "registered") == 0 ) {
									led_set_mmc("reg", "100", "5000");
								} else {
									led_set_mmc("off", "100", "5000");
								}
								free(mmc);
							}
						}
					}
				} else {
					led_set_mmc("off", "100", "5000");
				}
			}
			free(enabled);
		}

		if ( sleeping != NULL ) {
			free(sleeping);
		}

		// 休眠 5 秒
		sleep(5);
	}
}

void show_version() {
	printf("%s\n", "LED monitor For MF32(4 battery leds)");
	printf("%s\n\n", "v2023.10.22 By Phang");
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
		} else if (strcmp(argv[1], "led_init") == 0) {
			led_init();
		} else if (strcmp(argv[1], "led_sleep") == 0) {
			led_sleep();
		} else {
			show_version();
		}
	}
	return 0;
}
