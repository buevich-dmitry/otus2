To download and install the latest version, run:
```
wget -O custom_allocator-Linux.deb https://github.com/buevich-dmitry/otus2/releases/latest/download/custom_allocator-Linux.deb
sudo dpkg -i custom_allocator-Linux.deb
```

Also you can build the project locally:
```
./build.sh
sudo dpkg -i bin/custom_allocator-*-Linux.deb
```

Then run ip_filter app:
```
custom_allocator
```
