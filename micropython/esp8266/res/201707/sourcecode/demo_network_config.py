import network

# create instances
sta_if = network.WLAN(network.STA_IF)
ap_if = network.WLAN(network.AP_IF)

# to check 
s = sta_if.ifconfig()
a = ap_if.ifconfig()
print("Station Mode :",s)
print("AP Mode :",a)
