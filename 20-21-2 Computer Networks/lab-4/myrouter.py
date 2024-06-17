#!/usr/bin/env python3

'''
Basic IPv4 router (static routing) in Python.
'''

import time
import switchyard
from switchyard.lib.userlib import *


class FwEntry():
    def __init__(self, nwaddr, snaddr, nhaddr, iface):
        self.networkAddr = nwaddr
        self.subnetAddr = snaddr
        self.nextHopAddr = nhaddr
        self.interface = iface

    def print_entry(self):
        print(self.networkAddr, "\t\t", self.subnetAddr, "   \t",
            self.nextHopAddr, "          \t", self.interface
        )


class WEntry():
    def __init__(self, pkt, nhaddr, iface):
        self.packet = pkt
        self.nextHopAddr = nhaddr
        self.interface = iface

    def forward(self, dstmac, net):
        self.packet[Ethernet].dst = dstmac
        net.send_packet(self.interface.name, self.packet)


class ArpEntry:
    def __init__(self, nhaddr, iface):
        self.nextHopAddr = nhaddr
        self.interface = iface
        self.lastArpRequest = 0
        self.countArpRequest = 0

    def arp_request(self, net):
        log_info("Sending ARP request......")
        arpRequest = create_ip_arp_request(
            self.interface.ethaddr,
            self.interface.ipaddr,
            self.nextHopAddr
        )
        self.lastArpRequest = time.time()
        self.countArpRequest += 1
        net.send_packet(self.interface.name, arpRequest)


class WaitQueue():
    def __init__(self, net):
        self.waitQueue = []
        self.net = net
        self.arpQueue = []
        self.arpAddr = []

    def add_entry(self, entry, arp):
        self.waitQueue.append(entry)
        arpReqAddr = entry.nextHopAddr
        if arpReqAddr not in arp.keys() and arpReqAddr not in self.arpAddr:
            self.arpQueue.append(ArpEntry(arpReqAddr, entry.interface))
            self.arpAddr.append(arpReqAddr)

    def remove_entry(self, arpRepAddr):
        for arpReq in self.arpQueue[:]:
            if arpReq.nextHopAddr == arpRepAddr:
                self.arpQueue.remove(arpReq)
                log_info("Deleting answered ARP entry from queue...")
        if arpReq in self.arpAddr:
            self.arpAddr.remove(arpRepAddr)

    def update_queue(self, arp):
        for entry in self.waitQueue[:]:
            if entry.nextHopAddr in arp.keys():
                log_info("Fowarding packet from queue...")
                entry.forward(arp[entry.nextHopAddr], self.net)
                self.waitQueue.remove(entry)
                log_info("Deleting forwarded wait entry from queue...")
        for arpReq in self.arpQueue[:]:
            if time.time() - arpReq.lastArpRequest >= 1:
                if arpReq.countArpRequest < 5:
                    log_info("Sending ARP request from queue...")
                    arpReq.arp_request(self.net)
                else:
                    self.arpQueue.remove(arpReq)
                    if arpReq in self.arpAddr:
                        self.arpAddr.remove(arpReq)
                    log_info("Deleting timeout ARP entry from queue...")
                    for entry in self.waitQueue[:]:
                        if entry.nextHopAddr == arpReq.nextHopAddr:
                            self.waitQueue.remove(entry)
                            log_info("Deleting timeout wait entry from queue...")


class Router(object):
    def __init__(self, net: switchyard.llnetbase.LLNetBase):
        self.net = net
        # other initialization stuff here
        self.interfaces = net.interfaces()
        self.arpTable = {}
        self.forwardingTable = []
        self.waitQueue = WaitQueue(net)
        for iface in self.interfaces:
            self.forwardingTable.append(
                FwEntry(iface.ipaddr, iface.netmask, None, iface.name)
            )
        with open("forwarding_table.txt") as fwFile:
            for line in fwFile:
                entry = line.split()
                if entry:
                    self.forwardingTable.append(
                        FwEntry(entry[0], entry[1], entry[2], entry[3])
                    )
        self.print_fwTable()

    def print_arpTable(self):
        print("----------------------------------")
        print("IP\t\t Mac Address")
        for ip, mac in self.arpTable.items():
            print(ip, "\t", mac)
        print("----------------------------------")

    def print_fwTable(self):
        print("------------------------------------------------------------------------------------")
        print("network address  \t subnet Address\t\t next hop address\t interface")
        for fwEntry in self.forwardingTable:
            fwEntry.print_entry()
        print("------------------------------------------------------------------------------------")

    def handle_packet(self, recv: switchyard.llnetbase.ReceivedPacket):
        _, ifaceName, packet = recv
        # TODO: your logic here
        arp = packet.get_header(Arp)
        ipv4 = packet.get_header(IPv4)
        if arp is not None: #ARP packet
            #Update cached ARP table
            self.arpTable[arp.senderprotoaddr] = arp.senderhwaddr
            if arp.operation == 1: #Request
                log_info("Receive an ARP request.")
                targetInterface = None
                targetProto = arp.targetprotoaddr
                #Serching for the target IP address
                for interface in self.interfaces:
                    if interface.ipaddr == targetProto:
                        targetInterface = interface
                        break
                if targetInterface is not None: #Found
                    #Create ARP reply
                    arpReply = create_ip_arp_reply(targetInterface.ethaddr,
                    arp.senderhwaddr, targetInterface.ipaddr, arp.senderprotoaddr)
                    #Sent out the same interface the ARP request arrived on
                    self.net.send_packet(ifaceName, arpReply)
                    log_info("Sending ARP reply...")
                else:
                    log_info("Drop ARP request.")
            elif arp.operation == 2: #Reply
                log_info("Receive an ARP reply.")
                self.waitQueue.remove_entry(arp.senderprotoaddr)
            else: #Others
                log_info("Unknown ARP format.")
            #Print ARP table every time it is updated
            self.print_arpTable()
        elif ipv4 is not None:
            log_info("Receive an IPV4 packet.")
            ipv4.ttl -= 1
            if ipv4.dst in [iface.ipaddr for iface in self.interfaces]:
                log_info("Packet is for the router itself.")
                #To be handled at a larger stage
            else:
                log_info("Matching dest IP against torwaring table...")
                maxlen = 0
                match = None
                for fwEntry in self.forwardingTable:
                    netAddr = IPv4Network(str(fwEntry.networkAddr) +
                        "/" + str(fwEntry.subnetAddr), False
                    )
                    if ipv4.dst in netAddr:
                        pflen = netAddr.prefixlen
                        if pflen > maxlen:
                            match = fwEntry
                            maxlen = pflen
                if match is not None:
                    log_info("Matching successful.")
                    iface = match.interface
                    for interface in self.interfaces:
                        if interface.name == iface:
                            routerIface = interface
                            break
                    packet[Ethernet].src = routerIface.ethaddr
                    if match.nextHopAddr is not None:
                        self.waitQueue.add_entry(WEntry(packet,
                                ip_address(match.nextHopAddr), routerIface
                            ), self.arpTable
                        )
                    else:
                        self.waitQueue.add_entry(WEntry(
                                packet, ipv4.dst, routerIface
                            ), self.arpTable
                        )
                else:
                    log_info("Matching failed. Packet dropped.")
                    #To be handled in a later stage

    def start(self):
        '''A running daemon of the router.
        Receive packets until the end of time.
        '''
        while True:
            self.waitQueue.update_queue(self.arpTable)
            try:
                recv = self.net.recv_packet(timeout=1.0)
            except NoPackets:
                continue
            except Shutdown:
                break
            self.handle_packet(recv)
            #log_info("Handling packet...")
        self.stop()

    def stop(self):
        self.net.shutdown()


def main(net):
    '''
    Main entry point for router.  Just create Router
    object and get it going.
    '''
    router = Router(net)
    router.start()
