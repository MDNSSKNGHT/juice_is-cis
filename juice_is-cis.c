/* 
 * Copyright (C) 2024 mdnssknght. All Rights Reserved.
 */

#include <compiler.h>
#include <kpmodule.h>
#include <common.h>
#include <kputils.h>
#include <linux/string.h>
#include <linux/kallsyms.h>
#include <hook.h>

#include "juice_log.h"

#include "is-interface-sensor.h"

///< The name of the module, each KPM must have a unique name.
KPM_NAME("Juice my IS-CIS!");

///< The version of the module.
KPM_VERSION("1.0.0");

///< The license type.
KPM_LICENSE("Not licensed");

///< The author.
KPM_AUTHOR("mdnssknght");

///< The description.
KPM_DESCRIPTION("A KPM that juices IS-CIS driver capabilities.");

struct is_cis_ops *cis_ops_2ld;

void before_cis_init(hook_fargs2_t *args, void *udata)
{
	juice_logfi("subdev: %p", (void *)args->arg0);
}

void after_cis_init(hook_fargs2_t *args, void *udata)
{
	juice_logfi("subdev: %p", (void *)args->arg0);
}

void before_cis_deinit(hook_fargs2_t *args, void *udata)
{
	juice_logfi("subdev: %p", (void *)args->arg0);
}

void after_cis_deinit(hook_fargs2_t *args, void *udata)
{
	juice_logfi("subdev: %p", (void *)args->arg0);
}

/**
 * @brief KPM initialization
 * @details 
 * 
 * @param args 
 * @param reserved 
 * @return int 
 */
static long juice_init(const char *args, const char *event, void *__user reserved)
{
	juice_logi("kpm init, event: %s, args: %s\n", event, args);
	juice_logi("kernelpatch version: %x\n", kpver);

	cis_ops_2ld = (struct is_cis_ops *)kallsyms_lookup_name("cis_ops_2ld");

	juice_logfi("cis_ops_2ld: %p", cis_ops_2ld);

	hook_err_t err = 0;

	err |= hook_wrap1(cis_ops_2ld->cis_init, before_cis_init, after_cis_init, 0);
	err |= hook_wrap1(cis_ops_2ld->cis_deinit, before_cis_deinit, after_cis_deinit, 0);

	return err;
}

static long juice_control0(const char *args, char *__user out_msg, int outlen)
{
	juice_logi("kpm control0, args: %s\n", args);
	char echo[64] = "echo: ";
	strncat(echo, args, 48);
	compat_copy_to_user(out_msg, echo, sizeof(echo));
	return 0;
}

static long juice_control1(void *a1, void *a2, void *a3)
{
	juice_logi("kpm control1, a1: %llx, a2: %llx, a3: %llx\n", a1, a2, a3);
	return 0;
}

static long juice_exit(void *__user reserved)
{
	juice_logi("kpm exit\n");

	unhook(cis_ops_2ld->cis_init);
	unhook(cis_ops_2ld->cis_deinit);

	return 0;
}

KPM_INIT(juice_init);
KPM_CTL0(juice_control0);
KPM_CTL1(juice_control1);
KPM_EXIT(juice_exit);
