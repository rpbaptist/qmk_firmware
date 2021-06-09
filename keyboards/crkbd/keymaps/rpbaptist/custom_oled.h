#pragma once

#include "quantum.h"
#include "oled_driver.h"

extern uint8_t is_master;

oled_rotation_t oled_init_user(oled_rotation_t rotation);
void            render_crkbd_logo(void);
void            render_status(void);
void            oled_task_user(void);
