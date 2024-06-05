#include <linux/of.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/module.h>

#define DRIVER_NAME "jw_led"

struct jw_led {
    struct gpio_desc *gpio;
};

static int jw_led_probe(struct platform_device *pdev)
{
    struct jw_led *led;

    led = devm_kzalloc(&pdev->dev, sizeof(struct jw_led), GFP_KERNEL);
    if (!led)
        return -ENOMEM;

    platform_set_drvdata(pdev, led);

    led->gpio = devm_gpiod_get_index(&pdev->dev, "led", 0, GPIOD_OUT_LOW);
    if (IS_ERR(led->gpio)) {
        dev_err(&pdev->dev, "Failed to get jw_led/led-gpios property: %ld\n",
                PTR_ERR(led->gpio));
        return PTR_ERR(led->gpio);
    }

    /* 在这里可以添加其他代码来控制 GPIO17 */
    // gpiod_set_value(led->gpio, 1);

    return 0;
}

static const struct of_device_id jw_led_of_match[] = {
    { .compatible = "jw,jwled369", },
    { /* end of list */ },
};
MODULE_DEVICE_TABLE(of, jw_led_of_match);

static struct platform_driver jw_led_driver = {
    .probe = jw_led_probe,
    .driver = {
        .name = DRIVER_NAME,
        .of_match_table = jw_led_of_match,
    },
};
module_platform_driver(jw_led_driver);

MODULE_AUTHOR("jw.lee<jwlee36963@gmail.com>");
MODULE_DESCRIPTION("LED driver");
MODULE_LICENSE("GPL v2");