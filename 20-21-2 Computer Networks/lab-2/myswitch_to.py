'''
Ethernet learning switch in Python.

Note that this file currently has the code to implement a "hub"
in it, not a learning switch.  (I.e., it's currently a switch
that doesn't learn.)
'''
import switchyard
from switchyard.lib.userlib import *
import time

TIMEOUT = 10

class info:
    def __init__(self,interface,input_time):
        self.interface = interface
        self.input_time = input_time

def update_info(table, timeout):
    for mac in list(table):
        elapsed_time = time.time() - table[mac].input_time
        if (elapsed_time >= TIMEOUT):
            table.pop(mac)

def main(net: switchyard.llnetbase.LLNetBase):
    my_interfaces = net.interfaces()
    mymacs = [intf.ethaddr for intf in my_interfaces]
    
    info_table = {}

    while True:
        try:
            _, fromIface, packet = net.recv_packet()
        except NoPackets:
            continue
        except Shutdown:
            break

        log_debug (f"In {net.name} received packet {packet} on {fromIface}")
        eth = packet.get_header(Ethernet)
        if eth is None:
            log_info("Received a non-Ethernet packet?!")
            return
        #if eth.src not in info_table.keys():
        info_table[eth.src] = info(fromIface, time.time())
        update_info(info_table, TIMEOUT)
        if eth.dst in mymacs:
            log_info("Received a packet intended for me")
        else:
            if eth.dst not in info_table.keys():
                for intf in my_interfaces:
                    if fromIface!= intf.name:
                        log_info (f"Flooding packet {packet} to {intf.name}")
                        net.send_packet(intf, packet)
            else:
                port = info_table[eth.dst].interface
                log_info(f"Sending packet {packet} to {port}")
                net.send_packet(port, packet)

    net.shutdown()
