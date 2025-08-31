#include <linux/module.h>
#include <asm/io.h>
#include <arch/svinto.h>

/* Export shadow registers for the CPU I/O pins */
/* DISABLED: EXPORT_SYMBOL(genconfig_shadow); */
/* DISABLED: EXPORT_SYMBOL(port_pa_data_shadow); */
/* DISABLED: EXPORT_SYMBOL(port_pa_dir_shadow); */
/* DISABLED: EXPORT_SYMBOL(port_pb_data_shadow); */
/* DISABLED: EXPORT_SYMBOL(port_pb_dir_shadow); */
/* DISABLED: EXPORT_SYMBOL(port_pb_config_shadow); */
/* DISABLED: EXPORT_SYMBOL(port_g_data_shadow); */

/* Cache flush functions */
/* DISABLED: EXPORT_SYMBOL(flush_etrax_cache); */
/* DISABLED: EXPORT_SYMBOL(prepare_rx_descriptor); */
