// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright 2004 James Cleverdon, IBM.
 *
 * Flat APIC subarch code.
 *
 * Hacked for x86-64 by James Cleverdon from i386 architecture code by
 * Martin Bligh, Andi Kleen, James Bottomley, John Stultz, and
 * James Cleverdon.
 */
#include <linux/export.h>

#include <asm/apic.h>

#include "local.h"

static struct apic apic_physflat;
static struct apic apic_flat;

struct apic *apic __ro_after_init = &apic_flat;
EXPORT_SYMBOL_GPL(apic);

static int flat_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
{
	return 1;
}

static void _flat_send_IPI_mask(unsigned long mask, int vector)
{
	unsigned long flags;

	flags = hard_local_irq_save();
	__default_send_IPI_dest_field(mask, vector, APIC_DEST_LOGICAL);
	hard_local_irq_restore(flags);
}

static void flat_send_IPI_mask(const struct cpumask *cpumask, int vector)
{
	unsigned long mask = cpumask_bits(cpumask)[0];

	_flat_send_IPI_mask(mask, vector);
}

static void
flat_send_IPI_mask_allbutself(const struct cpumask *cpumask, int vector)
{
	unsigned long mask = cpumask_bits(cpumask)[0];
	int cpu = smp_processor_id();

	if (cpu < BITS_PER_LONG)
		__clear_bit(cpu, &mask);

	_flat_send_IPI_mask(mask, vector);
}

static u32 physflat_get_apic_id(u32 x)
{
	return (x >> 24) & 0xFF;
}

static int physflat_probe(void)
{
	return 1;
}

static int physflat_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
{
	return 1;
}

static struct apic apic_physflat __ro_after_init = {

	.name				= "physical flat",
	.probe				= physflat_probe,
	.acpi_madt_oem_check		= physflat_acpi_madt_oem_check,

	.dest_mode_logical		= false,

	.disable_esr			= 0,

	.cpu_present_to_apicid		= default_cpu_present_to_apicid,

	.max_apic_id			= 0xFE,
	.get_apic_id			= physflat_get_apic_id,

	.calc_dest_apicid		= apic_default_calc_apicid,

	.send_IPI			= default_send_IPI_single_phys,
	.send_IPI_mask			= default_send_IPI_mask_sequence_phys,
	.send_IPI_mask_allbutself	= default_send_IPI_mask_allbutself_phys,
	.send_IPI_allbutself		= default_send_IPI_allbutself,
	.send_IPI_all			= default_send_IPI_all,
	.send_IPI_self			= default_send_IPI_self,
	.nmi_to_offline_cpu		= true,

	.read				= native_apic_mem_read,
	.write				= native_apic_mem_write,
	.eoi				= native_apic_mem_eoi,
	.icr_read			= native_apic_icr_read,
	.icr_write			= native_apic_icr_write,
	.wait_icr_idle			= apic_mem_wait_icr_idle,
	.safe_wait_icr_idle		= apic_mem_wait_icr_idle_timeout,
};
apic_driver(apic_physflat);

struct apic *apic __ro_after_init = &apic_physflat;
EXPORT_SYMBOL_GPL(apic);
