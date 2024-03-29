## Как пользоваться Modbus TCP на STM32F767ZI.

 1) Для запуска теста нужно установить define MODBUSTCP_TEST.
 2) Подключить STM32F767ZI к компьютеру через Ethernet напрямую либо через сетевой коммутатор.
 3) Установить настройки сети как показано на изображении.
   <p align="center">
  <img src="/modbusTCP/pictures/Настройки.jpg" width=300/>
  </p>
  
 4) Попинговать плату, если пингуется то все подключилось. Для проверки Modbus TCP запустить программу Modbuss Poll 
  
 [Modbuss Poll](https://www.modbustools.com/download.html)

 
 5) Выбрать желаемые регистры. Тут указывается адрес платы и адрес первого желаемого регистра и количество регистров на чтение.
   <p align="center">
  <img src="/modbusTCP/pictures/выбор регистров.jpg" width=300/>
  </p>
  
 6) Настроить подключение и выбрать период опроса.
   <p align="center">
  <img src="/modbusTCP/pictures/подключение.jpg" width=500/>
  </p>
  
 7) Если все получилось, будут отображаться регистры.
   <p align="center">
  <img src="/modbusTCP/pictures/чтение регистров.jpg" width=900/>
  </p>
  
 8) Для изменения значения регистра нужно на него нажать и ввести желаемое значение.
