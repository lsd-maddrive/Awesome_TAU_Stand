## Как пользоваться Modbus TCP на STM32F767ZI.

 1) Для запуска теста нужно установить define MODBUSTCP_TEST.
 2) Подключить STM32F767ZI к компьютеру через Ethernet напрямую либо через сетевой коммутатор.
 3) Установить настройки сети как показано на изображении.
   <p align="center">
  <img src="/Matlab GUI/pictures/Настройки.jpg" width=300/>
  </p>
  
 4) Попинговать плату, если пингуется то все подключилось. 
  
 
 5) Запустить приложение в App Designer "testgui.mlapp"
   <p align="center">
  <img src="/Matlab GUI/pictures/Приложение.jpg" width=300/>
  </p>
  
 6) Для работы приложения необходима библиотека MODBUS для Matlab.
