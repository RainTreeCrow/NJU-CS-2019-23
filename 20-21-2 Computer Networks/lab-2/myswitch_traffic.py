'''
Ethernet learning switch in Python.

Note that this file currently has the code to implement a "hub"
in it, not a learning switch.  (I.e., it's currently a switch
that doesn't learn.)
'''
import switchyard
from switchyard.lib.userlib import *

TABLE_SIZE = 5

class info:
    def __init__(self,interface,volume):
        self.interface = interface
        self.volume = volume

def main(net: switchyard.llnetbase.LLNetBase):
    my_interfaces = net.interfaces()
    mymacs = [intf.ethaddr for intf in my_interfaces]

    info_table = {}
    info_counter = 0

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
        if eth.src in info_table.keys():
            if info_table[eth.src].interface != fromIface:
                info_table[eth.src].interface = fromIface
        else:
            if info_counter == TABLE_SIZE:
                min_volume = 10000000000
                for mac in list(info_table):
                    temp_volume = info_table[mac].volume
                    if (temp_volume < min_volume):
                        min_volume = temp_volume
                        min_mac = mac
                info_table.pop(min_mac)
            else:
                info_counter += 1
            info_table[eth.src] = info(fromIface, 0)
        if eth.dst in mymacs:
            log_info("Received a packet intended for me")
        else:
            if eth.dst not in info_table.keys():
                for intf in my_interfaces:
                    if fromIface!= intf.name:
                        log_info (f"Flooding packet {packet} to {intf.name}")
                        net.send_packet(intf, packet)
            else:
                info_table[eth.dst].volume += 1
                port = info_table[eth.dst].interface
                log_info(f"Sending packet {packet} to {port}")
                net.send_packet(port, packet)
        #for m, inf in info_table.items():
            #print(f"Volume: {m} {inf.interface} {inf.volume}\n")

    net.shutdown()
