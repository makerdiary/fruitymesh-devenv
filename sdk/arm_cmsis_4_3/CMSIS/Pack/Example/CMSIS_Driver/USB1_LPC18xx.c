/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        20. January 2015
 * $Revision:    V1.01
 *
 * Project:      USB common (Device and Host) module for NXP LPC18xx
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 1.01
 *    - Improved support for Host and Device
 *  Version 1.00
 *    - Initial release
 */

#include "LPC18xx.h"
#include "SCU_LPC18xx.h"

#include "Driver_USB.h"

#include "RTE_Device.h"
#include "RTE_Components.h"

volatile uint8_t USB1_role  = ARM_USB_ROLE_NONE;
volatile uint8_t USB1_state = 0;

#ifdef RTE_Drivers_USBH1
extern void USBH1_IRQ (void);
#endif
#ifdef RTE_Drivers_USBD1
extern void USBD1_IRQ (void);
#endif


// Common IRQ Routine **********************************************************

/**
  \fn          void USB1_IRQHandler (void)
  \brief       USB Interrupt Routine (IRQ).
*/
void USB1_IRQHandler (void) {
#if (defined(RTE_Drivers_USBH1) && defined(RTE_Drivers_USBD1))
  switch (USB1_role) {
#ifdef RTE_Drivers_USBH1
    case ARM_USB_ROLE_HOST:
      USBH1_IRQ ();
      break;
#endif
#ifdef RTE_Drivers_USBD1
    case ARM_USB_ROLE_DEVICE:
      USBD1_IRQ ();
      break;
#endif
    default:
      break;
  }
#else
#ifdef RTE_Drivers_USBH1
  USBH1_IRQ ();
#else
  USBD1_IRQ ();
#endif
#endif

}


// Public Functions ************************************************************

/**
  \fn          void USB1_PinsConfigure (void)
  \brief       Configure USB pins
*/
void USB1_PinsConfigure (void) {

  // Common (Device and Host) Pins
#if (RTE_USB1_IND0_PIN_EN)
  SCU_PinConfigure(RTE_USB1_IND0_PORT, RTE_USB1_IND0_BIT, RTE_USB1_IND0_FUNC);
#endif
#if (RTE_USB1_IND1_PIN_EN)
  SCU_PinConfigure(RTE_USB1_IND1_PORT, RTE_USB1_IND1_BIT, RTE_USB1_IND1_FUNC);
#endif

#if (RTE_USB_USB1_FS_PHY_EN)
#if (RTE_USB1_VBUS_PIN_EN)
  // Device Pin
  if (USB1_role == ARM_USB_ROLE_DEVICE) {
    SCU_PinConfigure(RTE_USB1_VBUS_PORT, RTE_USB1_VBUS_BIT, RTE_USB1_VBUS_FUNC | SCU_SFS_EPD | SCU_SFS_EZI);
  }
#endif
#endif

  // Host Pins
  if (USB1_role == ARM_USB_ROLE_HOST) {
#if (RTE_USB1_PPWR_PIN_EN)
    SCU_PinConfigure(RTE_USB1_PPWR_PORT, RTE_USB1_PPWR_BIT, RTE_USB1_PPWR_FUNC);
#endif
#if (RTE_USB1_PWR_FAULT_PIN_EN)
    SCU_PinConfigure(RTE_USB1_PWR_FAULT_PORT,RTE_USB1_PWR_FAULT_BIT, RTE_USB1_PWR_FAULT_FUNC);
#endif
  }

  // ULPI Pins
#if (RTE_USB_USB1_HS_PHY_EN)
  SCU_PinConfigure(RTE_USB1_ULPI_CLK_PORT, RTE_USB1_ULPI_CLK_BIT,  RTE_USB1_ULPI_CLK_FUNC);
  SCU_PinConfigure(RTE_USB1_ULPI_DIR_PORT, RTE_USB1_ULPI_DIR_BIT,  RTE_USB1_ULPI_DIR_FUNC);
  SCU_PinConfigure(RTE_USB1_ULPI_STP_PORT, RTE_USB1_ULPI_STP_BIT,  RTE_USB1_ULPI_STP_FUNC);
  SCU_PinConfigure(RTE_USB1_ULPI_NXT_PORT, RTE_USB1_ULPI_NXT_BIT,  RTE_USB1_ULPI_NXT_FUNC);
  SCU_PinConfigure(RTE_USB1_ULPI_D0_PORT,  RTE_USB1_ULPI_D0_BIT,   RTE_USB1_ULPI_D0_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D1_PORT,  RTE_USB1_ULPI_D1_BIT,   RTE_USB1_ULPI_D1_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D2_PORT,  RTE_USB1_ULPI_D2_BIT,   RTE_USB1_ULPI_D2_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D3_PORT,  RTE_USB1_ULPI_D3_BIT,   RTE_USB1_ULPI_D3_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D4_PORT,  RTE_USB1_ULPI_D4_BIT,   RTE_USB1_ULPI_D4_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D5_PORT,  RTE_USB1_ULPI_D5_BIT,   RTE_USB1_ULPI_D5_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D6_PORT,  RTE_USB1_ULPI_D6_BIT,   RTE_USB1_ULPI_D6_FUNC );
  SCU_PinConfigure(RTE_USB1_ULPI_D7_PORT,  RTE_USB1_ULPI_D7_BIT,   RTE_USB1_ULPI_D7_FUNC );
#endif
}

/**
  \fn          void USB1_PinsUnconfigure (void)
  \brief       Unconfigure USB pins
*/
void USB1_PinsUnconfigure (void) {

  // Common (Device and Host) Pins
#if (RTE_USB1_IND0_PIN_EN)
  SCU_PinConfigure(RTE_USB1_IND0_PORT, RTE_USB1_IND0_BIT, 0);
#endif
#if (RTE_USB1_IND1_PIN_EN)
  SCU_PinConfigure(RTE_USB1_IND1_PORT, RTE_USB1_IND1_BIT, 0);
#endif

#if (RTE_USB_USB1_FS_PHY_EN)
#if (RTE_USB1_VBUS_PIN_EN)
  // Device Pin
  if (USB1_role == ARM_USB_ROLE_DEVICE) {
    SCU_PinConfigure(RTE_USB1_VBUS_PORT, RTE_USB1_VBUS_BIT, 0);
  }
#endif
#endif

  // Host Pins
  if (USB1_role == ARM_USB_ROLE_HOST) {
#if (RTE_USB1_PPWR_PIN_EN)
    SCU_PinConfigure(RTE_USB1_PPWR_PORT, RTE_USB1_PPWR_BIT, 0);
#endif
#if (RTE_USB1_PWR_FAULT_PIN_EN)
    SCU_PinConfigure(RTE_USB1_PWR_FAULT_PORT,RTE_USB1_PWR_FAULT_BIT, 0);
#endif
  }

  // ULPI Pins
#if (RTE_USB_USB1_HS_PHY_EN)
  SCU_PinConfigure(RTE_USB1_ULPI_CLK_PORT, RTE_USB1_ULPI_CLK_BIT,  0);
  SCU_PinConfigure(RTE_USB1_ULPI_DIR_PORT, RTE_USB1_ULPI_DIR_BIT,  0);
  SCU_PinConfigure(RTE_USB1_ULPI_STP_PORT, RTE_USB1_ULPI_STP_BIT,  0);
  SCU_PinConfigure(RTE_USB1_ULPI_NXT_PORT, RTE_USB1_ULPI_NXT_BIT,  0);
  SCU_PinConfigure(RTE_USB1_ULPI_D0_PORT,  RTE_USB1_ULPI_D0_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D1_PORT,  RTE_USB1_ULPI_D1_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D2_PORT,  RTE_USB1_ULPI_D2_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D3_PORT,  RTE_USB1_ULPI_D3_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D4_PORT,  RTE_USB1_ULPI_D4_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D5_PORT,  RTE_USB1_ULPI_D5_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D6_PORT,  RTE_USB1_ULPI_D6_BIT,   0 );
  SCU_PinConfigure(RTE_USB1_ULPI_D7_PORT,  RTE_USB1_ULPI_D7_BIT,   0 );
#endif
}
