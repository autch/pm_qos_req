
# pm_qos_req: A Linux module for setting PM QoS request at fixed value

This is a Linux module for setting some PM QoS request(s) at fixed
values until it's unloaded.

Useful when fixing PM QoS value is necessary, such as in case of
http://lkml.org/lkml/2012/3/23/343


## Compiling

Grab the source:

    git clone git://github.com/autch/pm_qos_req.git
    cd pm_qos_req/

Make sure that Linux headers are installed:

    ls /lib/modules/`uname -r`/build

Or install it (Debian and its derivatives):

    apt-get install linux-headers-`uname -r`

Then build:

    make

Install:

    mkdir -p /lib/modules/`uname -r`/extra/
    cp pm_qos_req.ko /lib/modules/`uname -r`/extra/
    depmod -a


## DKMS

    # cd $SOURCE_DIRECTORY_WHERE_YOU_CLONED
    # mkdir /usr/src/pm_qos_req-1.0.0/
    # cp * /usr/src/pm_qos_req-1.0.0/
    # dkms add -m pm_qos_req -v 1.0.0
    # dkms build -m pm_qos_req -v 1.0.0
    # dkms install -m pm_qos_req -v 1.0.0


## Usage

This module does the same thing as following:

    (echo -ne '0x<microseconds in hex>'; sleep 1000d) >/dev/cpu_dma_latency </dev/null 2>/dev/null &
    (echo -ne '0x<microseconds in hex>'; sleep 1000d) >/dev/network_latency </dev/null 2>/dev/null &
    (echo -ne '0x<kbps in hex>'; sleep 1000d) >/dev/network_throughput </dev/null 2>/dev/null &

in a kernel module manner:

    modprobe pm_qos_req [cpu_dma_latency=<us>] [network_latency=<us>] [network_throughput=<kbps>]

See http://www.kernel.org/doc/Documentation/power/pm_qos_interface.txt for meaning of parameters.


## License

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


## Author

Autch <autch@autch.net>
http://github.com/autch/pm_qos_req

