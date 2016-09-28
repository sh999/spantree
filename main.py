# main.py
# Simulate bridge forwarding behavior

class Config_Message:
	def __init__(self, x, y, z):
		self.root = x
		self.dist_root = y
		self.sender = z

	def print_config(self):
		print "<", self.root,",", self.dist_root,",", self.sender,">"

class Bridge:
	def __init__(self, line):
		self.bridge_id = int(line[0])	# Numeric ID of bridge
		self.lans = []					# What LANs are linked to this bridge
		self.other_bridges = [] 		# What other bridges are linked to this bridge 
		self.config_message = Config_Message(self.get_bridge_id(), 0, self.get_bridge_id())   # Default config message <ID, 0, ID>
		# print "Line is:x", line, "x"
		self.connect_bridge_with_lans(line)

	def connect_bridge_with_lans(self, line):
		for i in range(1,len(line)):	# If see letter, denote as a connected lan to bridge
			# print "Looking at item:", line[i]
			if (ord(line[i]) >= 65 and ord(line[i]) <= 90) or (ord(line[i]) >= 97 and ord(line[i]) <= 122):  # ASCII for letters (lower and uppercase)
				# print ord(line[i])
				self.lans.extend(line[i])
			else: 						# If see non-letter, don't update lan
				# print ord(line[i])
				continue

	def get_bridge_id(self):
		return self.bridge_id

	def send_bridge(self):
		print "Sending from bridge", self.bridge_id
		print "Bridge's config:", 
		self.config_message.print_config()

	def print_bridge(self):
		print "Bridge #", self.bridge_id
		print "\tLANs:"
		for i in self.lans:
			print "\t\t", i

class Network:
	def __init__(self, input_file):
		print "Creating network"
		self.bridges = []
		self.lans = []
		self.parse_input(input_file) 	# Creates bridges and lans
		self.commands = []

	def parse_input(self, input_file):
		print "parsing input file"
		for line in input_file:
			# self.parse_line(l)
			print "parsing line", line
			temp_bridge = Bridge(line)   	# Creates bridge obj, which gets set up with its lans
			self.bridges.extend([temp_bridge])   # Add to list of bridges in this network
			# self.create_bridge_network()	# After all bridges and respective lans are set up, connect bridges to each other
			self.record_lans(line)  		# From raw line, keep unique lan names

	def parse_line(self, line):
		print "parsing line", line
		temp_bridge = Bridge(line)   	# Creates bridge obj, which gets set up with its lans
		self.bridges.extend([temp_bridge])   # Add to list of bridges in this network
		# self.create_bridge_network()	# After all bridges and respective lans are set up, connect bridges to each other
		self.record_lans(line)  		# From raw line, keep unique lan names

	def record_lans(self, line):
		print "Recording lans..."
		for i in range(1,len(line)):	# If see letter, denote as a connected lan to bridge
			# print "Looking at item:", line[i]
			if (ord(line[i]) >= 65 and ord(line[i]) <= 90) or (ord(line[i]) >= 97 and ord(line[i]) <= 122):  # ASCII for letters (lower and uppercase)
				# print line[i]
				# print ord(line[i])
				self.lans.extend(line[i])
			else: 						# If see non-letter, don't update lan
				# print ord(line[i])
				continue

	def create_bridge_network(self):		# Connect bridges from what lan's they share	
		print "Creating bridge network..."


	def run_commands(self, commands):
		self.commands = commands.get_commands()
		for i in self.commands:
			# print "Running command", i
			self.find_bridge_and_send(i)

	def find_bridge_and_send(self, bridge_id): 	# Send bridge with id i
		print "From network, finding bridge to send:", bridge_id
		self.get_bridge(bridge_id)

	def get_bridge(self, bridge_id):  # Given string ID, return bridge obj. with that id
		for b in self.bridges:
			# print "get Bridge ID:", b.get_bridge_id()
			# print "query id:", bridge_id
			if int(bridge_id) == b.get_bridge_id():
				# print "match"
				b.send_bridge()
				break

	def print_network(self):
		for b in self.bridges:
			b.print_bridge()

class Commands:
	def __init__(self, input_file):
		print "Creating commands"
		self.all_commands = self.parse_input(input_file)

	def parse_input(self, input_file): 	# From string of numbers, make list of numbers
		nums = []
		for i in input_file:
			nums = [int(n) for n in i.split()]
		print "Nums:"
		for i in nums:
			print i
		return nums

	def print_commands(self):
		for i in self.all_commands:
			print i

	def get_commands(self):
		return self.all_commands

def main():
	lan_input = open("lan", "r")
	commands_input = open("com", "r")
	network = Network(lan_input)
	commands = Commands(commands_input)
	print "Network and commands after parsing:"
	network.print_network()
	print "Commands:"
	commands.print_commands()
	print "Running simulation"
	network.run_commands(commands)

main()