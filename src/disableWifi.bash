#/bin/bash

rm /etc/dnsmasq.conf
cp /etc/dnsmasq.conf.new /etc/dnsmasq.conf

rm /etc/dhcpcd.conf
cp /etc/dhcpcd.conf.new /etc/dhcpcd.conf

systemctl unmask hostapd
systemctl enable hostapd