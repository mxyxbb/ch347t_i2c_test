## CH347T Test  
I test ch347t module.  
Everything works fine.  
100kHz timing, clock stretch: yes, push-pull no  
<img width="1442" height="224" alt="image" src="https://github.com/user-attachments/assets/1a2f7790-eb9b-4765-a7ad-1c00023172c6" />  
  
400kHz timing, clock stretch: yes, push-pull no  
<img width="1469" height="228" alt="image" src="https://github.com/user-attachments/assets/7a37ed53-112a-4624-82de-c2a10534eef2" />  
  
400kHz timing, clock stretch: yes, push-pull yes  
<img width="1384" height="219" alt="image" src="https://github.com/user-attachments/assets/2dab0f9c-3594-4752-96c1-845ae99b142b" />  

          // enable stretch
          CH347I2C_SetStretch(0, TRUE);
          // set driver push-pull
          CH347I2C_SetDriverMode(0, 1);

The example terminal output:  
<img width="662" height="1014" alt="image" src="https://github.com/user-attachments/assets/9908d77c-8dfd-4069-af38-e1b6d2c1284f" />


I'm using this module.  
<img width="545" height="517" alt="image" src="https://github.com/user-attachments/assets/06e45a1b-f5de-49e9-8ebe-a36682fc5619" />
