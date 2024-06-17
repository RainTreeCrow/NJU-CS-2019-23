#!/usr/bin/env python3

'''
Basic IPv4 router (static routing) in Python.
'''

import time
import switchyard
from switchyard.lib.userlib import *


class Router(object):
    def __init__(self, net: switchyard.llnetbase.LLNetBase):
        self.net = net
        # other initialization stuff here
        self.interfaces = net.interfaces()
        self.arpTable = {}

    def print_arpTable(self):
        print("----------------------------------")
        print("IP\t\t Mac Address")
        for ip, mac in self.arpTable.items():
            print(ip, "\t", mac)
        print("----------------------------------")

    def handle_packet(self, recv: switchyard.llnetbase.ReceivedPacket):
        _, ifaceName, packet = recv
        # TODO: your logic here
        arp = packet.get_header(Arp)
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
            elif arp.operation == 2: #Reply
                log_info("Receive an ARP reply.")
                #Nothing to do yet
            else: #Others
                log_info("Unknown ARP format.")
            #Print ARP table every time it is updated
            self.print_arpTable()
        else: #None ARP packet
            log_info("Not an ARP packet, dropped.")

    def start(self):
        '''A running daemon of the router.
        Receive packets until the end of time.
        '''
        while True:
            try:
                recv = self.net.recv_packet(timeout=1.0)
            except NoPackets:
                continue
            except Shutdown:
                break

            self.handle_packet(recv)

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
