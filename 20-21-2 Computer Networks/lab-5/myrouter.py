#!/usr/bin/env python3

'''
Basic IPv4 router (static routing) in Python.
'''

import time
import switchyard
from switchyard.lib.userlib import *


def mk_ping(hwsrc, hwdst, ipsrc, ipdst, reply=False, ttl=64, payload=''):
    ether = Ethernet()
    ether.src = EthAddr(hwsrc)
    ether.dst = EthAddr(hwdst)
    ether.ethertype = EtherType.IP
    ippkt = IPv4()
    ippkt.src = IPAddr(ipsrc)
    ippkt.dst = IPAddr(ipdst)
    ippkt.protocol = IPProtocol.ICMP
    ippkt.ttl = ttl
    ippkt.ipid = 0
    if reply:
        icmppkt = ICMP()
        icmppkt.icmptype = ICMPType.EchoReply
        icmppkt.icmpcode = ICMPCodeEchoReply.EchoReply
    else:
        icmppkt = ICMP()
        icmppkt.icmptype = ICMPType.EchoRequest
        icmppkt.icmpcode = ICMPCodeEchoRequest.EchoRequest
    #icmppkt.icmpdata = payload
    #icmppkt.icmpdata.sequence = 42
    icmppkt.icmpdata.sequence = payload.sequence
    icmppkt.icmpdata.identifier = payload.identifier
    #icmppkt.icmpdata.data = payload
    icmppkt.icmpdata.data = payload.data
    return ether + ippkt + icmppkt 

def mk_icmperr(hwsrc, hwdst, ipsrc, ipdst, xtype, xcode=0, origpkt=None, ttl=64):
    ether = Ethernet()
    ether.src = EthAddr(hwsrc)
    ether.dst = EthAddr(hwdst)
    ether.ethertype = EtherType.IP
    ippkt = IPv4()
    ippkt.src = IPAddr(ipsrc)
    ippkt.dst = IPAddr(ipdst)
    ippkt.protocol = IPProtocol.ICMP
    ippkt.ttl = ttl
    ippkt.ipid = 0
    icmppkt = ICMP()
    icmppkt.icmptype = xtype
    icmppkt.icmpcode = xcode
    if origpkt is not None:
        xpkt = deepcopy(origpkt)
        i = xpkt.get_header_index(Ethernet)
        if i >= 0:
            del xpkt[i]
        icmppkt.icmpdata.data = xpkt.to_bytes()[:28]
        icmppkt.icmpdata.origdgramlen = len(xpkt)

    return ether + ippkt + icmppkt 


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
    def __init__(self, pkt, ifaceName, nhaddr, iface):
        self.packet = pkt
        self.fromIface = ifaceName
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
    def __init__(self):
        self.waitQueue = []
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


class Router(object):
    def __init__(self, net: switchyard.llnetbase.LLNetBase):
        self.net = net
        # other initialization stuff here
        self.interfaces = net.interfaces()
        self.arpTable = {}
        self.forwardingTable = []
        self.wait = WaitQueue()
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
    
    def update_queue(self):
        for entry in self.wait.waitQueue[:]:
            if entry.nextHopAddr in self.arpTable.keys():
                log_info("Fowarding packet from queue...")
                entry.forward(self.arpTable[entry.nextHopAddr], self.net)
                self.wait.waitQueue.remove(entry)
                log_info("Deleting forwarded wait entry from queue...")
        for arpReq in self.wait.arpQueue[:]:
            if time.time() - arpReq.lastArpRequest >= 1:
                if arpReq.countArpRequest < 5:
                    log_info("Sending ARP request from queue...")
                    arpReq.arp_request(self.net)
                else:
                    self.wait.arpQueue.remove(arpReq)
                    if arpReq in self.wait.arpAddr:
                        self.wait.arpAddr.remove(arpReq)
                    log_info("Deleting timeout ARP entry from queue...")
                    for entry in self.wait.waitQueue[:]:
                        if entry.nextHopAddr == arpReq.nextHopAddr:
                            log_info("ARP failure.")
                            packet = entry.packet
                            ipv4 = packet.get_header(IPv4)
                            #icmp = packet.get_header(ICMP)
                            ether = packet.get_header(Ethernet)
                            packet = mk_icmperr(hwsrc=self.net.interface_by_name(
                                entry.fromIface).ethaddr,
                                hwdst=ether.src,
                                ipsrc=self.net.interface_by_name(entry.fromIface).ipaddr,
                                ipdst=ipv4.src,
                                xtype=ICMPType.DestinationUnreachable,
                                xcode=1,
                                origpkt=packet
                            )
                            self.send_ipv4(packet, entry.fromIface)
                            log_info("Deleting timeout wait entry from queue...")
                            self.wait.waitQueue.remove(entry)
    
    def send_ipv4(self, packet, ifacename):
        ipv4 = packet.get_header(IPv4)
        if ipv4.dst in [iface.ipaddr for iface in self.interfaces]:
            log_info("Packet is for the router itself.")
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
                    self.wait.add_entry(WEntry(packet, ifacename,
                            ip_address(match.nextHopAddr), routerIface
                        ), self.arpTable
                    )
                else:
                    self.wait.add_entry(WEntry(
                            packet, ifacename, ipv4.dst, routerIface
                        ), self.arpTable
                    )

    def handle_packet(self, recv: switchyard.llnetbase.ReceivedPacket):
        _, ifaceName, packet = recv
        # TODO: your logic here
        arp = packet.get_header(Arp)
        eth = packet[Ethernet]
        if arp is not None: #ARP packet
            #Update cached ARP table
            self.arpTable[arp.senderprotoaddr] = arp.senderhwaddr
            if arp.operation == ArpOperation.Request: #Request
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
            elif arp.operation == ArpOperation.Reply: #Reply
                log_info("Receive an ARP reply.")
                self.wait.remove_entry(arp.senderprotoaddr)
            else: #Others
                log_info("Unknown ARP format.")
            #Print ARP table every time it is updated
            self.print_arpTable()
        elif eth.ethertype == EtherType.IPv4:
            packet.get_header(IPv4).ttl -= 1
            ipv4 = packet.get_header(IPv4)
            icmp = packet.get_header(ICMP)
            ether = packet.get_header(Ethernet)
            log_info("Receive an IPV4 packet.")
            if ipv4.dst in [iface.ipaddr for iface in self.interfaces]:
                if ipv4.protocol == IPProtocol.UDP:
                    log_info("Cannot handle UDP packet.")
                    packet = mk_icmperr(hwsrc=self.net.interface_by_name(ifaceName).ethaddr,
                        hwdst=ether.src,
                        ipsrc=self.net.interface_by_name(ifaceName).ipaddr,
                        ipdst=ipv4.src,
                        xtype=ICMPType.DestinationUnreachable,
                        xcode=3,
                        origpkt=packet
                    ) 
                elif icmp.icmptype == ICMPType.EchoRequest:
                    log_info("Receive an ICMP echo request.")
                    packet = mk_ping(hwsrc=ether.dst, hwdst=ether.src,
                        ipsrc=ipv4.dst, ipdst=ipv4.src,
                        reply=True, payload=icmp.icmpdata
                    )
                else:
                    log_info("Not an ICMP echo request.")
                    packet = mk_icmperr(hwsrc=self.net.interface_by_name(ifaceName).ethaddr,
                        hwdst=ether.src,
                        ipsrc=self.net.interface_by_name(ifaceName).ipaddr,
                        ipdst=ipv4.src,
                        xtype=ICMPType.DestinationUnreachable,
                        xcode=3,
                        origpkt=packet
                    )
            else:
                matched = False
                for fwEntry in self.forwardingTable:
                    netAddr = IPv4Network(str(fwEntry.networkAddr) +
                        "/" + str(fwEntry.subnetAddr), False
                    )
                    if ipv4.dst in netAddr:
                        matched = True
                        break
                if matched == False:
                    log_info("Router doesn't know where to forward.")
                    packet = mk_icmperr(hwsrc=self.net.interface_by_name(ifaceName).ethaddr,
                        hwdst=ether.src,
                        ipsrc=self.net.interface_by_name(ifaceName).ipaddr,
                        ipdst=ipv4.src,
                        xtype=ICMPType.DestinationUnreachable,
                        origpkt=packet
                    )
                elif ipv4.ttl == 0:
                    log_info("ICMP time exceeded.")
                    packet = mk_icmperr(hwsrc=self.net.interface_by_name(ifaceName).ethaddr,
                        hwdst=ether.src,
                        ipsrc=self.net.interface_by_name(ifaceName).ipaddr,
                        ipdst=ipv4.src,
                        xtype=ICMPType.TimeExceeded,
                        origpkt=packet
                    )
            self.send_ipv4(packet, ifaceName)

    def start(self):
        '''A running daemon of the router.
        Receive packets until the end of time.
        '''
        while True:
            self.update_queue()
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
