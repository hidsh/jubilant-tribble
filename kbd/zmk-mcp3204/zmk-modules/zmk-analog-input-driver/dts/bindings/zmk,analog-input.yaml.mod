# File: dts/bindings/analog-input.yaml

description: ZMK Analog Input Driver

compatible: "zmk,analog-input"

include: base.yaml

properties:
  sampling-hz:
    type: int
    description: Optional sampling frequency in Hz


child-binding:
  description: Individual analog input channel
  properties:
    io-channels:
      required: true
      type: phandle-array
      description: ADC channel for this analog input
    mv-ref:
      type: int
      description: Reference voltage in millivolts
    mv-mid:
      type: int
      description: Center voltage in millivolts (used for neutral position)
    deadband:
      type: int
      description: Threshold for ignoring minor movements
