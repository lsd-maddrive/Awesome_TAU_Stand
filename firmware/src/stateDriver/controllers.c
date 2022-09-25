#include <controllers.h>

contraction_t contr_table_fun[NUMBER_CONTROL] = {
    [NONE_CONTROL] = {contrNoneInit,contrNoneUninit},
    [PID] = {0,0},
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
  contr_table_fun[set_contr->type].contr_init((void*)&set_contr->param);
}
/**
 * @brief   Stopping and removing thread the regulator .
 *
 * @api
 */
void controllersStop(controller_t* set_contr)
{
  contr_table_fun[set_contr->type].contr_uninit;
  motorUninit();
}
