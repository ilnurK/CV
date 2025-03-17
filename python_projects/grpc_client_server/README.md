# gRPC client-server, generating ships with random parameters, receiving verified ships by coordinates

<img src="source/_static/img.png" alt="battleship image" width="250" height="250" />


### Server
The server provide a response-streaming endpoint where it receives
a set of coordinates in the equatorial system and responds with
a stream of spaceship entries.

### Client
The client receives a set of coordinates in the equatorial system in
the CLI, receives back a stream of battleships checked by constraints,
displays them in the CLI and adds them to the data_ships and
data_officers databases (creates them if they do not exist).
The client can also scan the transmitted coordinates to search for
traitors - the same officers (with a unique combination of first name,
last name and rank) can be found on both allied and enemy ships,
after which the list_traitors command adds them to the table

## Install
1. Installing dependencies  
```pip -r requirements.txt```  
2. Generate grpc files  
To generate the pythons files for the client and service, run the following command in protobuf directory:  
```python3 -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. battleship.proto```  
3. Generate documentation file  
```make html```  

## Running
1. Run server  
Change directory to /server   
```./reporting_server.py```  
2. Run client  
Change directory to /client  
```./reporting_client.py 1 2 3 4 5 6```  
or use the script to send coordinates multiple times  
```./data_filler.sh 50```  
