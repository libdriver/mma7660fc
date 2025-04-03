### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(mma7660fc REQUIRED)
```

### 3. MMA7660FC

#### 3.1 Command Instruction

1. Show mma7660fc chip and driver information.

   ```shell
   mma7660fc (-i | --information)
   ```

2. Show mma7660fc help.

   ```shell
   mma7660fc (-h | --help)
   ```

3. Show mma7660fc pin connections of the current board.

   ```shell
   mma7660fc (-p | --port)
   ```

4. Run mma7660fc register test.

   ```shell
   mma7660fc (-t reg | --test=reg)
   ```

5. Run mma7660fc read test, num means test times. 

   ```shell
   mma7660fc (-t read | --test=read) [--times=<num>]
   ```
   
6. Run mma7660fc motion test, ms means timeout in ms. 

   ```shell
   mma7660fc (-t motion | --test=motion) [--timeout=<ms>]
   ```
   
7. Run mma7660fc read function, num means read times.

   ```shell
   mma7660fc (-e read | --example=read) [--times=<num>]
   ```
   
8. Run mma7660fc read function, ms means timeout in ms.

   ```shell
   mma7660fc (-e motion | --example=motion) [--timeout=<ms>]
   ```

#### 3.2 Command Example

```shell
./mma7660fc -i

mma7660fc: chip is NXP MMA7660FC.
mma7660fc: manufacturer is NXP.
mma7660fc: interface is IIC.
mma7660fc: driver version is 1.0.
mma7660fc: min supply voltage is 2.4V.
mma7660fc: max supply voltage is 3.6V.
mma7660fc: max current is 0.29mA.
mma7660fc: max temperature is 85.0C.
mma7660fc: min temperature is -40.0C.
```

```shell
./mma7660fc -p

mma7660fc: IIC interface SCL connected to GPIO3(BCM).
mma7660fc: IIC interface SDA connected to GPIO2(BCM).
mma7660fc: INT connected to GPIO17(BCM).
```

```shell
./mma7660fc -t reg

mma7660fc: chip is NXP MMA7660FC.
mma7660fc: manufacturer is NXP.
mma7660fc: interface is IIC.
mma7660fc: driver version is 1.0.
mma7660fc: min supply voltage is 2.4V.
mma7660fc: max supply voltage is 3.6V.
mma7660fc: max current is 0.29mA.
mma7660fc: max temperature is 85.0C.
mma7660fc: min temperature is -40.0C.
mma7660fc: start register test.
mma7660fc: mma7660fc_get_tilt_status test.
mma7660fc: tilt status is 0x00.
mma7660fc: check tilt status ok.
mma7660fc: mma7660fc_get_auto_sleep_status test.
mma7660fc: auto sleep status is false.
mma7660fc: check auto sleep status ok.
mma7660fc: mma7660fc_get_auto_wake_up_status test.
mma7660fc: auto wake up status is false.
mma7660fc: check auto wake up status ok.
mma7660fc: mma7660fc_set_sleep_count/mma7660fc_get_sleep_count test.
mma7660fc: set sleep count 103.
mma7660fc: check sleep count ok.
mma7660fc: mma7660fc_set_front_back_interrupt/mma7660fc_get_front_back_interrupt test.
mma7660fc: enable front back interrupt.
mma7660fc: check front back interrupt ok.
mma7660fc: disable front back interrupt.
mma7660fc: check front back interrupt ok.
mma7660fc: mma7660fc_set_up_down_right_left_interrupt/mma7660fc_get_up_down_right_left_interrupt test.
mma7660fc: enable up down right left interrupt.
mma7660fc: check up down right left interrupt ok.
mma7660fc: disable up down right left interrupt.
mma7660fc: check up down right left interrupt ok.
mma7660fc: mma7660fc_set_tap_interrupt/mma7660fc_get_tap_interrupt test.
mma7660fc: enable tap interrupt.
mma7660fc: check tap interrupt ok.
mma7660fc: disable tap interrupt.
mma7660fc: check tap interrupt ok.
mma7660fc: mma7660fc_set_auto_sleep_interrupt/mma7660fc_get_auto_sleep_interrupt test.
mma7660fc: enable auto sleep interrupt.
mma7660fc: check auto sleep interrupt ok.
mma7660fc: disable auto sleep interrupt.
mma7660fc: check auto sleep interrupt ok.
mma7660fc: mma7660fc_set_update_interrupt/mma7660fc_get_update_interrupt test.
mma7660fc: enable update interrupt.
mma7660fc: check update interrupt ok.
mma7660fc: disable update interrupt.
mma7660fc: check update interrupt ok.
mma7660fc: mma7660fc_set_shake_x_interrupt/mma7660fc_get_shake_x_interrupt test.
mma7660fc: enable shake x interrupt.
mma7660fc: check shake x interrupt ok.
mma7660fc: disable shake x interrupt.
mma7660fc: check shake x interrupt ok.
mma7660fc: mma7660fc_set_shake_y_interrupt/mma7660fc_get_shake_y_interrupt test.
mma7660fc: enable shake y interrupt.
mma7660fc: check shake y interrupt ok.
mma7660fc: disable shake y interrupt.
mma7660fc: check shake y interrupt ok.
mma7660fc: mma7660fc_set_shake_z_interrupt/mma7660fc_get_shake_z_interrupt test.
mma7660fc: enable shake z interrupt.
mma7660fc: check shake z interrupt ok.
mma7660fc: disable shake z interrupt.
mma7660fc: check shake z interrupt ok.
mma7660fc: mma7660fc_set_mode/mma7660fc_get_mode test.
mma7660fc: set mode test.
mma7660fc: check mode ok.
mma7660fc: set mode active.
mma7660fc: check mode ok.
mma7660fc: set mode standby.
mma7660fc: check mode ok.
mma7660fc: mma7660fc_set_auto_wake_up/mma7660fc_get_auto_wake_up test.
mma7660fc: enable auto wake up.
mma7660fc: check auto wake up ok.
mma7660fc: disable auto wake up.
mma7660fc: check auto wake up ok.
mma7660fc: mma7660fc_set_auto_sleep/mma7660fc_get_auto_sleep test.
mma7660fc: enable auto sleep.
mma7660fc: check auto sleep ok.
mma7660fc: disable auto sleep.
mma7660fc: check auto sleep ok.
mma7660fc: mma7660fc_set_sleep_counter_prescaler/mma7660fc_get_sleep_counter_prescaler test.
mma7660fc: set sleep counter prescaler 1.
mma7660fc: check sleep counter prescaler ok.
mma7660fc: set sleep counter prescaler 16.
mma7660fc: check sleep counter prescaler ok.
mma7660fc: mma7660fc_set_interrupt_pin_type/mma7660fc_get_interrupt_pin_type test.
mma7660fc: set interrupt pin type open drain.
mma7660fc: check interrupt pin type ok.
mma7660fc: set interrupt pin type push pull.
mma7660fc: check interrupt pin type ok.
mma7660fc: mma7660fc_set_interrupt_active_level/mma7660fc_get_interrupt_active_level test.
mma7660fc: set interrupt active level low.
mma7660fc: check interrupt active level ok.
mma7660fc: set interrupt active level high.
mma7660fc: check interrupt active level ok.
mma7660fc: mma7660fc_set_tap_detection_rate/mma7660fc_get_tap_detection_rate test.
mma7660fc: set tap detection rate 120.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 64.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 32.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 16.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 8.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 4.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 2.
mma7660fc: check tap detection rate ok.
mma7660fc: set tap detection rate 1.
mma7660fc: check tap detection rate ok.
mma7660fc: mma7660fc_set_auto_wake_rate/mma7660fc_get_auto_wake_rate test.
mma7660fc: set auto wake rate 32.
mma7660fc: check auto wake rate ok.
mma7660fc: set auto wake rate 16.
mma7660fc: check auto wake rate ok.
mma7660fc: set auto wake rate 8.
mma7660fc: check auto wake rate ok.
mma7660fc: set auto wake rate 1.
mma7660fc: check auto wake rate ok.
mma7660fc: mma7660fc_set_tilt_debounce_filter/mma7660fc_get_tilt_debounce_filter test.
mma7660fc: set tilt debounce filter disabled.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 2.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 3.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 4.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 5.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 6.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 7.
mma7660fc: check tilt debounce filter ok.
mma7660fc: set tilt debounce filter 8.
mma7660fc: check tilt debounce filter ok.
mma7660fc: mma7660fc_set_tap_detection_threshold/mma7660fc_get_tap_detection_threshold test.
mma7660fc: set tap detection threshold 6.
mma7660fc: check tap detection threshold ok.
mma7660fc: mma7660fc_set_tap_x_detection/mma7660fc_get_tap_x_detection test.
mma7660fc: enable tap x detection.
mma7660fc: check tap x detection ok.
mma7660fc: disable tap x detection.
mma7660fc: check tap x detection ok.
mma7660fc: enable tap y detection.
mma7660fc: check tap y detection ok.
mma7660fc: disable tap y detection.
mma7660fc: check tap y detection ok.
mma7660fc: enable tap z detection.
mma7660fc: check tap z detection ok.
mma7660fc: disable tap z detection.
mma7660fc: check tap z detection ok.
mma7660fc: mma7660fc_set_tap_pulse_debounce_count/mma7660fc_get_tap_pulse_debounce_count test.
mma7660fc: set tap pulse debounce count 105.
mma7660fc: check tap pulse debounce count ok.
mma7660fc: mma7660fc_tap_pulse_debounce_convert_to_register/mma7660fc_tap_pulse_debounce_convert_to_data test.
mma7660fc: tap pulse debounce 1.50ms.
mma7660fc: check tap pulse debounce 1.30ms.
mma7660fc: finish register test.
```

```shell
./mma7660fc -t read --times=3

mma7660fc: chip is NXP MMA7660FC.
mma7660fc: manufacturer is NXP.
mma7660fc: interface is IIC.
mma7660fc: driver version is 1.0.
mma7660fc: min supply voltage is 2.4V.
mma7660fc: max supply voltage is 3.6V.
mma7660fc: max current is 0.29mA.
mma7660fc: max temperature is 85.0C.
mma7660fc: min temperature is -40.0C.
mma7660fc: start read test.
mma7660fc: x is -0.80g.
mma7660fc: y is 0.47g.
mma7660fc: z is 0.28g.
mma7660fc: x is -0.84g.
mma7660fc: y is 0.38g.
mma7660fc: z is 0.28g.
mma7660fc: x is -0.84g.
mma7660fc: y is 0.47g.
mma7660fc: z is 0.23g.
mma7660fc: finish read test.
```
```shell
./mma7660fc -t motion --timeout=10000

mma7660fc: chip is NXP MMA7660FC.
mma7660fc: manufacturer is NXP.
mma7660fc: interface is IIC.
mma7660fc: driver version is 1.0.
mma7660fc: min supply voltage is 2.4V.
mma7660fc: max supply voltage is 3.6V.
mma7660fc: max current is 0.29mA.
mma7660fc: max temperature is 85.0C.
mma7660fc: min temperature is -40.0C.
mma7660fc: start motion test.
mma7660fc: irq front.
mma7660fc: irq back.
mma7660fc: irq left.
mma7660fc: irq right.
mma7660fc: irq down.
mma7660fc: irq up.
mma7660fc: irq tap.
mma7660fc: irq shake.
mma7660fc: irq auto sleep.
mma7660fc: irq auto wake up.
mma7660fc: finish motion test.
```

```shell
./mma7660fc -e read --times=3

mma7660fc: 1/3.
mma7660fc: x is -0.89g.
mma7660fc: y is 0.47g.
mma7660fc: z is 0.28g.
mma7660fc: 2/3.
mma7660fc: x is -0.84g.
mma7660fc: y is 0.47g.
mma7660fc: z is 0.28g.
mma7660fc: 3/3.
mma7660fc: x is -0.84g.
mma7660fc: y is 0.47g.
mma7660fc: z is 0.28g.
```
```shell
./mma7660fc -e motion --timeout=10000

mma7660fc: irq front.
mma7660fc: irq back.
mma7660fc: irq left.
mma7660fc: irq right.
mma7660fc: irq down.
mma7660fc: irq up.
mma7660fc: irq tap.
mma7660fc: irq shake.
mma7660fc: irq auto sleep.
mma7660fc: irq auto wake up.
mma7660fc: finish motion.
```

```shell
./mma7660fc -h

Usage:
  mma7660fc (-i | --information)
  mma7660fc (-h | --help)
  mma7660fc (-p | --port)
  mma7660fc (-t reg | --test=reg)
  mma7660fc (-t read | --test=read) [--times=<num>]
  mma7660fc (-t motion | --test=motion) [--timeout=<ms>]
  mma7660fc (-e read | --example=read) [--times=<num>]
  mma7660fc (-e motion | --example=motion) [--timeout=<ms>]

Options:
  -e <read | motion>, --example=<read | motion>
                                     Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
  -p, --port                         Display the pin connections of the current board.
  -t <reg | read | motion>, --test=<reg | read | motion>
                                     Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
      --timeout=<ms>                 Set timeout in ms.([default: 10000])
```

