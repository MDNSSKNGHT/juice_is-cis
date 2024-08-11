/* 
 * Copyright (C) 2024 mdnssknght. All Rights Reserved.
 */

#include <compiler.h>
#include <kpmodule.h>
#include <linux/printk.h>
#include <common.h>
#include <kputils.h>
#include <linux/string.h>

///< The name of the module, each KPM must has a unique name.
KPM_NAME("Juice my IS-CIS!");

///< The version of the module.
KPM_VERSION("1.0.0");

///< The license type.
KPM_LICENSE("Not licensed");

///< The author.
KPM_AUTHOR("mdnssknght");

///< The description.
KPM_DESCRIPTION("A KPM that juices IS-CIS driver capabilities.");

/**
 * @brief KPM initialization
 * @details 
 * 
 * @param args 
 * @param reserved 
 * @return int 
 */
static long kpm_init(const char *args, const char *event, void *__user reserved)
{
    pr_info("kpm hello init, event: %s, args: %s\n", event, args);
    pr_info("kernelpatch version: %x\n", kpver);
    return 0;
}

static long kpm_control0(const char *args, char *__user out_msg, int outlen)
{
    pr_info("kpm hello control0, args: %s\n", args);
    char echo[64] = "echo: ";
    strncat(echo, args, 48);
    compat_copy_to_user(out_msg, echo, sizeof(echo));
    return 0;
}

static long kpm_control1(void *a1, void *a2, void *a3)
{
    pr_info("kpm hello control1, a1: %llx, a2: %llx, a3: %llx\n", a1, a2, a3);
    return 0;
}

static long kpm_exit(void *__user reserved)
{
    pr_info("kpm hello exit\n");
    return 0;
}

KPM_INIT(kpm_init);
KPM_CTL0(kpm_control0);
KPM_CTL1(kpm_control1);
KPM_EXIT(kpm_exit);
