#include <cstdlib>
#include <string>
#include <iostream>

int main (int argc, char *argv[]) {
std::string Sroot;
std::string Hboot;
std::string Aswap;

std::string LLusr;
std::string OThostname;

int pwd;
int pwdRoot;
int ui;
int linux_k;
int time;

std::cout << std::string(50, '-') << std::endl;
std::cout << "Welcome to Chimera installer\n";
std::cout << std::string(50, '-') << std::endl;

system("lsblk");

std::cout << "Please entar partition root! : ";
std::cin >> Sroot;

std::cout << "Please entar partition boot! : ";
std::cin >> Hboot;

std::cout << "Please entar partition swap! (or type empty if don't want swap ) : ";
std::cin >> Aswap;

std::cout << "name for hostname :";
std::cin >> OThostname;

std::cout << "name for user! :";
std::cin >> LLusr;

std::cout << "pasword for user! : ";
std::cin >> pwd;

std::cout << "pasword for root! : ";
std::cin >> pwdRoot;

std::cout << "var of linux-k\n" << "1>>linux-stable 2>>linux-lts";
std::cin >> linux_k;

system(("mkfs.ext4 /dev/" + Sroot).c_str());
system(("mkfs.fat -F32 /dev/" + Hboot).c_str());

if (Aswap.empty() || Aswap == "empty") { }
else { 
system(("mkswap /dev/" + Aswap).c_str()); 
system(("swapon /dev/" + Aswap).c_str()); }

system(("mount /dev/" + Sroot).c_str());
system(("mount -m /dev/" + Hboot + " /mnt/boot/efi").c_str());
system("chimera-bootstrap /mnt");
system("chimera-chroot /mnt");
system(("useradd -m -G wheel " + LLusr).c_str());


std::string setPwd = "echo " + LLusr + ":" + std::to_string(pwd) + " | chpasswd"; 
system(setPwd.c_str());

std::string cmd = "echo root:" + std::to_string(pwdRoot) + " | chpasswd"; 
system(cmd.c_str());

switch (linux_k) {
case 1: 
system("apk add linux-stable");
break;
case 2:
system("apk add linux-lts");
break;
default:
system("apk add linux-stable");}

system(("echo " + OThostname + " > /etc/hostname").c_str());

std::cout << "time zone ! : \n" << "Asia>>1 Africa>>2\n" << "Amarica>>3 Europe>>4 :";
std::cin >> time;

switch (time) {
case 1: 
std::cout << std::string(50, '-') << std::endl << "  city " << std::endl << std::string(50, '-') << std::endl;
std::cout << "Riyadh>>1 Dubai>>2\n" << "Baghdad>>3 Tokyo>>4\n" << "Singapore>>5 : ";
std::cin >> time;
switch (time) {
case 1: system("ln -sf /usr/share/zoneinfo/Asia/Riyadh /etc/localtime"); break;
case 2: system("ln -sf /usr/share/zoneinfo/Asia/Dubai /etc/localtime"); break;
case 3: system("ln -sf /usr/share/zoneinfo/Asia/Baghdad /etc/localtime"); break;
case 4: system("ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime"); break;
case 5: system("ln -sf /usr/share/zoneinfo/Asia/Singapore /etc/localtime"); break;}
break;
case 2:
std::cout << std::string(50, '-') << std::endl << "  city " << std::endl << std::string(50, '-') << std::endl;
std::cout << "Cairo>>1 Casablanca>>2\n" << "Tunis>>3 Johannesburg>>4  : ";
std::cin >> time;
switch (time) {
case 1: system("ln -sf /usr/share/zoneinfo/Africa/Cairo /etc/localtime"); break;
case 2: system("ln -sf /usr/share/zoneinfo/Africa/Casablanca /etc/localtime"); break;
case 3: system("ln -sf /usr/share/zoneinfo/Africa/Tunis /etc/localtime"); break;
case 4: system("ln -sf /usr/share/zoneinfo/Africa/Johannesburg /etc/localtime"); break;}
break;
case 3: 
std::cout << std::string(50, '-') << std::endl << "  city " << std::endl << std::string(50, '-') << std::endl;
std::cout << "New_York>>1 Chicago>>2\n" << "Los_Angeles>>3 Sao_Paulo>>4 : ";
std::cin >> time;
switch (time) {
case 1: system("ln -sf /usr/share/zoneinfo/America/New_York /etc/localtime"); break;
case 2: system("ln -sf /usr/share/zoneinfo/America/Chicago /etc/localtime"); break;
case 3: system("ln -sf /usr/share/zoneinfo/America/Los_Angeles /etc/localtime"); break; 
case 4: system("ln -sf /usr/share/zoneinfo/America/Sao_Paulo /etc/localtime"); break;}
break;
case 4: 
std::cout << std::string(50, '-') << std::endl << "  city " << std::endl << std::string(50, '-') << std::endl;
std::cout << "London>>1  Paris>>2\n" << "Istanbul>>3 Moscow>>4 :";
std::cin >> time;
switch (time) {
case 1: system("ln -sf /usr/share/zoneinfo/Europe/London /etc/localtime"); break; 
case 2: system("ln -sf /usr/share/zoneinfo/Europe/Paris /etc/localtime"); break;
case 3: system("ln -sf /usr/share/zoneinfo/Europe/Istanbul /etc/localtime"); break;
case 4: system("ln -sf /usr/share/zoneinfo/Europe/Moscow /etc/localtime"); break;}
break;

case 5: system("ln -sf /usr/share/zoneinfo/UTC /etc/localtime");
break;}
system("exit");

system("genfstab -U /mnt");
system("genfstab -U /mnt >> /mnt/etc/fstab");
system("chimera-chroot");

system("apk add grub-x86_64-efi");
system(("grub install /dev/" + Hboot).c_str());
system("grub-mkconfig -o /boot/grub/grub.cfg");
system("reboot");

return 0;
} 
