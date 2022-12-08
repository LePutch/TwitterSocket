#!/bin/sh
gnome-terminal --title="SERVEUR" -- sh -c "make -C ./Server/; ./Server/server 5000" 
gnome-terminal  --title="CLIENT" -- sh -c "make -C ./Client/; ./Client/client 127.0.0.1 5000"
