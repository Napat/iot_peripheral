import network

# create instances
sta_if = network.WLAN(network.STA_IF)
ap_if = network.WLAN(network.AP_IF)

sta_if.active(True)
ap_if.active(False)

cfg = ("192.168.2.155","255.255.255.0","192.168.2.1","8.8.8.8")
sta_if.config(cfg)
sta_if.connect("n3amedia_tenda","0870412804")

print(sta_if.isconnected())
print(sta_if.ifconfig()) 
