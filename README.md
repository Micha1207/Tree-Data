# Tree-Data
Extremely simple system data get tool. 

### How to compile?
First of all make sure that you have `gcc` and `git` installed on your system:
  - Debian / Ubuntu and Debian-based:
      `sudo apt install build-essential git`
  - Arch / Manjaro and Arch-based:
    `sudo pacman -S base-devel git`
  - CentOS/ RHEL / Fedora and 
    `sudo dnf install gcc gcc-c++ make git`
  - OpenSUSE and OpenSuse-based:
    `sudo zypper install gcc gcc-c++ make git`

Than: `git clone https://github.com/Micha1207/Tree-Data.git`

Next: `cd Tree-Data` 

Than run: `make -j$(nproc)`
This will compile the project for you and it will make `a.elf` executable.

To run `a.elf` exectuable run: 
   `./a.elf`

THAT'S IT!

