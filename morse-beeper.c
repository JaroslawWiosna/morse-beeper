#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("MPL-2.0");
MODULE_AUTHOR("Jaroslaw Wiosna");
MODULE_DESCRIPTION("Morse Beeper");

static int __init hello_init(void)
{
    printk(KERN_INFO "Morse Beeper loaded\n");
    return 0;
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Cleaning up Morse Beeper.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
