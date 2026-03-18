#include <stdio.h>
#include <windows.h>   // Include file for Win32 time functions
#include "CH347DLL.H"

/* the NI 845x handles */
HANDLE DeviceHandle;
HANDLE I2CHandle;

/*  error Function for NI 845x */
#ifndef errChk
#define errChk(fCall) if (Error = (fCall), Error < 0) {goto Error;} else
#endif

int main() {

    int    Error            = 0;

    mDeviceInforS DevInfor = {0};
    BOOL RetVal = FALSE;
    
    // I2C模式
    //// 位0-位2: I2C接口速度/SCL频率, 000=低速/20KHz,001=标准/100KHz(默认值),010=快速/400KHz,011=高速/750KHz,100=低速/50KHz,101=标准/200KHz，110=快速/1MHz
    // 其它保留,必须为0
    ULONG iMode = 0x01; // 设置为标准速度/100KHz
    UCHAR OutBuf[4096] = {0};
    UCHAR InBuf[4096] = {0};
    ULONG AckCount = 0;

    printf("\n\nSearching for Devices\n\n");
    /* find first device */
    errChk ((int)CH347OpenDevice (0));
    printf("Found first device on the USB. \n");

    /* open device handle */
    errChk ((int)CH347GetDeviceInfor (0, &DevInfor));
    printf("Chip mode: %d \n", DevInfor.ChipMode);
    printf("Speed:%s\n", DevInfor.UsbSpeedType?"HS":"FS");
    printf("Ver:%02X\n", DevInfor.FirewareVer);
    printf("DeviceID:%s\n", DevInfor.DeviceID);//HID\VID_1A86&PID_55DC&MI_01#8&1B2C087C&0&0000#
    printf("ProductString:%s\n", DevInfor.ProductString); //HID To UART+SPI+I2C
    printf("ManufacturerString:%s\n", DevInfor.ManufacturerString);//wch.cn
    
    errChk ((int)CH347SetTimeout (0, 500, 500));
    printf("Open device...success. \n\n");

    RetVal = CH347I2C_Set(0, iMode);
	printf("CH347 I2C Set clock %s\n",RetVal ? "succ" : "failure");

    RetVal = CH347I2C_SetStretch(0, TRUE);
	printf("CH347 I2C set stetching %s\n",RetVal ? "succ" : "failure");

	RetVal = CH347I2C_SetDriverMode(0, 1);
	printf("CH347 I2C set push-pull %s\n", RetVal ? "succ" : "failure");

    printf("CH347InitI2C %s\n\n",RetVal ? "succ" : "failure");

    //ACK测试，向I2C总线发送一个设备地址，查看是否有设备响应ACK
    OutBuf[0] = 0x59<<1; // I2C设备地址8bit
    RetVal = CH347StreamI2C_RetACK(0, 1, OutBuf, 0, NULL, &AckCount);
    printf("CH347 I2C write 0x59 ACK count: %d\n",  AckCount);
    OutBuf[0] = 0x60<<1; // I2C设备地址8bit
    RetVal = CH347StreamI2C_RetACK(0, 1, OutBuf, 0, NULL, &AckCount);
    printf("CH347 I2C write 0x60 ACK count: %d\n",  AckCount);

    // I2C总线扫描，向I2C总线发送所有可能的设备地址，查看哪些地址有设备响应ACK
    printf("\nStart I2C Bus Scan... \n");

    printf("\t ");
    for(int i=0; i<16; i++) // print column header
        printf("%02X ", i);

    printf("\n\n");

    for(int i=0; i<128; i++)
    {
        if(i%16 == 0)
            printf("%02X:\t", i);
        OutBuf[0] = i<<1; // I2C设备地址8bit
        RetVal = CH347StreamI2C_RetACK(0, 1, OutBuf, 0, NULL, &AckCount);
        if(AckCount)
            printf("%02X ", i);
        else
            printf("-- ");
        if(i%16 == 15)
            printf("\n");
    }
    printf("\n");

    OutBuf[0] = 0x60<<1; // I2C设备地址8bit
    OutBuf[1] = 0x00; // 寄存器地址
    OutBuf[2] = 0x55; // 待写入的数据
    RetVal = CH347StreamI2C_RetACK(0, 3, OutBuf, 0, NULL, &AckCount);
    printf("Write data: 0x%02X 0x%02X 0x%02X\n", OutBuf[0], OutBuf[1], OutBuf[2]);
    printf("AckCount %d\n",AckCount);
    printf("CH347 I2C write %s\n", AckCount ? "succ" : "failure");
    printf("\n");
    
    OutBuf[0] = 0x60<<1; // I2C设备地址8bit
    OutBuf[1] = 0x00; // 寄存器地址
    RetVal = CH347StreamI2C_RetACK(0, 2, OutBuf, 1, InBuf, &AckCount);
    printf("Read data: 0x%02X\n", InBuf[0]);
    printf("AckCount %d\n",AckCount);
    printf("CH347 I2C read %s\n", AckCount ? "succ" : "failure");
    printf("\n");

    OutBuf[0] = 0x60<<1; // I2C设备地址8bit
    OutBuf[1] = 0x00; // 寄存器地址
    OutBuf[2] = 0x55; // 待写入的数据
    OutBuf[3] = 0x56; // 待写入的数据
    OutBuf[4] = 0x57; // 待写入的数据
    OutBuf[5] = 0x58; // 待写入的数据
    RetVal = CH347StreamI2C_RetACK(0, 6, OutBuf, 0, NULL, &AckCount);
    printf("Write data: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n", OutBuf[0], OutBuf[1], OutBuf[2], OutBuf[3], OutBuf[4], OutBuf[5]);
    printf("AckCount %d\n",AckCount);
    printf("CH347 I2C write %s\n", AckCount ? "succ" : "failure");
    printf("\n");

    OutBuf[0] = 0x60<<1; // I2C设备地址8bit
    OutBuf[1] = 0x00; // 寄存器地址
    RetVal = CH347StreamI2C_RetACK(0, 2, OutBuf, 4, InBuf, &AckCount);
    printf("Read data: 0x%02X 0x%02X 0x%02X 0x%02X\n", InBuf[0], InBuf[1], InBuf[2], InBuf[3]);
    printf("AckCount %d\n",AckCount);
    printf("CH347 I2C read %s\n", AckCount ? "succ" : "failure");
    printf("\n");


    printf("Press Enter to close device and exit. \n");
    CH347CloseDevice (0);
    getchar();

Error:
   if (Error < 0)
   {
      CH347CloseDevice (0);
      printf("Device closed. \n");
      getchar();
   }
    return 0;
}