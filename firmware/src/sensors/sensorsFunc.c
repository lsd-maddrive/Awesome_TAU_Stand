#include "measurements.h"

msg_t noneLoadInit(sendata_t* table_data)
{
  table_data[SEN_CURRENT].sen_status = SEN_ON;

  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t noneLoadAct(sendata_t* table_data)
{
  table_data[SEN_CURRENT].measur.prev=table_data[SEN_CURRENT].measur.current;
  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t firstLoadInit(sendata_t* table_data)
{
  table_data[SEN_CURRENT].sen_status = SEN_ON;

  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t firstLoadAct(sendata_t* table_data)
{
  table_data[SEN_CURRENT].measur.prev=table_data[SEN_CURRENT].measur.current;
  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t secondLoadInit(sendata_t* table_data)
{
  table_data[SEN_CURRENT].sen_status = SEN_ON;

  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t secondLoadAct(sendata_t* table_data)
{
  table_data[SEN_CURRENT].measur.prev=table_data[SEN_CURRENT].measur.current;
  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t thirdLoadInit(sendata_t* table_data)
{
  table_data[SEN_CURRENT].sen_status = SEN_ON;

  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}

msg_t thirdLoadAct(sendata_t* table_data)
{
  table_data[SEN_CURRENT].measur.prev=table_data[SEN_CURRENT].measur.current;
  table_data[SEN_CURRENT].measur.current=0;//get_something()
  return MSG_OK;
}
