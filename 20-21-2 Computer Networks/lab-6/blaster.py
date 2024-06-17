#!/usr/bin/env python3

import time
from random import randint
import switchyard
from switchyard.lib.address import *
from switchyard.lib.packet import *
from switchyard.lib.userlib import *


class senderEntry:
    def __init__(self, pkt, seq):
        self.packet = pkt
        self.sequence = seq
        self.acked = False

class Blaster:
    def __init__(
            self,
            net: switchyard.llnetbase.LLNetBase,
            blasteeIp,
            num,
            length="100",
            senderWindow="5",
            timeout="300",
            recvTimeout="100"
    ):
        self.net = net
        # TODO: store the parameters
        self.blasteeIp = IPv4Address(blasteeIp)
        self.num = int(num)
        self.length = int(length)
        self.senderWindow = int(senderWindow)
        self.timeout = float(timeout) / 1000
        self.recvTimeout = float(recvTimeout) / 1000
        #store the printing stats
        self.totalTXtime = 0
        self.numOfreTX = 0
        self.numOfcoarseTO = 0
        self.throughput = 0
        self.goodput = 0
        #store my own variables
        self.window = []
        self.curSequence = 1
        self.LHS = 1
        self.RHS = 1
        self.startTime = time.time()
        self.lastUpdateTime = time.time()
        self.over = False

    def handle_packet(self, recv: switchyard.llnetbase.ReceivedPacket):
        _, _, packet = recv
        log_debug("I got a packet")
        sequence = int.from_bytes(packet[3].to_bytes()[:4], 'big')
        for entry in self.window:
            if entry.sequence == sequence:
                log_info("Ack for packet #{}".format(sequence))
                entry.acked = True
                self.goodput += self.length
        while len(self.window) > 0:
            if self.window[0].acked == True:
                self.LHS = self.window[0].sequence + 1
                self.window.pop(0)
                self.lastUpdateTime = time.time()
            else:
                break

    def handle_no_packet(self):
        log_debug("Didn't receive anything")
        found = False
        if (time.time() - self.lastUpdateTime) > self.timeout:
            for entry in self.window:
                if entry.acked == False:
                    found = True
                    log_info("Timeout packet #{}".format(entry.sequence))
                    self.net.send_packet('blaster-eth0', entry.packet)
                    self.numOfreTX += 1
                    self.throughput += self.length
                    break
        if found == True:
            self.numOfcoarseTO += 1
        elif self.RHS - self.LHS + 1 < self.senderWindow:
            if self.curSequence <= self.num:
                # Creating the headers for the packet
                pkt = Ethernet() + IPv4() + UDP()
                pkt[1].protocol = IPProtocol.UDP
                # Do other things here and send packet
                pkt[Ethernet].src = EthAddr('10:00:00:00:00:01')
                pkt[Ethernet].dst = EthAddr('20:00:00:00:00:01')
                pkt[IPv4].src = IPv4Address('192.168.100.1')
                pkt[IPv4].dst = self.blasteeIp
                seqNumber = self.curSequence.to_bytes(4, 'big')
                length = self.length.to_bytes(2, 'big')
                payload = 'payload'.ljust(self.length, '.').encode()
                pkt += seqNumber + length + payload
                self.RHS = self.curSequence
                log_info("Packet #{}".format(self.curSequence))
                self.window.append(senderEntry(pkt, self.curSequence))
                self.net.send_packet('blaster-eth0', pkt)
                self.curSequence += 1
                self.throughput += self.length
            else:
                if len(self.window) == 0:
                    self.over = True

    def start(self):
        '''A running daemon of the blaster.
        Receive packets until the end of time.
        '''
        while True:
            if self.over == True:
                break
            try:
                recv = self.net.recv_packet(timeout=1.0)
            except NoPackets:
                self.handle_no_packet()
                continue
            except Shutdown:
                break

            self.handle_packet(recv)
        self.totalTXtime = time.time() - self.startTime
        print("Total TX time: ", self.totalTXtime)
        print("Number of reTX: ", self.numOfreTX)
        print("Number of coarse TOs: ", self.numOfcoarseTO)
        print("Thoughput: ", self.throughput / self.totalTXtime)
        print("Goodput: ", self.goodput / self.totalTXtime)
        self.shutdown()

    def shutdown(self):
        self.net.shutdown()


def main(net, **kwargs):
    blaster = Blaster(net, **kwargs)
    blaster.start()
