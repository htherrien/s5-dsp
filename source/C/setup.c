/*******************************************************************************
 * Projet S5
 * @file    setup.c
 * @author  Hugo Therrien, Marc-Andr� Roireau
 * @date    29 novembre 2017
 * @version 0.2
 *
 * Contient toutes les fonctions d'initilisation du DSP
 *
 ******************************************************************************/

#include "setup.h"

#include <dsk6713_led.h>

#include "acquisitionSignal.h"
#include "dsk.h"
#include "moyenneMobile.h"
#include "correlations3Axes.h"

void setup(void)
{
    DSK6713_LED_init();
    configAndStartTimer0AsClock300Hz();
    configAndStartTimer1AsClock8000Hz();
}

void configAndStartTimer0AsClock10Hz(void)
{
    CTL0 &= ~0x00000080; /* Put clock in hold */
    PRD0  = 2812500;     /* Set clock frequency to 10 Hz */
    CTL0 |= 0x00000200; /* Set internal clock source */
    CTL0 |= 0x00000100; /* Set as clock mode */
    CTL0 |= 0x00000004; /* TSTAT is driven on TOUT */
    CTL0 |= 0x00000001; /* TOUT is a timer output pin */
    CTL0 |= 0x000000C0; /* Start timer */
}

void configAndStartTimer0AsClock30Hz(void)
{
    CTL0 &= ~0x00000080; /* Put clock in hold */
    PRD0  = 937500;     /* Set clock frequency to 30 Hz */
    CTL0 |= 0x00000200; /* Set internal clock source */
    CTL0 |= 0x00000100; /* Set as clock mode */
    CTL0 |= 0x00000004; /* TSTAT is driven on TOUT */
    CTL0 |= 0x00000001; /* TOUT is a timer output pin */
    CTL0 |= 0x000000C0; /* Start timer */
}

void configAndStartTimer0AsClock300Hz(void)
{
    CTL0 &= ~0x00000080; /* Put clock in hold */
    PRD0  = 93750;     /* Set clock frequency to 300 Hz */
    CTL0 |= 0x00000200; /* Set internal clock source */
    CTL0 |= 0x00000100; /* Set as clock mode */
    CTL0 |= 0x00000004; /* TSTAT is driven on TOUT */
    CTL0 |= 0x00000001; /* TOUT is a timer output pin */
    CTL0 |= 0x000000C0; /* Start timer */
}

void configAndStartTimer1AsClock8000Hz(void)
{
    CTL1 &= ~0x00000080; /* Put clock in hold */
    PRD1  = 3516;        /* Set clock frequency to 8000 Hz */
    CTL1 |= 0x00000200; /* Set internal clock source */
    CTL1 |= 0x00000100; /* Set as clock mode */
    CTL1 |= 0x00000004; /* TSTAT is driven on TOUT */
    CTL1 |= 0x00000001; /* TOUT is a timer output pin */
    CTL1 |= 0x000000C0; /* Start timer */
}

void pinConfig(GPIO_Handle* gpHandle, void* vectors)
{
    // Set pin4 as interrupt on falling edge
    GPIO_pinEnable(*gpHandle, GPIO_PIN4);
    GPIO_pinDirection(*gpHandle, GPIO_PIN4, GPIO_INPUT);
    GPIO_intPolarity(*gpHandle, GPIO_GPINT4, GPIO_FALLING);

    // Set pin5 as interrupt on falling edge
    GPIO_pinEnable(*gpHandle, GPIO_PIN5);
    GPIO_pinDirection(*gpHandle, GPIO_PIN5, GPIO_INPUT);
    GPIO_intPolarity(*gpHandle, GPIO_GPINT5, GPIO_FALLING);

    // Vap interrupt vectors
    IRQ_setVecs(vectors);

    // Enable PIN4 interrupt
    IRQ_map(IRQ_EVT_GPINT4, 4);
    IRQ_reset(IRQ_EVT_GPINT4);
    IRQ_enable(IRQ_EVT_GPINT4);

    // Enable PIN5 interrupt
    IRQ_map(IRQ_EVT_GPINT5, 5);
    IRQ_reset(IRQ_EVT_GPINT5);
    IRQ_enable(IRQ_EVT_GPINT5);
}
