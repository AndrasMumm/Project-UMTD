# Project-UMTD
Ultra Mega Tower Defense

An attempt on building a multiplayer Towerdefense game focusing on clean synchronization and scalability for funs and giggles.

Utilizes several "we are probably not the first to come up with, but we think it is a really smart way to do it" techniques a high amount of entities can (hopefully in the future) be syncronized across several clients while maintaining short input delays and intelligent agent logic and navigation.

Additionally all events are managed and spawned by the server while the clients only request certain actions and events, which can be verified by the server before being processed.\
This approach makes sure one does not need to trust the client, which secures the game against cheaters in online lobbies without needing any client side protection, which arguably is the most efficient client side detection.
