/******************************************************************************
 *  app.h (for LEGO Mindstorms EV3)
 *  Created on: 2017/06/07
 *  Definition of the Tasks
 *  Author: Jerry W
 *  like system's root "main frame", controls cycle tasks etc.
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"

/*
 *  Set priority
 */
#define MAIN_PRIORITY    TMIN_APP_TPRI + 1  /* main task priority */
#define DRIVER_PRIORITY  TMIN_APP_TPRI + 2
#define COMM_PRIORITY TMIN_APP_TPRI + 3

/*
 *  ターゲットに依存する可能性のある定数の定義
 */
#ifndef STACK_SIZE
#define STACK_SIZE      4096        /* タスクのスタックサイズ */
#endif /* STACK_SIZE */

/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void driver_task(intptr_t exinf);
extern void comm_task(intptr_t exinf);

extern void invoker_4_ms(intptr_t exinf);
extern void invoker_8_ms(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
