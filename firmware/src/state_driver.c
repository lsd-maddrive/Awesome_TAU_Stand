#include "state_driver.h"


msg_t stateDriverInit(Driver *sdp)
{
  if(sdp->state == STATE_UNINIT)
  {
    sdp->state = STATE_STOP;
    sdp->config = 0;
    return MSG_OK;
  }
  else return MSG_RESET;

}

msg_t stateDriverStart(Driver *sdp,DConfig *config)
{
  if(sdp->state == STATE_STOP)
    {
      measurementsStart();
      sdp->state = STATE_READY;
      sdp->config = config;
      measurementsStart();
      setNewLoad(sdp->config->load);
      return MSG_OK;
    }
  else
    {
      return MSG_RESET;
    }
}
msg_t stateDriverStop(Driver *sdp)
{
  if(sdp->state == STATE_READY)
    {
      sdp->state = STATE_STOP;
      return MSG_OK;
    }
  else return MSG_RESET;
}

msg_t stateDriverReinit(Driver *sdp,DConfig *config)
{
  if(sdp->state == STATE_STOP)
    {
      sdp->state = STATE_READY;
      sdp->config = config;
      return MSG_OK;
    }
  else return MSG_RESET;
}

msg_t stateDriverActivate(Driver *sdp)
{
  if(sdp->state == STATE_READY)
    {
      controllersStart();
      sdp->state = STATE_ACTIVE;
      return MSG_OK;
    }
  else return MSG_RESET;
}

msg_t stateDriverInactivate(Driver *sdp)
{
  if(sdp->state == STATE_ACTIVE)
    {
      sdp->state = STATE_READY;
      return MSG_OK;
    }
  else return MSG_RESET;
}
