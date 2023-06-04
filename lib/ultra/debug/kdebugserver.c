#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/rdb.h"
#include "macros.h"

#if LIBULTRA_VERSION <= OS_VER_D || !defined(_FINALROM)
static s32 debugState = 0;
static s32 numChars = 0;
static s32 numCharsToReceive = 0;

static u8 debugBuffer[0x100];
#endif

OSThread __osThreadSave;

#if LIBULTRA_VERSION <= OS_VER_D || !defined(_FINALROM)
UNUSED static void u32_to_string(u32 k, u8 *s) {
    s[0] = (k >> 0x18) & 0xff;
    s[1] = (k >> 0x10) & 0xff;
    s[2] = (k >> 0x8) & 0xff;
    s[3] = k & 0xff;
}

static u32 string_to_u32(u8 *s) {
    u32 k;

    k = (s[0] & 0xff) << 0x18;
    k |= (s[1] & 0xff) << 0x10;
    k |= (s[2] & 0xff) << 0x8;
    k |= (s[3] & 0xff);

    return k;
}

static void send_packet(u8 *s, s32 n) {
    rdbPacket pkt;
    s32 i;

    pkt.type = 2;

    for (pkt.length = n, i = 0; i < n; i++) {
        pkt.buf[i] = s[i];
    }
    *(volatile u32 *) RDB_BASE_REG = *(u32 *) &pkt;

    while (!(__osGetCause() & CAUSE_IP6)) {
        ;
    }
    *(volatile u32 *) RDB_READ_INTR_REG = 0;
}

static void send(u8 *buff, s32 len) {
    s32 i;
    s32 end;
    s32 rem;

    if (!__osRdbWriteOK) {
        while (!(__osGetCause() & CAUSE_IP6)) {
            ;
        }
        *(volatile u32 *) RDB_READ_INTR_REG = 0;
        __osRdbWriteOK = 1;
    }

    i = 0;
    rem = len % 3;
    end = len - rem;

    for (; i < end; i += 3) {
        send_packet(&buff[i], 3);
    }

    if (rem > 0) {
        send_packet(&buff[end], rem);
    }
}

static void process_command_memory(void) {
    u32 buff = string_to_u32(&debugBuffer[1]);
    u32 size = string_to_u32(&debugBuffer[5]);

    send((u8 *) (uintptr_t) buff, size);
}

static void process_command_register(void) {
    send((u8 *) &__osThreadSave.context, sizeof(__OSThreadContext));
}

void kdebugserver(u32 packet) {
    u32 i;
    rdbPacket pkt;

    *(u32 *) &pkt = packet;

    for (i = 0; i < pkt.length; i++) {
        debugBuffer[numChars] = pkt.buf[i];
        numChars++;
    }

    numCharsToReceive -= pkt.length;

    switch (debugState) {
        case 0:
            switch (pkt.buf[0]) {
                case 1:
                    debugState = 1;
                    numCharsToReceive = 9 - pkt.length;
                    break;
                case 2:
                    process_command_register();
                    debugState = 0;
                    numChars = 0;
                    numCharsToReceive = 0;
                    break;
                default:
                    debugState = 0;
                    numChars = 0;
                    numCharsToReceive = 0;
                    break;
            }
            break;
        case 1:
            if (numCharsToReceive <= 0) {
                if (debugBuffer[0] == 1) {
                    process_command_memory();
                    debugState = 0;
                    numChars = 0;
                    numCharsToReceive = 0;
                } else {
                    debugState = 0;
                    numChars = 0;
                    numCharsToReceive = 0;
                }
            }
            break;
        default:
            debugState = 0;
            numChars = 0;
            numCharsToReceive = 0;
            break;
    }
}
#endif
