sudo make install
sudo modprobe -rv rtl8723be
sudo modprobe -v rtl8723be ant_sel=2
num="$(ls /sys/class/net | awk '/^wl/')"
sudo ip link set $num up
sudo iw dev $num scan
echo "options rtl8723be ant_sel=2" | sudo tee /etc/modprobe.d/50-rtl8723be.conf
