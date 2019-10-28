# smspva-api

an api wrapper for the smspva.com api.

## supported languages:
c++17

## supported (soon):
python 3.8
c#.net
PHP 7.3

## getting started

these instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

depends on the language, visit the section accordingly


## c++
```
//make sure the header files (http_request.hpp and the json folder) are present
//smspva.hpp
#include "smspva.hpp"

smspva::smspva api = smspva::smspva("YOUR_KEY_HERE");
```
you can then use the following methods
```
//get the current account balance as a double
double balance = api.get_balance();

//get the current user karma
int karma = api.get_karma();
```

more stuff coming soon

## features
handles all the annoying stuff for you, makes the api easier to use since you don't have to handle all of the web requests

## contributing
please be sure to make the http lib better, not really sure if this is a good solution, stole it from Mr. Sloan Kelly on YouTube

please create a pull request if you have ideas for new stuff.

## versioning

no versions but updates (sometimes)

## thanks to
Niels Lohmann [GitHub](https://github.com/nlohmann/) for his json library

## authors
* **Robert 'BaumFX'** - *made the stuff* - [website](https://rob.gg) - [GitHub](https://github.com/BaumFX)

## license

its like (insert current line amount) lines but dont say you made it, okay?
