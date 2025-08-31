/***************************************************************************/

/*
 *	clk.c -- general ColdFire CPU kernel clk handling
 *
 *	Copyright (C) 2009, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/clk.h>
#include <asm/coldfire.h>

/***************************************************************************/

struct clk *clk_get(struct device *dev, const char *id)
{
	return NULL;
}
/* DISABLED: EXPORT_SYMBOL(clk_get); */

int clk_enable(struct clk *clk)
{
	return 0;
}
/* DISABLED: EXPORT_SYMBOL(clk_enable); */

void clk_disable(struct clk *clk)
{
}
/* DISABLED: EXPORT_SYMBOL(clk_disable); */

void clk_put(struct clk *clk)
{
}
/* DISABLED: EXPORT_SYMBOL(clk_put); */

unsigned long clk_get_rate(struct clk *clk)
{
	return MCF_CLK;
}
/* DISABLED: EXPORT_SYMBOL(clk_get_rate); */
/***************************************************************************/
