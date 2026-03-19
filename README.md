## CH347T Test  
I test ch347t module.  
Everything works fine.  
100kHz timing, clock stretch: yes, push-pull no  
<img width="1442" height="224" alt="image" src="https://github.com/user-attachments/assets/1a2f7790-eb9b-4765-a7ad-1c00023172c6" />  
  
400kHz timing, clock stretch: yes, push-pull no  
<img width="1469" height="228" alt="image" src="https://github.com/user-attachments/assets/7a37ed53-112a-4624-82de-c2a10534eef2" />  
  
400kHz timing, clock stretch: yes, push-pull yes  
<img width="1384" height="219" alt="image" src="https://github.com/user-attachments/assets/2dab0f9c-3594-4752-96c1-845ae99b142b" />  

Accurate delay can be set by api 'CH347I2C_SetDelaymS'  
This is a blocking function which will block your process for milisecond you set.  
The following picture shows a 10ms delay by the api.  
<img width="1613" height="224" alt="image" src="https://github.com/user-attachments/assets/b5f4f93c-7c4f-4836-bd47-b933fc3b543e" />




The example terminal output:  
<img width="662" height="1014" alt="image" src="https://github.com/user-attachments/assets/9908d77c-8dfd-4069-af38-e1b6d2c1284f" />


I'm using this module.  
<img width="545" height="517" alt="image" src="https://github.com/user-attachments/assets/06e45a1b-f5de-49e9-8ebe-a36682fc5619" />
