/* 
 * Copyright (C) 2024 mdnssknght. All Rights Reserved.
 */

#ifndef JUICE_LOG_H
#define JUICE_LOG_H

#include <linux/printk.h>

#define PREFIX_MAX 48
#define LOG_LINE_MAX (1024 - PREFIX_MAX)

#define juice_logv(fmt, ...) printk("[+] juice_is-cis V " fmt, ##__VA_ARGS__)
#define juice_logfv(fmt, ...) printk("[+] juice_is-cis V %s: " fmt, __func__, ##__VA_ARGS__)

#define juice_logd(fmt, ...) printk("[+] juice_is-cis D " fmt, ##__VA_ARGS__)
#define juice_logfd(fmt, ...) printk("[+] juice_is-cis D %s: " fmt, __func__, ##__VA_ARGS__)

#define juice_logi(fmt, ...) printk("[+] juice_is-cis I " fmt, ##__VA_ARGS__)
#define juice_logfi(fmt, ...) printk("[+] juice_is-cis I %s: " fmt, __func__, ##__VA_ARGS__)

#define juice_logw(fmt, ...) printk("[-] juice_is-cis W " fmt, ##__VA_ARGS__)
#define juice_logfw(fmt, ...) printk("[-] juice_is-cis W %s: " fmt, __func__, ##__VA_ARGS__)

#define juice_loge(fmt, ...) printk("[-] juice_is-cis E " fmt, ##__VA_ARGS__)
#define juice_logfe(fmt, ...) printk("[-] juice_is-cis E %s: " fmt, __func__, ##__VA_ARGS__)

#endif /* JUICE_LOG_H */
