#!/usr/bin/python
#

import traceback
import sys
import time
import re
import random
import math
from datetime import datetime
from time import sleep
from jsonrpc import ServiceProxy
from jsonrpc.proxy import JSONRPCException
from jsonrpc.json import JSONDecodeException
import ConfigParser
Config = ConfigParser.ConfigParser()

def ConfigSectionMap(section):
    dict1 = {}
    options = Config.options(section)
    for option in options:
        try:
            dict1[option] = Config.get(section, option)
            if dict1[option] == -1:
                DebugPrint("skip: %s" % option)
        except:
            print("exception on %s!" % option)
            dict1[option] = None
    return dict1

config_file = "satoshidice.ini"
try:
	Config.read(config_file)
	BTCHOST = ConfigSectionMap("BitcoinRPC")['rpchost']
	BTCPORT = ConfigSectionMap("BitcoinRPC")['rpcport']
	BTCUSER = ConfigSectionMap("BitcoinRPC")['rpcuser']
	BTCPASS = ConfigSectionMap("BitcoinRPC")['rpcpass']
except ConfigParser.NoSectionError:
	ConfigFile = open(config_file,'w')
	Config.add_section('BitcoinRPC')
	Config.set('BitcoinRPC','rpchost',"127.0.0.1")
	Config.set('BitcoinRPC','rpcport',"8332")
	Config.set('BitcoinRPC','rpcuser',"user")
	Config.set('BitcoinRPC','rpcpass',"password")
	Config.write(ConfigFile)
	ConfigFile.close()
	Config.read(config_file)
	BTCHOST = ConfigSectionMap("BitcoinRPC")['rpchost']
	BTCPORT = ConfigSectionMap("BitcoinRPC")['rpcport']
	BTCUSER = ConfigSectionMap("BitcoinRPC")['rpcuser']
	BTCPASS = ConfigSectionMap("BitcoinRPC")['rpcpass']
except:
	ConfigFile = open(config_file,'w')
	Config.add_section('BitcoinRPC')
	Config.set('BitcoinRPC','rpchost',"127.0.0.1")
	Config.set('BitcoinRPC','rpcport',"8332")
	Config.set('BitcoinRPC','rpcuser',"user")
	Config.set('BitcoinRPC','rpcpass',"password")
	Config.read(config_file)
	BTCHOST = ConfigSectionMap("BitcoinRPC")['rpchost']
	BTCPORT = ConfigSectionMap("BitcoinRPC")['rpcport']
	BTCUSER = ConfigSectionMap("BitcoinRPC")['rpcuser']
	BTCPASS = ConfigSectionMap("BitcoinRPC")['rpcpass']
	
def ExitDice(sb, balc, tf):
	starting_balance = sb
	balance_c = balc
	total_fees = tf
	output =  "Starting Balance: %s" % starting_balance
	output += "Ending Balance  : %s" % balance_c
	output += "Total Fees: %s" % total_fees
	amt_won = balance_c - starting_balance
	output += "Net Change: %s" % amt_won
	print output
	sys.exit()

SERVER = "http://%s:%s@%s:%s" % (BTCUSER, BTCPASS, BTCHOST, BTCPORT)
RPC = ServiceProxy(SERVER)
RPC.settxfee(0.0005)


MIN_BET = 0.01
MAX_BET = 6
ADDRESS = '1dice8EMZmqKvrGE4Qc9bUFf9PX3xaYDp'

bet = MIN_BET
total_fees = 0
count = 0
count_won = 0
starting_balance = None

while (bet <= MAX_BET) and (count_won < 100):
	count += 1
	try:
		balance_a = RPC.getbalance("*", 0)
		if starting_balance is None: starting_balance = balance_a
		RPC.sendtoaddress(ADDRESS, bet)
		balance_b = RPC.getbalance("*", 0)
		
		fee = round(balance_a - balance_b - bet, 8)
		total_fees += fee
		
		output =  "Game # %s\n" % count
		output += "Balance: %s \t" % balance_a
		output += "Bet: %s \t" % bet
		output += "Fee: %s \t" % fee
		output += "Total Fees: %s\n" % round(total_fees, 8)
		output += "Balance: %s \t" % balance_b
		sys.stdout.write(output)
		sys.stdout.write("Waiting")
		
		balance_c = 0
		while balance_b >= balance_c:
			sleep(20)
			balance_c = RPC.getbalance("*", 0)
			sys.stdout.write(".")
		
		sys.stdout.write("\n")
		output = "Balance: %s \t" % balance_c
		sys.stdout.write(output)
		
		diff = balance_c - balance_b
		if diff > bet:
			bet = MIN_BET
			count_won += 1
			string = "Won! (%s out of %s)\n" % (count_won, count)
			sys.stdout.write(string)
		else:
			bet *= 2
			string = "Lose!\n"
			sys.stdout.write(string)
		
		sys.stdout.write("\n")
		
	except JSONRPCException, e:
		logit(e.error['message'])
	except KeyboardInterrupt:
		print "\nStopping..."
		ExitDice(starting_balance, balance_c, total_fees)
		

	
ExitDice()