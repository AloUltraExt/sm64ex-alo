#include "libultra_internal.h"
#include "PR/rcp.h"

extern OSViContext *__osViNext;
extern OSViContext *__osViCurr;

void __osViSwapContext() {
    register OSViMode *s0;
    register OSViContext *s1;
    u32 origin;
    u32 hStart;
    u32 sp34;
    u32 field;
    register u32 s2;
    field = 0;
    s1 = __osViNext;
    s0 = s1->modep;
    field = IO_READ(VI_V_CURRENT_LINE_REG) & 1;
    s2 = osVirtualToPhysical(s1->buffer);
    origin = (s0->fldRegs[field].origin) + s2;
    if (s1->unk00 & 2) {
        s1->unk20 |= s0->comRegs.xScale & ~0xfff;
    } else {
        s1->unk20 = s0->comRegs.xScale;
    }
    if (s1->unk00 & 4) {
        sp34 = (u32)(s0->fldRegs[field].yScale & 0xfff);
        s1->unk2c = s1->unk24 * sp34;
        s1->unk2c |= s0->fldRegs[field].yScale & ~0xfff;
    } else {
        s1->unk2c = s0->fldRegs[field].yScale;
    }
    hStart = s0->comRegs.hStart;
    if (s1->unk00 & 0x20) {
        hStart = 0;
    }
    if (s1->unk00 & 0x40) {
        s1->unk2c = 0;
        origin = osVirtualToPhysical(s1->buffer);
    }
    if (s1->unk00 & 0x80) {
        s1->unk2c = (s1->unk28 << 0x10) & 0x3ff0000;
        origin = osVirtualToPhysical(s1->buffer);
    }
    IO_WRITE(VI_ORIGIN_REG, origin);
    IO_WRITE(VI_WIDTH_REG, s0->comRegs.width);
    IO_WRITE(VI_BURST_REG, s0->comRegs.burst);
    IO_WRITE(VI_V_SYNC_REG, s0->comRegs.vSync);
    IO_WRITE(VI_H_SYNC_REG, s0->comRegs.hSync);
    IO_WRITE(VI_LEAP_REG, s0->comRegs.leap);
    IO_WRITE(VI_H_START_REG, hStart);
    IO_WRITE(VI_V_START_REG, s0->fldRegs[field].vStart);
    IO_WRITE(VI_V_BURST_REG, s0->fldRegs[field].vBurst);
    IO_WRITE(VI_INTR_REG, s0->fldRegs[field].vIntr);
    IO_WRITE(VI_X_SCALE_REG, s1->unk20);
    IO_WRITE(VI_Y_SCALE_REG, s1->unk2c);
    IO_WRITE(VI_CONTROL_REG, s1->features);
    __osViNext = __osViCurr;
    __osViCurr = s1;
    *__osViNext = *__osViCurr;
}
