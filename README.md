# Music App for any music (and not only) services
This application is a browser. Without an interface, only the site page specified in url.txt . Without utl.txt the program won't start! The site URL should be in the first line.

## Requirements 
In order to build a program from source, you need cmake and qt (qtwebengine/qtwebkit)

### For Linux
```bash
$ git clone https://github.com/723mist/Music-App-for-any-music-services.git
$ cd Music-App-for-any-music-and-not-only-services
$ mkdir build 
$ cp url.txt build/
$ cd build 
$ cmake .. && make
$ ./MusicPlayer
