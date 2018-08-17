#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysinfo.h>
#include <linux/utsname.h>

void getUptime(void){
	struct sysinfo s_info;
	printk("Uptime: %li\n",s_info.uptime);
}

void getSystemInfo(void){
	printk(KERN_INFO "Kernel sysname: %s\n",utsname()->sysname);
	printk(KERN_INFO "Kernel nodename: %s\n",utsname()->nodename);
	printk(KERN_INFO "Kernel release: %s\n",utsname()->release);
	printk(KERN_INFO "Kernel version: %s\n",utsname()->version);
	printk(KERN_INFO "Kernel machine: %s\n",utsname()->machine);
}


/* This function is called when the module is loaded. */
int simple_init(void){
       printk(KERN_INFO "Aby's kernel is loading the module\n");

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Aby's kernel is removing the module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

