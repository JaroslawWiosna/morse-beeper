#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/kd.h>
#include <linux/kmod.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include "/usr/include/asm-generic/fcntl.h"

MODULE_LICENSE("MPL-2.0");
MODULE_AUTHOR("Jaroslaw Wiosna");
MODULE_DESCRIPTION("Morse Beeper");

irq_handler_t irq_handler (int irq, void *dev_id, struct pt_regs *regs) {
    char* argv[4];
    char* envp[4]; 
    argv[0] = "/bin/bash";
    argv[1] = "-c";
    argv[2] = "play -n synth 0.1 sine 400 vol 0.5";
    argv[3] = NULL;

    envp[0] = "HOME=/";
    envp[1] = "TERM=linux";
    envp[2] = "PATH=/sbin:/usr/sbin:/bin:/usr/bin";
    envp[3] = NULL;

    static unsigned char scancode;
    scancode = inb(0x60);
    if ((scancode == 0x01) || (scancode == 0x81)) {
        printk("You pressed ESC\n");
    } else if (scancode == 0x3b) {
        printk("You pressed F1\n");
    } else if (scancode == 0x3c) {
        printk("You pressed F2\n");
    } else if (scancode == 0x3d) {
        call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
        printk("You pressed F3\n");
    } else if (scancode == 0x3e) {
        printk("You pressed F4\n");
    } else if (scancode == 0x3f) {
        printk("You pressed F5\n");
    } else if (scancode == 0x40) {
        printk("You pressed F6\n");
    } else if (scancode == 0x41) {
        printk("You pressed F7\n");
    } else if (scancode == 0x42) {
        printk("You pressed F8\n");
    }

    return (irq_handler_t) IRQ_HANDLED;
}

static int __init hello_init(void)
{
    int result;
    result = request_irq(
            1, 
            (irq_handler_t) irq_handler, 
            IRQF_SHARED, 
            "keyboard_stats_irq", 
            (void *)(irq_handler));
    printk(KERN_INFO "Morse Beeper loaded\n");
    return 0;
}

static void __exit hello_cleanup(void)
{
    free_irq(1, (irq_handler_t) irq_handler); 
    printk(KERN_INFO "Cleaning up Morse Beeper.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
