Imagine that you have a microcontroller that communicates to a generic system that may consist
of several other boards via UART. How do you ensure that each message is properly sent and
that its content is correct?
Now imagine that you receive a message and an interruption is triggered every time a new
information is received. Inside every message you have a different command, and for every
command you have different payloads, receiving positive and negative values.
Implement the interrupt and the parser functions in a generic way using the C language and share
this code through a public repository on GitHub. Low-level methods can be abstracted. If you
prefer, use frameworks like Arduino, ESP32 or even other market platforms in this low-level code
abstraction.