Vagrant.configure("2") do |config|
  config.vm.box = "centos/7"
  config.vm.provision "shell", path: "provisioner.sh"
  config.vm.synced_folder ".", "/vagrant", type: "virtualbox"
end
