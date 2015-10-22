# Robby The Robot
A versatile simulator for programming various robotic tasks.  The simulator environment is programmed in C++ and SFML, while a library for scripting robots is being developed for Python.  Interprocess communication is done with pure sockets, so more language support is possible in the future.

### Current Features

A differential-drive robot can be accurately kinematically simulated and controlled (with or without acceleration).  A gyro sensor has also been implemented for reading rotational velocity.  Should work on Mac and Linux, but Windows is unlikely due to different socket-y stuff.

### Progress

Working on expanding functionality and extensibility.
