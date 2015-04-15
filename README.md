# Soundlamp

An experimental hardware-based echolocation aid for blind users. More details soon.

## Building

The only supported build method at the moment is via [Vagrant](https://www.vagrantup.com). After [downloading](https://www.vagrantup.com/downloads.html), run:

`vagrant up`

During the provisioning step, the VM reboots to load a new kernel with updated device drivers. When this has completed, run:

`vagrant ssh`

This places you in a shell within a newly-created virtual machine, with the Arduino development environment installed. Supported Arduino devices are available inside the VM and are hidden from the host environment. Project code is at _/vagrant_.

[Ino](http://www.inotool.org) is used to build Soundlamp. To build, run:

    cp etc/mozzi_config.h lib/mozzi
    ino build

If all is successful, run:

`ino upload`

to upload the firmware and start the code.