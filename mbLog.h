#pragma once

// for log output
// - allows simple redirect to another Serial (or whatever)
// - allows quick disable without uncommenting each Seral.print..
// - stream style

#include <Arduino.h>

// #ifdef WITH_THREADS
// ksfhbvksjfbvjkfsd
// #include <TeensyThreads.h>
// #define LK Threads::Scope m(_mutex)
// #else
#define LK 
// #endif

// does not work with typedef :( ???
#ifndef MbLogOut
    #define MbLogOut LK; Serial
#endif

class MbLog
{
public:
    enum FORMAT {
        bin, dec, oct, hex, endl
    };
    MbLog() {}
    inline void begin() {}
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
    inline void print  (uint64_t val, byte how = DEC) { MbLogOut.println((uint32_t)(val>>32),how); MbLogOut.println((uint32_t)(val&&0xffffffff),how); }
    inline void println(uint64_t val, byte how = DEC) { MbLogOut.println((uint32_t)(val>>32),how); MbLogOut.println((uint32_t)(val&&0xffffffff),how); }
    inline void print  (const char *msg) { MbLogOut.print(msg); }
    inline void println(const char *msg) { MbLogOut.println(msg); }
    inline void print  (float val) { MbLogOut.print(val); }
    inline void println(float val) { MbLogOut.println(val); }
    inline void print  (double val) { MbLogOut.print(val); }
    inline void println(double val) { MbLogOut.println(val); }
    inline MbLog& operator<<(const char *msg) { MbLogOut.print(msg); return *this; };
    inline MbLog& operator<<(int16_t val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(int val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(unsigned int val) { MbLogOut.print(val,_how); return *this; };
#ifndef ESP32
    inline MbLog& operator<<(int32_t val) { MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(uint32_t val) { MbLogOut.print(val,_how); return *this; };
#endif
    inline MbLog& operator<<(byte val) {
        if(_how == HEX) {
            sprintf(buffer, "%02x", val);
            MbLogOut.print(buffer);
        } else {
            MbLogOut.print(val,_how);
        }
        return *this;
    };
    inline MbLog& operator<<(float val) { MbLogOut.print(val,_dez); return *this; };
    inline MbLog& operator<<(double val) { MbLogOut.print(val,_dez); return *this; };
    inline MbLog& operator<<(bool val) { MbLogOut.print(val,DEC); return *this; };
    inline MbLog& operator<<(uint16_t val) {
        if(_how == HEX) {
            sprintf(buffer, "%04x", val);
            MbLogOut.print(buffer);
        } else {
            MbLogOut.print(val,_how);
        }
        return *this;
    };
    inline MbLog& operator<<(uint64_t val) {
        uint32_t upper = val>>32;
        uint32_t lower = val;
        sprintf(buffer, "%08lx %08lx", upper, lower);
        MbLogOut.print(buffer);
        return *this;
    };
    inline MbLog& operator<<(FORMAT val) {
        switch(val) {
            case bin:  { _how = BIN; return *this; }
            case oct:  { _how = OCT; return *this; }
            case dec:  { _how = DEC; return *this; }
            case hex:  { _how = HEX; return *this; }
            case endl: { MbLogOut.print("\n"); return *this; }
        }
        return *this;
    };

private:
    byte _how = DEC;
    byte _dez = 2;
    char buffer[40];
// #ifdef WITH_THREADS
//     Threads::Mutex _mutex;
// #endif
};

extern MbLog LOG;
