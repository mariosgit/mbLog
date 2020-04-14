#pragma once

// for log output
// - allows simple redirect to another Serial (or whatever)
// - allows quick disable without uncommenting each Seral.print..
// - stream style

#include <Arduino.h>

// does not work with typedef :( ???
#ifndef MbLogOut
    #define MbLogOut Serial
#endif

class MbLog
{
public:
    MbLog() {}
    inline void begin() {}
    inline MbLog& bin() {_how = BIN; return *this;}
    inline MbLog& oct() {_how = OCT; return *this;}
    inline MbLog& dec() {_how = DEC; return *this;}
    inline MbLog& hex() {_how = HEX; return *this;}
    inline MbLog& dez(byte val) {_dez = val; return *this;}

    inline void print  (byte val, byte how = DEC) { MbLogOut.print(val,how); }
    inline void println(byte val, byte how = DEC) { MbLogOut.println(val,how); }
    inline void print  (uint16_t val, byte how = DEC) { MbLogOut.print(val,how); }
    inline void println(uint16_t val, byte how = DEC) { MbLogOut.println(val,how); }
    inline void print  (int16_t val, byte how = DEC) { MbLogOut.print(val,how); }
    inline void println(int16_t val, byte how = DEC) { MbLogOut.println(val,how); }
    inline void print  (uint32_t val, byte how = DEC) { MbLogOut.print(val,how); }
    inline void println(uint32_t val, byte how = DEC) { MbLogOut.println(val,how); }
    inline void print  (int32_t val, byte how = DEC) { MbLogOut.print(val,how); }
    inline void println(int32_t val, byte how = DEC) { MbLogOut.println(val,how); }
    inline void print  (const char *msg) { MbLogOut.print(msg); }
    inline void println(const char *msg) { MbLogOut.println(msg); }
    inline void print  (float val) { MbLogOut.print(val); }
    inline void println(float val) { MbLogOut.println(val); }
    inline void print  (double val) { MbLogOut.print(val); }
    inline void println(double val) { MbLogOut.println(val); }
    inline MbLog& operator<<(const char *msg) { MbLogOut.print(msg); return *this; };
    inline MbLog& operator<<(int val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(int32_t val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(uint32_t val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(byte val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(char val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(float val) { MbLogOut.print(val,_dez); return *this; };
    inline MbLog& operator<<(double val) { MbLogOut.print(val,_dez); return *this; };
    inline MbLog& operator<<(bool val) { MbLogOut.print(val,DEC); return *this; };

private:
    byte _how = DEC;
    byte _dez = 2;
};

extern MbLog LOG;
