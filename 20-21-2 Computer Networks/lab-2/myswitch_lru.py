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
    def __init__(self,interface,index):
        self.interface = interface
        self.index = index

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
                max_index = 0
                for mac in list(info_table):
                    temp_index = info_table[mac].index
                    if (temp_index > max_index):
                        max_index = temp_index
                        max_mac = mac
                #print(f"Delete {max_mac} {info_table[max_mac].interface} from table\n")
                info_table.pop(max_mac)
            else:
                info_counter += 1
            for mac in list(info_table):
                info_table[mac].index += 1
            info_table[eth.src] = info(fromIface, 0)
            #print(f"Add {eth.src} {fromIface} to table.\n")
        if eth.dst in mymacs:
            log_info("Received a packet intended for me")
        else:
            if eth.dst not in info_table.keys():
                for intf in my_interfaces:
                    if fromIface!= intf.name:
                        log_info (f"Flooding packet {packet} to {intf.name}")
                        net.send_packet(intf, packet)
            else:
                dst_index = info_table[eth.dst].index
                for mac in list(info_table):
                    if (info_table[mac].index <= dst_index):
                        info_table[mac].index += 1
                info_table[eth.dst].index = 0
                port = info_table[eth.dst].interface
                log_info(f"Sending packet {packet} to {port}")
                net.send_packet(port, packet)

    net.shutdown()
