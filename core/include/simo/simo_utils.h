/**
 * @file simo_utils.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdint.h>



typedef  void (*write_function_t)(char*,uint16_t);

typedef void(*task_function_t)(void*);

typedef void(*callback_t)(void);