/*
    pm_qos_req: Linux module for setting PM QoS request at fixed value
    Copyright (C) 2012 Autch <autch@autch.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/string.h>

#include <linux/pm_qos.h>

#define DRIVER_AUTHOR	"Autch <autch@autch.net>"
#define DRIVER_DESC	"Set PM QoS request at fixed value"

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("cpu_dma_latency");
MODULE_SUPPORTED_DEVICE("network_latency");
MODULE_SUPPORTED_DEVICE("network_throughput");

static int cpu_dma_latency = PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE;
static int network_latency = PM_QOS_NETWORK_LAT_DEFAULT_VALUE;
static int network_throughput = PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE;

module_param(cpu_dma_latency, int, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(cpu_dma_latency, "CPU DMA latency in microseconds");

module_param(network_latency, int, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(network_latency, "Network latency in microseconds");

module_param(network_throughput, int, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(network_throughput, "Network throughput in kilobits per second");

static struct pm_qos_request req_cpu_dma_latency;
static struct pm_qos_request req_network_latency;
static struct pm_qos_request req_network_throughput;

static int __init init_pm_qos_req(void)
{
	printk(KERN_INFO "pm_qos_req: loaded\n");

	if(cpu_dma_latency != PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE) {
		memset(&req_cpu_dma_latency, 0, sizeof req_cpu_dma_latency);
		printk(KERN_INFO "pm_qos_req: setting CPU DMA latency to %d us\n", cpu_dma_latency);
		pm_qos_add_request(&req_cpu_dma_latency, PM_QOS_CPU_DMA_LATENCY, cpu_dma_latency);
	}
	if(network_latency != PM_QOS_NETWORK_LAT_DEFAULT_VALUE) {
		memset(&req_network_latency, 0, sizeof req_network_latency);
		printk(KERN_INFO "pm_qos_req: setting network latency to %d us\n", network_latency);
		pm_qos_add_request(&req_network_latency, PM_QOS_NETWORK_LATENCY, network_latency);
	}
	if(network_throughput != PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE) {
		memset(&req_network_throughput, 0, sizeof req_network_throughput);
		printk(KERN_INFO "pm_qos_req: setting network throughput to %d kbit/sec\n", network_throughput);
		pm_qos_add_request(&req_network_throughput, PM_QOS_NETWORK_THROUGHPUT, network_throughput);
	}
	return 0;
}

static void __exit cleanup_pm_qos_req(void)
{
	printk(KERN_INFO "pm_qos_req: removing PM QoS requests\n");

	if(cpu_dma_latency != PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE) {
		pm_qos_remove_request(&req_cpu_dma_latency);
	}
	if(network_latency != PM_QOS_NETWORK_LAT_DEFAULT_VALUE) {
		pm_qos_remove_request(&req_network_latency);
}
	if(network_throughput != PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE) {
		pm_qos_remove_request(&req_network_throughput);
	}
}

module_init(init_pm_qos_req);
module_exit(cleanup_pm_qos_req);
