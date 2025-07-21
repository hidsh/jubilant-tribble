# usb logging
Refer to: https://zmk.dev/docs/development/usb-logging

## 1. Makefile
```
	west build  --pristine=always \
                :
	            --snippet=zmk-usb-logging \         <--!!!
                :
```

## 2. Kconfig.xxx
(optional)
```
CONFIG_LOG_PROCESS_THREAD_STARTUP_DELAY_MS 8000
```

## 3. View log
Refer to: https://github.com/thewh1teagle/serust

```
serust --product-id 615e        # 0x615e: zmk's default
```


# zmk studio
Refer to: 

## 1. Makefile
```
	west build  --pristine=always \
                :
	            --snippet=studio-rpc-usb-uart \     <--!!!
	            --  :
	                -DCONFIG_ZMK_STUDIO=y \         <--!!!
	                -DCONFIG_ZMK_STUDIO_LOCKING=n   <--!!!
```

## 2. .overlay
```
 :
#include <physical_layouts.dtsi>                                <--!!!
 :
    physical_layout0: physical_layout0 {
        compatible = "zmk,physical-layout";
          :
        transform = <&default_transform>;
        keys                                                    <--!!!
        //                          w   h   x   y  rot rx ry    <--!!!
            = <&key_physical_attrs 100 100   0   0  0   0  0>   <--!!!
            , <&key_physical_attrs 100 100 100   0  0   0  0>   <--!!!
            , <&key_physical_attrs 100 100   0 100  0   0  0>   <--!!!
            , <&key_physical_attrs 100 100 100 100  0   0  0>   <--!!!
            ;                                                   <--!!!
    };
```

## 3. usb port permission
```
$ ls -l /dev/ttyACM*
crw-rw---- 1 root uucp 166, 0 2025-05-23 17:30 /dev/ttyACM0
                  ^^^^

$ sudo usermod -aG uucp USER-NAME

$ groups USER-NAME
g : g wheel uucp ollama
            ^^^^
```

## 4. logout

logout and re-login to linux

## 5. connect to zmk.studio

1. open browser
2. naviage to https://zmk.studio
3. choose ttyACM*

# 
