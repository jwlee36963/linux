// hello_module.c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jw.lee");
MODULE_DESCRIPTION("A simple example module");

static int __init hello_module_init(void) {
    printk(KERN_INFO "jw: Hello, my module loaded.\n");
    return 0;
}

static void __exit hello_module_exit(void) {
    printk(KERN_INFO "jw: Goodbye, my module unloaded.\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);
