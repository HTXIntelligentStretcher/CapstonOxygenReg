#/bin/bash

rm /etc/dnsmasq.conf
cp /etc/dnsmasq.conf.orig /etc/dnsmasq.conf

rm /etc/dhcpcd.conf
cp /etc/dhcpcd.conf.orig /etc/dhcpcd.conf

systemctl disable hostapd
systemctl mask hostapd