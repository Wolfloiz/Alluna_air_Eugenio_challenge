/*
####################################################################
## Simple Mqtt Client Code for connecting to Eugenio.io IoT platform
####################################################################
##
##################################################
## Código feito por Artur Sarlo(artur.sarlo@la.logicalis.com) codigo 
## modificado por Luiz Henrique (luizhfmonteiro@gmail.com) para 
## Eugenio Challenge Hub
##################################################
*/

#ifndef SECRETS
#define SECRETS

/*
 #########################################################################################
 # CHANGE HERE
 #########################################################################################
*/
#define WIFI_SSID "Luiz-2.4G-"
#define WIFI_PASSWORD "ruanicolaucoelho"

#define DEVICE_ID "529a226c-f80f-4c26-8175-46f8e3c37ff8"

// Copy contents from CA certificate here ▼
static const char cacert[] PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n" \
"RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n" \
"VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n" \
"DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n" \
"ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n" \
"VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n" \
"mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n" \
"IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n" \
"mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n" \
"XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n" \
"dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n" \
"jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n" \
"BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n" \
"DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n" \
"9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n" \
"jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n" \
"Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n" \
"ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n" \
"R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n" \
"-----END CERTIFICATE-----\n";

// Copy contents from cert.pem here ▼
static const char client_cert[] PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDCTCCAfGgAwIBAgIUcoVVWQE4+YVVsxo1c1D+HMvoDKowDQYJKoZIhvcNAQEL\n" \
"BQAwFDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTIwMTAwMTE3NTgwNloXDTIxMTAw\n" \
"MTE3NTgwNlowFDESMBAGA1UEAwwJbG9jYWxob3N0MIIBIjANBgkqhkiG9w0BAQEF\n" \
"AAOCAQ8AMIIBCgKCAQEAlQ+iWfwWFKdmCc6XoT5KjJxu0DZP75IxSyxkFNLYcE0w\n" \
"Ueh4PcoMl8Qjp1dLjMyjnSEnYg1N4a3kuwSGjst+hRhBAPS9LemXDAz/ICNuc6N1\n" \
"mpMAehWcIFy0y5AP+cMd58Fv7E4YBJ1bv+dS8aReBoqeecSi2ufuiYTdQk96NqDC\n" \
"s/Qn+47bODR8V5BtU+iTQcPDqj7UWsLbiXiXyJC8HMOAs6AnaZam4m0SOiCPcPB7\n" \
"TfgDo4uheWmBs7bneGqdmYjsUEVE0hoZ/aRArPNGsWtdu2ngHBm3559Z+hk/uXLd\n" \
"wUyrw/bpWyni9QogWW3XJbRcEmyS8iyKzfn5eGnO7QIDAQABo1MwUTAdBgNVHQ4E\n" \
"FgQU1q0GXcTnxn7RVDQ7HZ0AevTh1e0wHwYDVR0jBBgwFoAU1q0GXcTnxn7RVDQ7\n" \
"HZ0AevTh1e0wDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEABJWJ\n" \
"RSia2GScFsFssHJCGEqOqcOkTLq1AvL5UMhwoQBvcPJYyrD8DPCGndwzFK9IKKjj\n" \
"lOlLjaFW59lUQi3Kl7c+db8DcSVOYEZw1ss66GTG7/kCZ8ngtEfucgFngUK/LvaV\n" \
"EiEr33fdvsQvU3gjtbw61FrlxQhK48jhWSHrbGOh/EhKW+MbUMDTYFz3DCJoQZAR\n" \
"VtjabvmyqWL9xXCVHsq7PD/8cVxx7LOxDstc6tcAipVnzMOLRCUuVBjnqholMSlS\n" \
"N8mTO2UE3Ne9VAo7Ev92hZaUop+1g/i10l2qCuYTQ991/awXYif6u2wfTFvqwjaa\n" \
"TcoFftZ0FSSY24uECQ==\n" \
"-----END CERTIFICATE-----\n";

// Copy contents from  key.pem here ▼
static const char privkey[] PROGMEM = \
"-----BEGIN PRIVATE KEY-----\n" \
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCVD6JZ/BYUp2YJ\n" \
"zpehPkqMnG7QNk/vkjFLLGQU0thwTTBR6Hg9ygyXxCOnV0uMzKOdISdiDU3hreS7\n" \
"BIaOy36FGEEA9L0t6ZcMDP8gI25zo3WakwB6FZwgXLTLkA/5wx3nwW/sThgEnVu/\n" \
"51LxpF4Gip55xKLa5+6JhN1CT3o2oMKz9Cf7jts4NHxXkG1T6JNBw8OqPtRawtuJ\n" \
"eJfIkLwcw4CzoCdplqbibRI6II9w8HtN+AOji6F5aYGztud4ap2ZiOxQRUTSGhn9\n" \
"pECs80axa127aeAcGbfnn1n6GT+5ct3BTKvD9ulbKeL1CiBZbdcltFwSbJLyLIrN\n" \
"+fl4ac7tAgMBAAECggEALKeHWm+zabKQVeXG9O4FRURjygpLPhjMnZmJzdcwMcxd\n" \
"6lu7Eb+isCB5EduL7X0skpjpBG255B7FA+WiLcr2dwbCCnhG6CcvMdP+5fDXWNsi\n" \
"ExFwtiIdKHC9VLIupwL1xYTkc6UdetxtLPsulOdJp6oFObNXmj6a7iWYZxIKKazg\n" \
"OTlU2TO8d2lc8v1FUXC+gDj4D6jEVqiaREPoez4lj/t2KWtddlE390P4fqVIJ6he\n" \
"/jL4iq/ipALfcLlduGeeGEwVKZiuy0MpkttrMp+ErWFWMh8A3Y+9nivJzqSvU2qx\n" \
"o84NhBaBAg4N776DJCAmwyqS31DzqcqMEDeZAIQAnQKBgQDGTleIa0Yt/ieCVDO2\n" \
"jCqnIDP5xT70b6kiEaP9HzIgmbyGFNxXcfWBPh8kT4PeLlZj3EG45CsP8VEAoT3b\n" \
"7cB4+27ApOJ5hUCyWED4ekbcqceRuHT0xkGyvZl7QotyLKG9S0Qc0xUl5bUcQPYm\n" \
"9ko1DOV6kvS/IEUqK0M3WTyf8wKBgQDAbZJSQoXp1NQ88GnJ0kOGBWCv5imJAY4M\n" \
"faghaE72f4hM86FxQRIg7aaw2HOHsRb/0pgmCI+iz1yW4Qshm2pp4iAzp1iDnGpZ\n" \
"/mGFYK4Dm5H2+FBnKXNDbYWdspRcsaBioP0hvDdMxKE6J9+6MM3FY9uX+I2Twufp\n" \
"+zdB57htnwKBgFaDMP7LxfckrLnX4COgbK8yhlpN6dQbro61YXR5GpZMW4mnKiVg\n" \
"CvnSTyW5Js9UKc4w9d8ic4LmBS+gKGt9An4FOuECTecz8fCcPePo/GciDnWNIkDz\n" \
"CRBgVMgIVOt/eyQo5NMqZ0x8NRHZaUnAIsmYEbjyyaFkA6iM7SsFXERvAoGBAInn\n" \
"PKCVKhE8xGlzxeysMlX+zp7grM2R/rH276IZddVz6kNzqjRW9N4CUp6UUJ9jC1+F\n" \
"FiLTqdR9FRbP6sFH9wgw1PEPsgCH/TPHeS4z7iGJwR6kMELuUrt05vfv/iE77vwf\n" \
"8ajWkS8ED6N05gIybZVTjhEoQJYvbTKjJaOmo+ZzAoGACDmJNSwBwHrA82bKcgdS\n" \
"qNOi7PWNg93LH6QiIgfi2jQp7uNHn70t5OBIyDW106r99ipwnrD4FWJjG5znVXnu\n" \
"PB4s5r+Jd21QLwamuXEw2bauCJ0Ft+tDFX2Y7yafwdAQh8RT0+IHDLcEz0JmHUK1\n" \
"A+s3Ccgw4B43413uftuk/Zk=\n" \
"-----END PRIVATE KEY-----\n";

/*
#########################################################################################
#########################################################################################
*/

// NTP related
#define UTC_TIME_ZONE_BRAZIL_HOURS -3
#define UTC_TIME_ZONE_BRAZIL_SECONDS UTC_TIME_ZONE_BRAZIL_HOURS * 3600
//#define USE_SUMMER_TIME_DST  //uncomment to use DST
#define DST_HOURS 0
#define DST_SECONDS DST_HOURS * 3600
#define CURRENT_TIME_APROXIMATION_AS_EPOCH_SECONDS 1510592825
#define NTP_SERVER_0 "pool.ntp.org"
#define NTP_SERVER_1 "time.nist.gov"

// MQTT related
#define MQTT_BROKER "logicalis-eugeniostg-iothub.azure-devices.net"
#define MQTT_PORT 8883
#define MQTT_USER "logicalis-eugeniostg-iothub.azure-devices.net/" DEVICE_ID "/api-version=2019-03-30"

#define MQTT_SUB_CLOUD_TO_DEVICE_TOPIC "devices/529a226c-f80f-4c26-8175-46f8e3c37ff8/messages/devicebound/#"
#define MQTT_SUB_INVOKE_BASE_TOPIC "$iothub/methods/POST/"
#define MQTT_SUB_INVOKE_TOPIC "$iothub/methods/POST/#"

#define MQTT_PUB_INVOKE_REPLY_TOPIC "$iothub/methods/res/{status_code}/?$rid={rid}"
#define MQTT_PUB_DEVICE_TO_CLOUD_TOPIC "devices/529a226c-f80f-4c26-8175-46f8e3c37ff8/messages/events/"

// #define USE_ARDUINO_JSON_LIB

#endif