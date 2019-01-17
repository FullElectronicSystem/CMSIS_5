#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_GPIO_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(0,1)  /* API version */


/****** GPIO Pin Mode *****/
#define ARM_GPIO_PIN_MODE_IN_OUT_POS        0
#define ARM_GPIO_PIN_MODE_IN_OUT_MASK       (3UL << ARM_GPIO_PIN_MODE_INOOUT_POS)
#define ARM_GPIO_PIN_MODE_INPUT             (0UL << ARM_GPIO_PIN_MODE_INOOUT_POS)   //!< Pin as input
#define ARM_GPIO_PIN_MODE_OUTPUT_PP         (1UL << ARM_GPIO_PIN_MODE_INOOUT_POS)   //!< Pin as output push-pull
#define ARM_GPIO_PIN_MODE_OUTPUT_OD         (2UL << ARM_GPIO_PIN_MODE_INOOUT_POS)   //!< Pin as output open drain
                                                                                    // Value 3 RFU
#define ARM_GPIO_PIN_MODE_PULLUP_POS        2
#define ARM_GPIO_PIN_MODE_PULLUP_MASK       (1UL << ARM_GPIO_PIN_MODE_PULLUP_POS)
#define ARM_GPIO_PIN_MODE_PULLUP            (0UL << ARM_GPIO_PIN_MODE_PULLUP_POS)   //!< Pin with pull up
#define ARM_GPIO_PIN_MODE_NO_PULLUP         (1UL << ARM_GPIO_PIN_MODE_PULLUP_POS)   //!< Pin without pull up

#define ARM_GPIO_PIN_MODE_PULLDW_POS        3
#define ARM_GPIO_PIN_MODE_PULLDW_MASK       (1UL << ARM_GPIO_PIN_MODE_PULLDW_POS)
#define ARM_GPIO_PIN_MODE_PULLDW            (0UL << ARM_GPIO_PIN_MODE_PULLDW_POS)  //!< Pin with pull down
#define ARM_GPIO_PIN_MODE_NO_PULLDW         (1UL << ARM_GPIO_PIN_MODE_PULLDW_POS)  //!< Pin without pull down

#define ARM_GPIO_PIN_MODE_EVENT_POS         4
#define ARM_GPIO_PIN_MODE_EVENT_MASK        ( 15UL     << ARM_GPIO_PIN_MODE_EVENT_POS)
#define ARM_GPIO_PIN_MODE_EVENT_RISING      ((1UL<<1) << ARM_GPIO_PIN_MODE_EVENT_POS)   //!< Pin rising generate an event : \ref ARM_GPIO_SignalEvent
#define ARM_GPIO_PIN_MODE_EVENT_FALLING     ((1UL<<2) << ARM_GPIO_PIN_MODE_EVENT_POS)   //!< Pin falling generate an event : \ref ARM_GPIO_SignalEvent
#define ARM_GPIO_PIN_MODE_EVENT_LOW         ((1UL<<3) << ARM_GPIO_PIN_MODE_EVENT_POS)   //!< Pin low generate an event : \ref ARM_GPIO_SignalEvent
#define ARM_GPIO_PIN_MODE_EVENT_HIGH        ((1UL<<4) << ARM_GPIO_PIN_MODE_EVENT_POS)   //!< Pin high generate an event : \ref ARM_GPIO_SignalEvent


/****** GPIO Pin State *****/
#define ARM_GPIO_PIN_STATE_LOW              0
#define ARM_GPIO_PIN_STATE_HIGH             1

/****** GPIO Pin State  *****/
#define ARM_GPIO_PIN_NUM_LOW (n)   (ARM_GPIO_PIN_STATE_HIGH << (n))   ///< GPIO PIN n LOW
#define ARM_GPIO_PIN_NUM_HIGH(n)   (ARM_GPIO_PIN_STATE_LOW  << (n))   ///< GPIO n HIGH

/****** GPIO Pin Number *****/
#define ARM_GPIO_PIN_NUM_MASK(n)   (1UL << (n))   ///< GPIO PIN Number/Mask for pin n  

/****** GPIO Event *****/
#define ARM_GPIO_EVENT_RISING  				(1UL << 0)  ///< GPIO rising event
#define ARM_GPIO_EVENT_FALLING 				(1UL << 1)  ///< GPIO falling event
#define ARM_GPIO_EVENT_LOW  	  			(1UL << 2)  ///< GPIO is low event
#define ARM_GPIO_EVENT_HIGH   				(1UL << 3)  ///< GPIO is high event

// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_GPIO_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          ARM_GPIO_CAPABILITIES ARM_GPIO_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_GPIO_CAPABILITIES

  \fn          int32_t ARM_GPIO_Initialize (ARM_GPIO_SignalEvent_t cb_event)
  \brief       Initialize GPIO Interface.
  \param[in]   cb_event  Pointer to \ref ARM_GPIO_SignalEvent
  \return      \ref execution_status

  \fn          int32_t ARM_GPIO_Uninitialize (void)
  \brief       De-initialize GPIO Interface.
  \return      \ref execution_status

  \fn          int32_t ARM_GPIO_PowerControl (ARM_POWER_STATE state)
  \brief       Control GPIO Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          SetPinMode
  \brief       Set pin mode
  \param[in]   pin_num Pin number
  \param[in]   mode mode to set
  \return      \ref execution_status

  \fn          SetPin
  \brief       Set pin state
  \param[in]   pin_num Pin number (0-31)
  \param[in]   state state to set (ARM_GPIO_PIN_STATE_LOW/ARM_GPIO_PIN_STATE_HIGH)
  \return      \ref execution_status

  \fn          GetPin
  \brief       Get pin state
  \param[in]   pin_num Pin number (0-31)
  \return      Pin state 

  \fn          SetPort
  \brief       Set multiple pin state
  \param[in]   pin_mask   Mask of all affected pin (\see ARM_GPIO_PIN_NUM_MASK)
  \param[in]   state_mask Stetes of all affected pin  (\see ARM_GPIO_PIN_NUM_LOW and \see ARM_GPIO_PIN_NUM_HIGH)
  \return      \ref execution_status

  \fn          GetPort
  \brief       Get multiple pin state
  \param[in]   pin_mask   Mask of all pin to read (\see ARM_GPIO_PIN_NUM_MASK)
  \return      Pin state mask

  \fn          void ARM_GPIO_SignalEvent (uint32_t pin_num, uint32_t event)
  \brief       Signal GPIO Events.
  \param[in]   pin_num pin number
  \param[in]   event \ref GPIO_events notification mask
  \return      none

*/


typedef void (*ARM_GPIO_SignalEvent_t) (uint32_t pin_num, uint32_t event);  ///< Pointer to \ref ARM_GPIO_SignalEvent : Signal GPIO Event.

/**
\brief GPIO Driver Capabilities.
*/
typedef struct _ARM_GPIO_CAPABILITIES {
  uint32_t event_rising     : 1;        ///< supports rising event
  uint32_t event_falling    : 1;        ///< supports falling event
} ARM_GPIO_CAPABILITIES;


/**
\brief Access structure of the GPIO Driver.
*/
typedef struct _ARM_DRIVER_GPIO {
  ARM_DRIVER_VERSION    (*GetVersion)      (void);                                    ///< Pointer to \ref ARM_GPIO_GetVersion : Get driver version.
  ARM_GPIO_CAPABILITIES (*GetCapabilities) (void);                                    ///< Pointer to \ref ARM_GPIO_GetCapabilities : Get driver capabilities.
  int32_t               (*Initialize)      (ARM_GPIO_SignalEvent_t cb_event);         ///< Pointer to \ref ARM_GPIO_Initialize : Initialize GPIO Interface.
  int32_t               (*Uninitialize)    (void);                                    ///< Pointer to \ref ARM_GPIO_Uninitialize : De-initialize GPIO Interface.
  int32_t               (*PowerControl)    (ARM_POWER_STATE state);                   ///< Pointer to \ref ARM_GPIO_PowerControl : Control GPIO Interface Power.
  int32_t               (*SetPinMode)      (uint32_t pin_num, uint32_t mode);         ///< Pointer to \ref ARM_GPIO_SetPinMode : Set pin mode
  int32_t               (*SetPin)          (uint32_t pin_num, uint32_t state);        ///< Pointer to \ref ARM_GPIO_SetPin : Set pin state
  int32_t               (*GetPin)          (uint32_t pin_num);                        ///< Pointer to \ref ARM_GPIO_GetPin : Get pin state
  int32_t               (*SetPort)         (uint32_t pin_mask, uint32_t state_mask);  ///< Pointer to \ref ARM_GPIO_SetPort : Set multiple pin state
  int32_t               (*GetPort)         (uint32_t pin_mask);                       ///< Pointer to \ref ARM_GPIO_GetPort : Get multiple pin state
  
} const ARM_DRIVER_GPIO;


#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H_ */
