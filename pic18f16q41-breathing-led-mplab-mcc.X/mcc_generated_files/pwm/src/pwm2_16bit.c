/**
  PWM2_16BIT Generated Driver File
 
  @Company
    Microchip Technology Inc.
 
  @File Name
    pwm2_16bit.c
 
  @Summary
    This is the generated driver implementation file for the PWM2_16BIT driver
 
  @Description
    This source file provides APIs for driver for PWM2_16BIT.
    Generation Information :
        Driver Version    :  <!--Use existing driver version-->
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.20
        MPLAB             :  MPLABX 5.30
*/

/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "../pwm2_16bit.h"

//Pointers to PWM2_16BIT interrupt handlers
//User can use them in application code to initialize with custom ISRs
static void (*PWM2_16BIT_Slice1Output1_InterruptHandler)(void);   //SaP1IF and hence PWMxIF is set
static void (*PWM2_16BIT_Slice1Output2_InterruptHandler)(void);   //SaP2IF and hence PWMxIF is set
static void (*PWM2_16BIT_Period_InterruptHandler)(void);          //PWMxPIF is set
static void PWM2_16BIT_Slice1Output1_DefaultInterruptHandler(void);
static void PWM2_16BIT_Slice1Output2_DefaultInterruptHandler(void);
static void PWM2_16BIT_Period_DefaultInterruptHandler(void);

void PWM2_16BIT_Initialize(void)
{
     PWM2ERS = 0x0;

     PWM2CLK = 0x4;

     PWM2LDS = 0x0;

     PWM2PRL = 0x47;

     PWM2PRH = 0x1;

     PWM2CPRE = 0x0;

     PWM2PIPOS = 0x0;

     PWM2GIR = 0x0;

     PWM2GIE = 0x0;

     PWM2S1CFG = 0x0;

     PWM2S1P1L = 0xA4;

     PWM2S1P1H = 0x0;

     PWM2S1P2L = 0xA4;

     PWM2S1P2H = 0x0;
    
    //Clear PWM2_16BIT period interrupt flag
    PIR5bits.PWM2PIF = 0;
    
    //Clear PWM2_16BIT interrupt flag
    PIR5bits.PWM2IF = 0;
    
    //Clear PWM2_16BIT slice 1, output 1 interrupt flag
    PWM2GIRbits.S1P1IF = 0;
    
    //Clear PWM2_16BIT slice 1, output 2 interrupt flag
    PWM2GIRbits.S1P2IF = 0;
    
    //PWM2_16BIT interrupt enable bit
    PIE5bits.PWM2IE = 0;
    
    //PWM2_16BIT period interrupt enable bit
    PIE5bits.PWM2PIE = 0;
    
    //Set default interrupt handlers
    PWM2_16BIT_Slice1Output1_SetInterruptHandler(PWM2_16BIT_Slice1Output1_DefaultInterruptHandler);
    PWM2_16BIT_Slice1Output2_SetInterruptHandler(PWM2_16BIT_Slice1Output2_DefaultInterruptHandler);
    PWM2_16BIT_Period_SetInterruptHandler(PWM2_16BIT_Period_DefaultInterruptHandler);

     PWM2CON = 0x80;
}

void PWM2_16BIT_Enable()
{
    PWM2CON |= _PWM2CON_EN_MASK;
}

void PWM2_16BIT_Disable()
{
    PWM2CON &= (~_PWM2CON_EN_MASK);
}

void PWM2_16BIT_WritePeriodRegister(uint16_t periodCount)
{
    PWM2PRL = (uint8_t)periodCount;
    PWM2PRH= (uint8_t)(periodCount >> 8);
}

void PWM2_16BIT_SetSlice1Output1DutyCycleRegister(uint16_t registerValue)
{    
    PWM2S1P1L = (uint8_t)(registerValue);
    PWM2S1P1H = (uint8_t)(registerValue >> 8);
}

void PWM2_16BIT_SetSlice1Output2DutyCycleRegister(uint16_t registerValue)
{        
    PWM2S1P2L = (uint8_t)(registerValue);
    PWM2S1P2H = (uint8_t)(registerValue >> 8);
}

void PWM2_16BIT_LoadBufferRegisters(void)
{
    //Load the period and duty cycle registers on the next period event
    PWM2CONbits.LD = 1;
}

void PWM2_16BIT_PWMI_ISR(void)
{
    PIR5bits.PWM2IF = 0;
    if((PWM2GIEbits.S1P1IE == 1) && (PWM2GIRbits.S1P1IF == 1))
    {
        PWM2GIRbits.S1P1IF = 0;
        if(PWM2_16BIT_Slice1Output1_InterruptHandler != NULL)
            PWM2_16BIT_Slice1Output1_InterruptHandler();
    }
    else if((PWM2GIEbits.S1P2IE == 1) && (PWM2GIRbits.S1P2IF == 1))
    {
        PWM2GIRbits.S1P2IF = 0;
        if(PWM2_16BIT_Slice1Output2_InterruptHandler != NULL)
            PWM2_16BIT_Slice1Output2_InterruptHandler();
    }
}

void PWM2_16BIT_PWMPI_ISR(void)
{
    PIR5bits.PWM2PIF = 0;
    if(PWM2_16BIT_Period_InterruptHandler != NULL)
        PWM2_16BIT_Period_InterruptHandler();
}

void PWM2_16BIT_Slice1Output1_SetInterruptHandler(void (* InterruptHandler)(void))
{
    PWM2_16BIT_Slice1Output1_InterruptHandler = InterruptHandler;
}

void PWM2_16BIT_Slice1Output2_SetInterruptHandler(void (* InterruptHandler)(void))
{
    PWM2_16BIT_Slice1Output2_InterruptHandler = InterruptHandler;
}

void PWM2_16BIT_Period_SetInterruptHandler(void (* InterruptHandler)(void))
{
    PWM2_16BIT_Period_InterruptHandler = InterruptHandler;
}

static void PWM2_16BIT_Slice1Output1_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use PWM2_16BIT_Slice1Output1_SetInterruptHandler() function to use Custom ISR
}

static void PWM2_16BIT_Slice1Output2_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use PWM2_16BIT_Slice1Output2_SetInterruptHandler() function to use Custom ISR
}

static void PWM2_16BIT_Period_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use PWM2_16BIT_Period_SetInterruptHandler() function to use Custom ISR
}
