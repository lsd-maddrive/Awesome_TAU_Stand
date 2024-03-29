#include <controllers.h>

contraction_t contr_table_fun[NUMBER_CONTROL] = {
    [MANUAL_CONTROL] = {manualControlInit,manualControlUninit},
    [SLAVE_CONTROL] = {slaveControlInit,slaveControlUninit},
    [CONTROL2] = {0,0},
};

/**
 * @brief   Initialization and start of the controller.
 *
 * @param[in] set_contr   the selected regulator and the adjustable value                      .
 *
 * @init
 */
void controllersStart(controller_t* set_contr)
{
  motorInit();
  contr_table_fun[set_contr->type].contr_init((void*)&set_contr->statevariable);
}
/**
 * @brief   Stopping and removing thread the regulator .
 *
 * @api
 */
void controllersStop(controller_t* set_contr)
{
  contr_table_fun[set_contr->type].contr_uninit();
  motorUninit();
}
