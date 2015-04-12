# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  config.vm.box = "boxcutter/ubuntu1504"

  # If true, then any SSH connections made will enable agent forwarding.
  # Default value: false
  config.ssh.forward_agent = true

  config.vm.provider :virtualbox do |vb|
    vb.customize ["modifyvm", :id, "--usb", "on"]
    vb.customize ["modifyvm", :id, "--usbehci", "on"]
    vb.customize ["usbfilter", "add", 0, "--target", :id, "--vendorid", "0x2341", "--name", "ArduinoUno"]
  end

  config.vm.provision :shell, inline: """
    adduser vagrant dialout
    apt-get update
    apt-get install --no-install-recommends -y arduino python-pip picocom linux-image-extra-`uname -r`
    pip install ino
  """

end