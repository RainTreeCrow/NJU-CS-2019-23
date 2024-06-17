#!/usr/bin/env python3

import time
import threading
from random import random

import switchyard
from switchyard.lib.address import *
from switchyard.lib.packet import *
from switchyard.lib.userlib import *


class Middlebox:
    def __init__(
            self,
            net: switchyard.llnetbase.LLNetBase,
            dropRate="0.19"
    ):
        self.net = net
        self.dropRate = float(dropRate)
        self.intf1 = "middlebox-eth0"
        #self.totalCount = 0
        #self.dropCount = 0

    def handle_packet(self, recv: switchyard.llnetbase.ReceivedPacket):
        _, fromIface, packet = recv
        sequence = int.from_bytes(packet[3].to_bytes()[:4], 'big')
        if fromIface == self.intf1:
            log_debug("Received from blaster")
            '''
            Received data packet
            Should I drop it?
            If not, modify headers & send to blastee
            '''
            #self.totalCount += 1
            rand = random()
            if rand <= self.dropRate:
                log_info("Dropped packet #{}".format(sequence))
                #self.dropCount += 1
            else:
                log_info("Sending packet #{} to blastee".format(sequence))
                packet[Ethernet].src = '40:00:00:00:00:02'
                packet[Ethernet].dst = '20:00:00:00:00:01'
                self.net.send_packet("middlebox-eth1", packet)
        elif fromIface == "middlebox-eth1":
            log_debug("Received from blastee")
            '''
            Received ACK
            Modify headers & send to blaster. Not dropping ACK packets!
            net.send_packet("middlebox-eth0", pkt)
            '''
            log_info("Sendinng ACK #{} to blaster".format(sequence))
            packet[Ethernet].src = '40:00:00:00:00:01'
            packet[Ethernet].dst = '10:00:00:00:00:01'
            self.net.send_packet("middlebox-eth0", packet)
        else:
            log_debug("Oops :))")

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
            #log_info("Received {} packets, dropped {}.".format(self.totalCount, self.dropCount))
        self.shutdown()

    def shutdown(self):
        self.net.shutdown()


def main(net, **kwargs):
    middlebox = Middlebox(net, **kwargs)
    middlebox.start()
