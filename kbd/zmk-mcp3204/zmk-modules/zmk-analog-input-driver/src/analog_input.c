// File: src/analog_input.c

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(zmk_analog_input, LOG_LEVEL_DBG);

#define ANALOG_INPUT_NODE DT_INST(0, zmk_analog_input)

#define ANALOG_INPUT_CHANNEL(n) DT_CHILD(ANALOG_INPUT_NODE, n)
#define ANALOG_INPUT_CTLR(n) DT_IO_CHANNELS_CTLR(ANALOG_INPUT_CHANNEL(n))
//#define ANALOG_INPUT_INPUT(n) DT_IO_CHANNELS_INPUT(ANALOG_INPUT_CHANNEL(n))
#define ANALOG_INPUT_INPUT(n) DT_IO_CHANNELS_CELL(ANALOG_INPUT_CHANNEL(n), 1)

enum {
    CH_X,
    CH_Y,
    CH_COUNT
};

struct analog_input_channel_config {
    const struct device *dev;
    uint8_t input;
};

static struct analog_input_channel_config ch_cfg[CH_COUNT] = {
    [CH_X] = {
        .dev = DEVICE_DT_GET(ANALOG_INPUT_CTLR(x_ch)),
        .input = ANALOG_INPUT_INPUT(x_ch),
    },
    [CH_Y] = {
        .dev = DEVICE_DT_GET(ANALOG_INPUT_CTLR(y_ch)),
        .input = ANALOG_INPUT_INPUT(y_ch),
    }
};

int analog_input_read(uint8_t ch, int16_t *out)
{
    const struct device *adc_dev = ch_cfg[ch].dev;
    uint8_t input = ch_cfg[ch].input;

    if (!device_is_ready(adc_dev)) {
        LOG_ERR("ADC device not ready");
        return -ENODEV;
    }

    struct adc_channel_cfg cfg = {
        .gain = ADC_GAIN_1,
        .reference = ADC_REF_INTERNAL,
        .acquisition_time = ADC_ACQ_TIME_DEFAULT,
        .channel_id = input,
    };

    int ret = adc_channel_setup(adc_dev, &cfg);
    if (ret) {
        LOG_ERR("ADC channel setup failed (%d)", ret);
        return ret;
    }

    int16_t buf;
    struct adc_sequence sequence = {
        .channels = BIT(input),
        .buffer = &buf,
        .buffer_size = sizeof(buf),
        .resolution = 12,
    };

    ret = adc_read(adc_dev, &sequence);
    if (ret == 0) {
        *out = buf;
        return 0;
    } else {
        LOG_ERR("ADC read failed (%d)", ret);
        return ret;
    }
}

