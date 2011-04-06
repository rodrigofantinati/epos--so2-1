// EPOS-- PC Real-Time Clock Mediator

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __pc_rtc_h
#define __pc_rtc_h

#include <rtc.h>

__BEGIN_SYS

// The mc146818 RTC used in PCs also features an alarm and
// a batery-backup RAM (CMOS)
class PC_RTC: public RTC_Common
{
private:
    typedef Traits<PC_RTC> _Traits;
//    static const Type_Id _TYPE = Type<PC_RTC>::TYPE;

    // 146818 I/O ports
    enum {
	ADDR	= 0x70,
	DATA	= 0x71
    };

    // 146818 addresses
    enum {
	SECONDS		= 0x00,
	ALARM_S		= 0x01,
	MINUTES		= 0x02,
	ALARM_M		= 0x03,
	HOURS		= 0x04,
	ALARM_H		= 0x05,
	WEEKDAY		= 0x06, // 1 = Sunday
	DAY		= 0x07,
	MONTH		= 0x08,
	YEAR		= 0x09,
	REG_A    	= 0x0a, // Control/Status Register A
	REG_B		= 0x0b, // Control/Status Register B
	REG_C		= 0x0c, // Control/Status Register C
	REG_D		= 0x0d, // Control/Status Register D
	CMOS_DIAGNOSTIC	= 0x0e, // POST diagnostic
	CMOS_POWER_DONW	= 0x0f, // Status of system power-down
	CMOS_FLOPPY	= 0x10,
	CMOS_DISK1	= 0x11,
	CMOS_DISK2	= 0x12,
		       // 0x13	is reserved
	CMOS_CONFIG	= 0x14,
	CMOS_MEM_LSB	= 0x15,
	CMOS_MEM_MSB	= 0x16,
	CMOS_EX_MEM_LSB	= 0x17,
	CMOS_EX_MEM_MSB	= 0x18,
		       // 0x19  until
		       // 0x2d	is reserved
	CMOS_CHK_LSB	= 0x2e,
	CMOS_CHK_MSB	= 0x2f,
	CMOS_OT_MEM_LSB	= 0x30,
	CMOS_OT_MEM_HSB	= 0x31,
	CENTURY		= 0x32
		       // 0x33  until
		       // 0x3f	is reserved
    };

    // Control/Status register A
    enum {
	INT_FREQ_MASK	= 0x0f, // Interrupt frequency
	TIME_FREQ_MASK	= 0x70, // Time frequency ?
	UPDATED		= 0x80, // Enable/disable time updates
	DEF_REG_A	= 0x26  // BIOS defaults (INT=1024Hz, TIME=32,768KHz)
    };

    // Control/Status register B
    enum {
	DST		= 0x01, // Daylight savings time
	HOUR_24		= 0x02, // Hour format 24/12
	BINARY		= 0x04, // Binary or BCD
	INT_MASK	= 0x70, // Interrupt masks
	INT_SECOND	= 0x10, // Every time update (second)
	INT_ALARM	= 0x20, // When alarm time is reached
  	INT_FREQ	= 0x40, // Periodic (freq in CRTL A)
	ENABLE		= 0x80, // Enable/disable time updates
	DEF_REG_B	= (ENABLE | BINARY | HOUR_24)
    };

    // Status register C
    enum {
	INT_STAT_MASK	= 0x70, // What caused an interrupt?
	INT_STAT_SECOND	= 0x10, // Time update (second)
	INT_STAT_ALARM	= 0x20, // Alarm
  	INT_STAT_FREQ	= 0x40  // Periodic
    };

    // Status register D
    enum {
  	BATERY = 0x80 // 0 -> low
    };

public:
    PC_RTC() {}
    ~PC_RTC() {}

    Seconds read();
    void write(const Seconds & time);

    static int init(System_Info *si);

private:
    unsigned char reg(unsigned char a) {
	IA32::out8(ADDR, a);
	return IA32::in8(DATA);
    }
    void reg(unsigned char a, unsigned char v) {
	IA32::out8(ADDR, a);
	IA32::out8(DATA, v);
    }
};

__END_SYS

#endif
