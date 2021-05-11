#ifndef N64_MEM_ERROR_SCREEN_H
#define N64_MEM_ERROR_SCREEN_H

extern u8 gNotEnoughMemory;
void thread5_mem_error_message_loop(UNUSED void *arg);
Gfx *geo_display_error_message(u32 callContext, UNUSED struct GraphNode *node, UNUSED u32 unused);
u8 does_pool_end_lie_out_of_bounds(void *end);

#endif
