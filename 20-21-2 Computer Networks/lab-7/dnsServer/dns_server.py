'''DNS Server for Content Delivery Network (CDN)
'''

import sys
from socketserver import UDPServer, BaseRequestHandler
from utils.dns_utils import DNS_Request, DNS_Rcode
from utils.ip_utils import IP_Utils
from datetime import datetime
import math
import random

import re
from collections import namedtuple


__all__ = ["DNSServer", "DNSHandler"]


class DnsEntry():
    def __init__(self, name, _type, values):
        self.domainName = name
        self.recordType = _type
        self.recordValues = values


class DNSServer(UDPServer):
    def __init__(self, server_address, dns_file, RequestHandlerClass, bind_and_activate=True):
        super().__init__(server_address, RequestHandlerClass, bind_and_activate=True)
        self._dns_table = []
        self.parse_dns_file(dns_file)
        
    def parse_dns_file(self, dns_file):
        # ---------------------------------------------------
        # TODO: your codes here. Parse the dns_table.txt file
        # and load the data into self._dns_table.
        # --------------------------------------------------
        with open(dns_file) as DnsFile:
            for line in DnsFile:
                entry = line.split()
                if entry:
                    self._dns_table.append(
                        DnsEntry(entry[0], entry[1], entry[2:])
                    )
        '''
        testFile = open("test.txt", "w")
        for entry in self._dns_table:
            testFile.write(entry.domainName + " ")
            testFile.write(entry.recordType + " ")
            for item in entry.recordValues:
                testFile.write(item + " ")
            testFile.write("\n")
        testFile.close()
        '''

    @property
    def table(self):
        return self._dns_table


class DNSHandler(BaseRequestHandler):
    """
    This class receives clients' udp packet with socket handler and request data. 
    ----------------------------------------------------------------------------
    There are several objects you need to mention:
    - udp_data : the payload of udp protocol.
    - socket: connection handler to send or receive message with the client.
    - client_ip: the client's ip (ip source address).
    - client_port: the client's udp port (udp source port).
    - DNS_Request: a dns protocl tool class.
    We have written the skeleton of the dns server, all you need to do is to select
    the best response ip based on user's infomation (i.e., location).

    NOTE: This module is a very simple version of dns server, called global load ba-
          lance dns server. We suppose that this server knows all the ip addresses of 
          cache servers for any given domain_name (or cname).
    """
    
    def __init__(self, request, client_address, server):
        self.table = server.table
        super().__init__(request, client_address, server)

    def get_response(self, request_domain_name):
        response_type, response_val = (None, None)
        # ------------------------------------------------
        # TODO: your codes here.
        # Determine an IP to response according to the client's IP address.
        #       set "response_ip" to "the best IP address".
        client_ip, _ = self.client_address
        for entry in self.table:
            entry_split = entry.domainName.split('.')
            request_split = request_domain_name.split('.')
            if entry_split[-1] == '':
                entry_split.pop()
            if request_split[-1] == '':
                request_split.pop()
            '''
            testFile = open("test.txt", "w")
            for item in entry_split:
                testFile.write(item + " ")
            testFile.write("\n")
            for item in request_split:
                testFile.write(item + " ")
            testFile.write("\n")
            testFile.close()
            '''
            if entry.domainName[0] == '*' and entry_split[(1 + len(request_split) - \
                len(entry_split)):] == request_split[1:] \
                or entry_split[0:] == request_split[0:]:
                response_type = str(entry.recordType)
                if entry.recordType == "CNAME":
                    response_val = str(entry.recordValues[0])
                elif entry.recordType == "A":
                    if (len(entry.recordValues) == 1):
                        response_val = str(entry.recordValues[0])
                    else:
                        client_la, client_long = IP_Utils.getIpLocation(client_ip)
                        if (client_la, client_long) == (None, None):
                            index = random.randint(0, len(entry.recordValues) - 1)
                            response_val = str(entry.recordValues[index])
                        else:
                            selected_ip = None
                            min_dist = float('inf')
                            for ip in entry.recordValues:
                                temp_la, temp_long = IP_Utils.getIpLocation(ip)
                                temp_dist = math.sqrt((temp_la - client_la) ** 2 +\
                                    (temp_long - client_long) ** 2)
                                if (temp_dist < min_dist):
                                    min_dist = temp_dist
                                    selected_ip = ip
                            response_val = str(selected_ip)
        # -------------------------------------------------
        return (response_type, response_val)

    def handle(self):
        """
        This function is called once there is a dns request.
        """
        ## init udp data and socket.
        udp_data, socket = self.request

        ## read client-side ip address and udp port.
        client_ip, client_port = self.client_address

        ## check dns format.
        valid = DNS_Request.check_valid_format(udp_data)
        if valid:
            ## decode request into dns object and read domain_name property.
            dns_request = DNS_Request(udp_data)
            request_domain_name = str(dns_request.domain_name)
            self.log_info(f"Receving DNS request from '{client_ip}' asking for "
                          f"'{request_domain_name}'")

            # get caching server address
            response = self.get_response(request_domain_name)

            # response to client with response_ip
            if None not in response:
                dns_response = dns_request.generate_response(response)
            else:
                dns_response = DNS_Request.generate_error_response(
                                             error_code=DNS_Rcode.NXDomain)
        else:
            self.log_error(f"Receiving invalid dns request from "
                           f"'{client_ip}:{client_port}'")
            dns_response = DNS_Request.generate_error_response(
                                         error_code=DNS_Rcode.FormErr)

        socket.sendto(dns_response.raw_data, self.client_address)

    def log_info(self, msg):
        self._logMsg("Info", msg)

    def log_error(self, msg):
        self._logMsg("Error", msg)

    def log_warning(self, msg):
        self._logMsg("Warning", msg)

    def _logMsg(self, info, msg):
        ''' Log an arbitrary message.
        Used by log_info, log_warning, log_error.
        '''
        info = f"[{info}]"
        now = datetime.now().strftime("%Y/%m/%d-%H:%M:%S")
        sys.stdout.write(f"{now}| {info} {msg}\n")
