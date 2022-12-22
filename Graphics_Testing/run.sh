arduino-cli compile --fqbn arduino:megaavr:nona4809 --build-property compiler.cpp.extra_flags=-DHOST_BUILD=1 --output-dir BUILD -u -p/dev/ttyACM0 -v *.ino
