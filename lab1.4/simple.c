#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

#include <linux/string.h>

#define STUDENTS_NO 10

struct student{
        unsigned int ID;
        unsigned char name[50];
        unsigned int age;
}students[STUDENTS_NO];
int pos =0;

void add(int st_ID, char *st_name,int st_age){
        students[pos].ID= st_ID;
        strcpy(students[pos].name, st_name);
        students[pos].age=st_age;
        pos++;
}

void list(void){
        int i=0;
        while(i<pos){
                printk("ID: %d, Name: %s, Age: %d\n", students[i].ID, students[i].name,students[i].age);
                i++;
        }
}

// Custom functions.
void uptime(void);
void getSystemInfo(void);

// This function is called when the module is loaded.
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       uptime();
       getSystemInfo();
	add(0,"Daniela",20);
	add(1,"Angelica",15);
	add(2,"David",22);
	add(3,"Jessica",19);
	list();
       return 0;
}

// This function is called when the module is removed.
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}


// This functions gets the uptime
void uptime() {
  printk("Uptime: %i\n", jiffies_to_msecs(get_jiffies_64())/1000);
}


// This function gets the general system information
void getSystemInfo(){  
  struct new_utsname *buf;
  buf = utsname();

  printk("Nodename: %s\n",buf->nodename);
  printk("Machine: %s\n",buf->machine);
  printk("Sysname: %s\n",buf->sysname);
  printk("Release: %s\n",buf->release);
  printk("Version: %s\n",buf->version);
#ifdef __linux__
  printk("Domain Name: %s\n", buf->domainname); // GNU extension
#endif
}


/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
