# mbLog - C++ std::iostream style console outputs.

It does not implement iostream, it just mimics it's interface. So you can write ```LOG <<output <<moreoutput;```, which sometimes is faster to write then all these prints.

## Install

Clone this repo to your libraries or lib folder. Or add it to .gitmodules ```git submodule add ADR lib/mbLog```.

## Use

```
#include <mbLog.h>

...

void loop()
{
    int bla = 5;
    LOG <<"write something.. bla=" <<bla <<"\n";
}
```

## Options

### Write somewhere else

Before including mbLog.h, define where to log to.. Defaults to "Serial" and thus it uses the Serial.printXY functions.
```
#define MbLogOut Serial1
#include <mbLog.h>
...
```
