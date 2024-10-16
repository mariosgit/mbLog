#pragma once

// for log output
// - allows simple redirect to another Serial (or whatever)
// - allows quick disable without uncommenting each Seral.print..
// - stream style

#include <Arduino.h>

#ifdef WITH_THREADS
#include <TeensyThreads.h>
#define LK Threads::Scope m(_mutex);
#else
#define LK 
#endif

// does not work with typedef :( ???
#ifndef MbLogOut
    #define MbLogOut Serial
#endif

class MbLog
{
public:
#ifdef ARDUINO_ARCH_STM32
    typedef int how_t; // someone alsways needs spezial treatment :(
#else
    typedef uint8_t how_t;
#endif
    enum FORMAT {
        bin, dec, oct, hex, endl
    };
    MbLog() {}
    inline void begin() {}
    inline MbLog& dez(byte val) {_dez = val; return *this;}

    inline void print  (byte val, how_t how = DEC) { LK MbLogOut.print(val,how); }
    inline void println(byte val, how_t how = DEC) { LK MbLogOut.println(val,how); }
    inline void print  (uint16_t val, how_t how = DEC) { LK MbLogOut.print(val,how); }
    inline void println(uint16_t val, how_t how = DEC) { LK MbLogOut.println(val,how); }
    inline void print  (int16_t val, how_t how = DEC) { LK MbLogOut.print(val,how); }
    inline void println(int16_t val, how_t how = DEC) { LK MbLogOut.println(val,how); }
    inline void print  (uint32_t val, how_t how = DEC) { LK MbLogOut.print(val,how); }
    inline void println(uint32_t val, how_t how = DEC) { LK MbLogOut.println(val,how); }
    inline void print  (int32_t val, how_t how = DEC) { LK MbLogOut.print(val,how); }
    inline void println(int32_t val, how_t how = DEC) { LK MbLogOut.println(val,how); }
    inline void print  (uint64_t val, how_t how = DEC) { LK MbLogOut.println((uint32_t)(val>>32),how); MbLogOut.println((uint32_t)(val&&0xffffffff),how); }
    inline void println(uint64_t val, how_t how = DEC) { LK MbLogOut.println((uint32_t)(val>>32),how); MbLogOut.println((uint32_t)(val&&0xffffffff),how); }
    inline void print  (const char *msg) { LK MbLogOut.print(msg); }
    inline void println(const char *msg) { LK MbLogOut.println(msg); }
    inline void print  (float val) { LK MbLogOut.print(val); }
    inline void println(float val) { LK MbLogOut.println(val); }
    inline void print  (double val) { LK MbLogOut.print(val); }
    inline void println(double val) { LK MbLogOut.println(val); }
    inline MbLog& operator<<(const char *msg) { LK MbLogOut.print(msg); return *this; };
    inline MbLog& operator<<(int16_t val) { LK MbLogOut.print(val,_how); return *this; };
#ifdef TEENSYDUINO
    inline MbLog& operator<<(int val) { LK MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(unsigned int val) { LK MbLogOut.print(val,_how); return *this; };
#endif
#ifndef ESP32
    inline MbLog& operator<<(int32_t val) { LK MbLogOut.print(val,_how); return *this; };
    inline MbLog& operator<<(uint32_t val) { LK MbLogOut.print(val,_how); return *this; };
#endif
    inline MbLog& operator<<(byte val) {
        LK 
        if(_how == HEX) {
            sprintf(buffer, "%02x", val);
            MbLogOut.print(buffer);
        } else {
            MbLogOut.print(val,_how);
        }
        return *this;
    };
    inline MbLog& operator<<(float val) { LK MbLogOut.print(val,_dez); return *this; };
    inline MbLog& operator<<(double val) { LK MbLogOut.print(val,_dez); return *this; };
    inline MbLog& operator<<(bool val) { LK MbLogOut.print(val,DEC); return *this; };
    inline MbLog& operator<<(uint16_t val) {
        LK 
        if(_how == HEX) {
            sprintf(buffer, "%04x", val);
            MbLogOut.print(buffer);
        } else {
            MbLogOut.print(val,_how);
        }
        return *this;
    };
    inline MbLog& operator<<(uint64_t val) {
        LK 
        uint32_t upper = val>>32;
        uint32_t lower = val;
        sprintf(buffer, "%08lx %08lx", upper, lower);
        MbLogOut.print(buffer);
        return *this;
    };
    inline MbLog& operator<<(FORMAT val) {
        LK 
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
    how_t _how = DEC;
    how_t _dez = 2;
    char buffer[40];
#ifdef WITH_THREADS
    Threads::Mutex _mutex;
#endif
};

extern MbLog LOG;
