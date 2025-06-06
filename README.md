# Tree-Data
Extremely simple system data get tool. 

## How to compile and run?
First of all make sure that you have gcc installed on your system:
  - Debian / Ubuntu and Debian-based:
      sudo apt install build-essential
  - Arch / Manjaro and Arch-based:
    sudo pacman -S base-devel
  - CentOS/ RHEL / Fedora and 
    sudo dnf install gcc gcc-c++ make
  - OpenSUSE and OpenSuse-based:
    sudo zypper install gcc gcc-c++ make

Than run: make -j$(nproc)
This will compile the project for you and it will make a.elf executable.

To run a.elf exectuable run: 
   ./a.elf

THAT'S IT!
