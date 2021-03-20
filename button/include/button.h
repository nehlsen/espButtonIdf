/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2018 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#ifndef ESP_JUMPSTART__BUTTON_H_
#define ESP_JUMPSTART__BUTTON_H_

#include "iot_button.h"

#ifdef __cplusplus

/**
 * class of button
 * simple usage:
 * Button* btn = new Button(BUTTON_IO_NUM, BUTTON_ACTIVE_LEVEL);
 * btn->add_cb(BUTTON_CB_PUSH, button_tap_cb, (void*) push, 50 / portTICK_PERIOD_MS);
 * btn->add_custom_cb(5, button_press_5s_cb, NULL);
 * ......
 * delete btn;
 */
class Button
{
private:
    button_handle_t m_btn_handle;

    /**
     * prevent copy constructing
     */
    Button(const Button &);
    Button &operator = (const Button &);
public:

    /**
     * @brief constructor of Button
     *
     * @param gpio_num GPIO index of the pin that the button uses
     * @param active_level button hardware active level.
     *        For "BUTTON_ACTIVE_LOW" it means when the button pressed, the GPIO will read low level.
     */
    Button(gpio_num_t gpio_num, button_active_t active_level = BUTTON_ACTIVE_HIGH);

    ~Button();

    /**
     * @brief Register a callback function for a button_cb_type_t action.
     *
     * @param type callback function type
     * @param cb callback function for "TAP" action.
     * @param arg Parameter for callback function
     * @note
     *        Button callback functions execute in the context of the timer service task.
     *        It is therefore essential that button callback functions never attempt to block.
     *        For example, a button callback function must not call vTaskDelay(), vTaskDelayUntil(),
     *        or specify a non zero block time when accessing a queue or a semaphore.
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Parameter error
     */
    esp_err_t setEventCallback(button_cb_type_t type, button_cb cb, void *arg);

    /**
     * @brief Register a callback function for a serial trigger event.
     *
     * @param btn_handle handle of the button object
     * @param start_after_sec define the time after which to start serial trigger action
     * @param interval_tick serial trigger interval
     * @param cb callback function for "TAP" action.
     * @param arg Parameter for callback function
     * @note
     *        Button callback functions execute in the context of the timer service task.
     *        It is therefore essential that button callback functions never attempt to block.
     *        For example, a button callback function must not call vTaskDelay(), vTaskDelayUntil(),
     *        or specify a non zero block time when accessing a queue or a semaphore.
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Parameter error
     */
    esp_err_t setSerialCallback(button_cb cb, void *arg, TickType_t interval_tick, uint32_t start_after_sec);

    /**
     * @brief Callbacks invoked as timer events occur while button is pressed
     *
     * @param press_sec the callback function would be called if you press the button for a specified period of time
     * @param cb callback function for "PRESS and HOLD" action.
     * @param arg Parameter for callback function
     *
     * @note
     *        Button callback functions execute in the context of the timer service task.
     *        It is therefore essential that button callback functions never attempt to block.
     *        For example, a button callback function must not call vTaskDelay(), vTaskDelayUntil(),
     *        or specify a non zero block time when accessing a queue or a semaphore.
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Parameter error
     */
    esp_err_t addOnPressCallback(uint32_t press_sec, button_cb cb, void *arg);

    /**
     * @brief Single callback invoked according to the latest timer event on button release.
     *
     * @param press_sec the callback function would be called if you press the button for a specified period of time
     * @param cb callback function for "PRESS and RELEASE" action.
     * @param arg Parameter for callback function
     *
     * @note
     *        Button callback functions execute in the context of the timer service task.
     *        It is therefore essential that button callback functions never attempt to block.
     *        For example, a button callback function must not call vTaskDelay(), vTaskDelayUntil(),
     *        or specify a non zero block time when accessing a queue or a semaphore.
     * @return
     *     - ESP_OK Success
     *     - ESP_FAIL Parameter error
     */
    esp_err_t addOnReleaseCallback(uint32_t press_sec, button_cb cb, void *arg);

    /**
     * @brief Remove callback
     *
     * @param type callback function event type
     *
     * @return
     *     - ESP_OK Success
     */
    esp_err_t removeCallback(button_cb_type_t type);
};
#endif

#endif
