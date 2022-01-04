/*
 * wifi.c
 *
 */
#include "wifi.h"
#include "user_interface.h"
#include "osapi.h"
#include "espconn.h"
#include "os_type.h"
#include "mem.h"
#include "user_config.h"
#include "config.h"
#include "sntp.h"
#include "debug.h"

static ETSTimer sntp_timer;
static ETSTimer WiFiLinker;
static uint8_t wifiStatus = STATION_IDLE, lastWifiStatus = STATION_IDLE;

static void ICACHE_FLASH_ATTR user_wifi_check_ip(void *arg);
static void user_sntpfn();


/* ------------ GLOBAL FUNCTIONS ------------------------------------------------------ */

void ICACHE_FLASH_ATTR USER_wifi_connect()
{
    struct station_config stationConf;

    INFO("WIFI_INIT\r\n");
    wifi_set_opmode_current(STATION_MODE);

    //wifi_station_set_auto_connect(FALSE);

    os_memset(&stationConf, 0, sizeof(struct station_config));

    os_sprintf(stationConf.ssid, "%s", sysCfg.sta_ssid);
    os_sprintf(stationConf.password, "%s", sysCfg.sta_pwd);

    wifi_station_set_config_current(&stationConf);

    os_timer_disarm(&WiFiLinker);
    os_timer_setfn(&WiFiLinker, (os_timer_func_t *)user_wifi_check_ip, NULL);
    os_timer_arm(&WiFiLinker, 1000, 0);

    //wifi_station_set_auto_connect(TRUE);
    wifi_station_connect();
}



/* ------------- LOCAL FUNCTIONS ------------------------------------------------------ */

static void ICACHE_FLASH_ATTR user_wifi_check_ip(void *arg)
{
    struct ip_info ipConfig;

    os_timer_disarm(&WiFiLinker);
    wifi_get_ip_info(STATION_IF, &ipConfig);
    wifiStatus = wifi_station_get_connect_status();

    if (wifiStatus == STATION_GOT_IP && ipConfig.ip.addr != 0) {
        os_timer_setfn(&WiFiLinker, (os_timer_func_t *)user_wifi_check_ip, NULL);
        os_timer_arm(&WiFiLinker, 3000, 0);
    } else {
        os_timer_setfn(&WiFiLinker, (os_timer_func_t *)user_wifi_check_ip, NULL);
        os_timer_arm(&WiFiLinker, 500, 0);
        if(wifi_station_get_connect_status() == STATION_WRONG_PASSWORD) {
            INFO("STATION_WRONG_PASSWORD\r\n");
            wifi_station_connect();
        } else if(wifi_station_get_connect_status() == STATION_NO_AP_FOUND) {
            INFO("STATION_NO_AP_FOUND\r\n");
            wifi_station_connect();
        } else if(wifi_station_get_connect_status() == STATION_CONNECT_FAIL) {
            INFO("STATION_CONNECT_FAIL\r\n");
            wifi_station_connect();
        } else {
            INFO("STATION_IDLE\r\n");
        }
    }

    if(wifiStatus != lastWifiStatus) {
        lastWifiStatus = wifiStatus;
        if(wifiStatus == STATION_GOT_IP){
            sntp_setservername(0, "pool.ntp.org"); // set sntp server after got ip address
            sntp_set_timezone(TIMEZONE);
            sntp_init();
            os_timer_disarm(&sntp_timer);
            os_timer_setfn(&sntp_timer, (os_timer_func_t *)user_sntpfn, NULL);
            os_timer_arm(&sntp_timer, 5000, 1);//5s
        } else {
            os_timer_disarm(&sntp_timer);
        }
    }
}


static void user_sntpfn()
{
    uint32_t ts = 0;
    char* real_time = NULL;
    uint8_t hour = 0u;

    ts = sntp_get_current_timestamp();
    real_time = sntp_get_real_time(ts);

    if(real_time != NULL) {
        //INFO("current time : %s\n", real_time);
        hour = ((*(real_time + 11) - '0') * 10u) + (*(real_time + 12) - '0');
        //INFO("Hour: %d\n", hour);
        if ( (hour >= 0) && (hour < 3) 
          || (hour >= 17) && (hour <= 23)) {
            // Turn the switch ON at 17:00:00 - 2:59:59
            gpio_output_set(0,BIT0,0,0);
        } else {
            // Turn the switch OFF at 3h
            gpio_output_set(BIT0,0,0,0);
        }
    }
}
