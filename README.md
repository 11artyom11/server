# Silver Leopard
Customizable Client-Server application, currently focused on chatting.

> **_NOTE:_**  Currently server and client are stored in one repository, but they are fully separatable and dont have any common dependencies.

> **_NOTE:_** Make sure you have openssl installed 




If not, you can install by command
```
sudo apt install libssl-dev
```

## To build project
- Clone repository from github
  ``` 
   $ git clone https://github.com/11artyom11/silverleopard.git
  ```
  -   After successful cloning make sure you have following dependencies installed

 - ### To build server
```
${ROOT}/silverleopard $ cd server/
${ROOT}/silverleopard/server $ cmake .
${ROOT}/silverleopard/server $ make [ -j | -k ] 
```

After you can find binary of server in ``` {ROOT}/silverleopard/server/bin/server/server/server_exe ``` file.

- ### To build client
```
${ROOT}/silverleopard $ cd client/
${ROOT}/silverleopard/client $ cmake .
${ROOT}/silverleopard/client $ make [ -j | -k ] 
```
After you can find binary of server in ``` {ROOT}/silverleopard/client/bin/client/cliient/client_exe ``` file.

#### to be continued....