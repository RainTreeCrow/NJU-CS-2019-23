#!/usr/bin/env python3

import time
import threading
from struct import pack
import switchyard
from switchyard.lib.address import *
from switchyard.lib.packet import *
from switchyard.lib.userlib import *


class Blastee:
    def __init__(
            self,
            net: switchyard.llnetbase.LLNetBase,
            blasterIp,
            num
    ):
        self.net = net
        # TODO: store the parameters
        self.blasterIp = IPv4Address(blasterIp)
        self.num = int(num)

    def handle_packet(self, recv: switchyard.llnetbase.ReceivedPacket):
        _, fromIface, packet = recv
        log_debug(f"I got a packet from {fromIface}")
        log_debug(f"Pkt: {packet}")
        rawSequence = packet[3].to_bytes()[:4]
        payloadLength = int.from_bytes(packet[3].to_bytes()[4:6], 'big')
        if payloadLength >= 8:
            rawPayload = packet[3].to_bytes()[6:14]
        else:
            rawPayload = packet[3].to_bytes()[6:]
            rawPayload += (0).to_bytes(8 - payloadLength, 'big')
        ack = Ethernet() + IPv4() + UDP()
        ack[1].protocol = IPProtocol.UDP
        ack[Ethernet].src = EthAddr('20:00:00:00:00:01')
        ack[Ethernet].dst = EthAddr('10:00:00:00:00:01')
        ack[IPv4].src = IPv4Address('192.168.200.1')
        ack[IPv4].dst = self.blasterIp
        ack += rawSequence
        ack += rawPayload
        sequence = int.from_bytes(packet[3].to_bytes()[:4], 'big')
        log_info("Sending ACK #{} to blaster".format(sequence))
        self.net.send_packet(fromIface, ack)

    def start(self):
        '''A running daemon of the blastee.
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

        self.shutdown()

    def shutdown(self):
        self.net.shutdown()


def main(net, **kwargs):
    blastee = Blastee(net, **kwargs)
    blastee.start()
