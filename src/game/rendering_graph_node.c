#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "engine/math_util.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "main.h"
#include "memory.h"
#include "print.h"
#include "rendering_graph_node.h"
#include "shadow.h"

#include "config.h"
#include "config/config_world.h"

/**
 * This file contains the code that processes the scene graph for rendering.
 * The scene graph is responsible for drawing everything except the HUD / text boxes.
 * First the root of the scene graph is processed when geo_process_root
 * is called from level_script.c. The rest of the tree is traversed recursively
 * using the function geo_process_node_and_siblings, which switches over all
 * geo node types and calls a specialized function accordingly.
 * The types are defined in engine/graph_node.h
 *
 * The scene graph typically looks like:
 * - Root (viewport)
 *  - Master list
 *   - Ortho projection
 *    - Background (skybox)
 *  - Master list
 *   - Perspective
 *    - Camera
 *     - <area-specific display lists>
 *     - Object parent
 *      - <group with 240 object nodes>
 *  - Master list
 *   - Script node (Cannon overlay)
 *
 */

s16 gMatStackIndex;
Mat4 gMatStack[32];
Mtx *gMatStackFixed[32];
#ifdef HIGH_FPS_PC
Mat4 gMatStackInterpolated[32];
Mtx *gMatStackInterpolatedFixed[32];
#endif

// ex-alo change
// Stores geo screen aspect ratio for obj_is_in_view
f32 sGeoAspectRatio;

u8 gCurrAnimType;
u8 gCurrAnimEnabled;
s16 gCurrAnimFrame;
#ifdef HIGH_FPS_PC
s16 gPrevAnimFrame;
#endif
f32 gCurrAnimTranslationMultiplier;
u16 *gCurrAnimAttribute;
s16 *gCurrAnimData;

struct AllocOnlyPool *gDisplayListHeap;

/* Rendermode settings for cycle 1 for all layers. */
struct RenderModeContainer renderModeTable_1Cycle[2] = {
    [RENDER_NO_ZB] = { {
        [LAYER_FORCE] = G_RM_OPA_SURF,
        [LAYER_OPAQUE] = G_RM_AA_OPA_SURF,
        [LAYER_OPAQUE_DECAL] = G_RM_AA_OPA_SURF,
        [LAYER_OPAQUE_INTER] = G_RM_AA_OPA_SURF,
        [LAYER_ALPHA] = G_RM_AA_TEX_EDGE,
        [LAYER_TRANSPARENT] = G_RM_AA_XLU_SURF,
        [LAYER_TRANSPARENT_DECAL] = G_RM_AA_XLU_SURF,
        [LAYER_TRANSPARENT_INTER] = G_RM_AA_XLU_SURF,
    } },
    [RENDER_ZB] = { {
        [LAYER_FORCE] = G_RM_ZB_OPA_SURF,
        [LAYER_OPAQUE] = G_RM_AA_ZB_OPA_SURF,
        [LAYER_OPAQUE_DECAL] = G_RM_AA_ZB_OPA_DECAL,
        [LAYER_OPAQUE_INTER] = G_RM_AA_ZB_OPA_INTER,
        [LAYER_ALPHA] = G_RM_AA_ZB_TEX_EDGE,
        [LAYER_TRANSPARENT] = G_RM_AA_ZB_XLU_SURF,
        [LAYER_TRANSPARENT_DECAL] = G_RM_AA_ZB_XLU_DECAL,
        [LAYER_TRANSPARENT_INTER] = G_RM_AA_ZB_XLU_INTER,
    } } };

/* Rendermode settings for cycle 2 for all layers. */
struct RenderModeContainer renderModeTable_2Cycle[2] = {
    [RENDER_NO_ZB] = { {
        [LAYER_FORCE] = G_RM_OPA_SURF2,
        [LAYER_OPAQUE] = G_RM_AA_OPA_SURF2,
        [LAYER_OPAQUE_DECAL] = G_RM_AA_OPA_SURF2,
        [LAYER_OPAQUE_INTER] = G_RM_AA_OPA_SURF2,
        [LAYER_ALPHA] = G_RM_AA_TEX_EDGE2,
        [LAYER_TRANSPARENT] = G_RM_AA_XLU_SURF2,
        [LAYER_TRANSPARENT_DECAL] = G_RM_AA_XLU_SURF2,
        [LAYER_TRANSPARENT_INTER] = G_RM_AA_XLU_SURF2,
    } },
    [RENDER_ZB] = { {
        [LAYER_FORCE] = G_RM_ZB_OPA_SURF2,
        [LAYER_OPAQUE] = G_RM_AA_ZB_OPA_SURF2,
        [LAYER_OPAQUE_DECAL] = G_RM_AA_ZB_OPA_DECAL2,
        [LAYER_OPAQUE_INTER] = G_RM_AA_ZB_OPA_INTER2,
        [LAYER_ALPHA] = G_RM_AA_ZB_TEX_EDGE2,
        [LAYER_TRANSPARENT] = G_RM_AA_ZB_XLU_SURF2,
        [LAYER_TRANSPARENT_DECAL] = G_RM_AA_ZB_XLU_DECAL2,
        [LAYER_TRANSPARENT_INTER] = G_RM_AA_ZB_XLU_INTER2,
    } } };

struct GraphNodeRoot *gCurGraphNodeRoot = NULL;
struct GraphNodeMasterList *gCurGraphNodeMasterList = NULL;
struct GraphNodePerspective *gCurGraphNodeCamFrustum = NULL;
struct GraphNodeCamera *gCurGraphNodeCamera = NULL;
struct GraphNodeObject *gCurGraphNodeObject = NULL;
struct GraphNodeHeldObject *gCurGraphNodeHeldObject = NULL;
u16 gAreaUpdateCounter = 0;

#ifdef F3DEX_GBI_2
LookAt lookAt;
#endif

#ifdef HIGH_FPS_PC
static Gfx *sPerspectivePos;
static Mtx *sPerspectiveMtx;

struct {
    Gfx *pos;
    void *mtx;
    void *displayList;
} gMtxTbl[GFX_POOL_SIZE_FIXED];
s32 gMtxTblSize;

static Gfx *sViewportPos;
static Vp sPrevViewport;

void mtx_patch_interpolated(void) {
    s32 i;

    if (sPerspectivePos != NULL) {
        gSPMatrix(sPerspectivePos, VIRTUAL_TO_PHYSICAL(sPerspectiveMtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    }

    for (i = 0; i < gMtxTblSize; i++) {
        Gfx *pos = gMtxTbl[i].pos;
        gSPMatrix(pos++, VIRTUAL_TO_PHYSICAL(gMtxTbl[i].mtx),
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPDisplayList(pos++, gMtxTbl[i].displayList);
    }

    if (sViewportPos != NULL) {
        Gfx *saved = gDisplayListHead;
        gDisplayListHead = sViewportPos;
        make_viewport_clip_rect(&sPrevViewport);
        gSPViewport(gDisplayListHead, VIRTUAL_TO_PHYSICAL(&sPrevViewport));
        gDisplayListHead = saved;
    }

    gMtxTblSize = 0;
    sPerspectivePos = NULL;
    sViewportPos = NULL;
}
#endif

/**
 * Process a master list node.
 */
void geo_process_master_list_sub(struct GraphNodeMasterList *node) {
    struct DisplayListNode *currList;
    s32 i;
    s32 enableZBuffer = (node->node.flags & GRAPH_RENDER_Z_BUFFER) != 0;
    struct RenderModeContainer *modeList = &renderModeTable_1Cycle[enableZBuffer];
    struct RenderModeContainer *mode2List = &renderModeTable_2Cycle[enableZBuffer];

    // @bug This is where the LookAt values should be calculated but aren't.
    // As a result, environment mapping is broken on Fast3DEX2 without the
    // changes below.
#ifdef F3DEX_GBI_2
    Mtx lMtx;
    guLookAtReflect(&lMtx, &lookAt, 0, 0, 0, /* eye */ 0, 0, 1, /* at */ 1, 0, 0 /* up */);
#endif

    if (enableZBuffer != 0) {
        gDPPipeSync(gDisplayListHead++);
        gSPSetGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }

    for (i = LAYER_FIRST; i < LAYER_COUNT; i++) {
        if ((currList = node->listHeads[i]) != NULL) {
            gDPSetRenderMode(gDisplayListHead++, modeList->modes[i], mode2List->modes[i]);
            while (currList != NULL) {
#ifdef HIGH_FPS_PC
                if ((u32) gMtxTblSize < sizeof(gMtxTbl) / sizeof(gMtxTbl[0])) {
                    gMtxTbl[gMtxTblSize].pos = gDisplayListHead;
                    gMtxTbl[gMtxTblSize].mtx = currList->transform;
                    gMtxTbl[gMtxTblSize++].displayList = currList->displayList;
                }
                gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transformInterpolated),
                          G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPDisplayList(gDisplayListHead++, currList->displayListInterpolated);
#else
                gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transform),
                          G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPDisplayList(gDisplayListHead++, currList->displayList);
#endif
                currList = currList->next;
            }
        }
    }
    if (enableZBuffer != 0) {
        gDPPipeSync(gDisplayListHead++);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }
}

#ifdef HIGH_FPS_PC
// Replaces a function call to another, which is why is not in mayus, unlike extra
#define geo_append_display_list(dl, layer) \
    geo_append_display_list_inter(dl, dl, layer);

#define GEO_APPEND_DISPLAY_LIST_EXTRA(dl, layer) \
    geo_append_display_list_inter((void *) VIRTUAL_TO_PHYSICAL(dl), (void *) VIRTUAL_TO_PHYSICAL(dl##Interpolated), layer)
#else
#define GEO_APPEND_DISPLAY_LIST_EXTRA(dl, layer) \
    geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(dl), layer)
#endif

/**
 * Appends the display list to one of the master lists based on the layer
 * parameter. Look at the RenderModeContainer struct to see the corresponding
 * render modes of layers.
 */
#ifdef HIGH_FPS_PC
void geo_append_display_list_inter(void *displayList, void *displayListInterpolated, s16 layer)
#else
void geo_append_display_list(void *displayList, s16 layer)
#endif
{

#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, &lookAt);
#endif
    if (gCurGraphNodeMasterList != 0) {
        struct DisplayListNode *listNode =
            alloc_only_pool_alloc(gDisplayListHeap, sizeof(struct DisplayListNode));

        listNode->transform = gMatStackFixed[gMatStackIndex];
        listNode->displayList = displayList;
#ifdef HIGH_FPS_PC
        listNode->transformInterpolated = gMatStackInterpolatedFixed[gMatStackIndex];
        listNode->displayListInterpolated = displayListInterpolated;
#endif
        listNode->next = 0;
        if (gCurGraphNodeMasterList->listHeads[layer] == 0) {
            gCurGraphNodeMasterList->listHeads[layer] = listNode;
        } else {
            gCurGraphNodeMasterList->listTails[layer]->next = listNode;
        }
        gCurGraphNodeMasterList->listTails[layer] = listNode;
    }
}

// ex-alo change
// simplify matrix and dl usage into functions (From HackerSM64)
void inc_mat_stack(void) {
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
#ifdef HIGH_FPS_PC
    Mtx *mtxInterpolated = alloc_display_list(sizeof(*mtxInterpolated));
#endif
    gMatStackIndex++;
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
#ifdef HIGH_FPS_PC
    mtxf_to_mtx(mtxInterpolated, gMatStackInterpolated[gMatStackIndex]);
    gMatStackInterpolatedFixed[gMatStackIndex] = mtxInterpolated;
#endif
}

void append_dl_and_return(struct GraphNodeDisplayList *node) {
    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }

    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }

    gMatStackIndex--;
}

/**
 * Process the master list node.
 */
void geo_process_master_list(struct GraphNodeMasterList *node) {
    s32 i;

    if (gCurGraphNodeMasterList == NULL && node->node.children != NULL) {
        gCurGraphNodeMasterList = node;
        for (i = LAYER_FIRST; i < LAYER_COUNT; i++) {
            node->listHeads[i] = NULL;
        }
        geo_process_node_and_siblings(node->node.children);
        geo_process_master_list_sub(node);
        gCurGraphNodeMasterList = NULL;
    }
}

/**
 * Process an orthographic projection node.
 */
void geo_process_ortho_projection(struct GraphNodeOrthoProjection *node) {
    if (node->node.children != NULL) {
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
        f32 left = (gCurGraphNodeRoot->x - gCurGraphNodeRoot->width) / 2.0f * node->scale;
        f32 right = (gCurGraphNodeRoot->x + gCurGraphNodeRoot->width) / 2.0f * node->scale;
        f32 top = (gCurGraphNodeRoot->y - gCurGraphNodeRoot->height) / 2.0f * node->scale;
        f32 bottom = (gCurGraphNodeRoot->y + gCurGraphNodeRoot->height) / 2.0f * node->scale;

        guOrtho(mtx, left, right, bottom, top, -2.0f, 2.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

        geo_process_node_and_siblings(node->node.children);
    }
}

#if WORLD_SCALE > 1
#define SCALE_WORLD_NODE(node) (node / (f32)WORLD_SCALE)
#else
#define SCALE_WORLD_NODE(node) node
#endif

/**
 * Process a perspective projection node.
 */
void geo_process_perspective(struct GraphNodePerspective *node) {
    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    if (node->fnNode.node.children != NULL) {
        u16 perspNorm;
        Mtx *mtx = alloc_display_list(sizeof(*mtx));

        sGeoAspectRatio = (f32) gCurGraphNodeRoot->width / (f32) gCurGraphNodeRoot->height;
#ifdef VERSION_EU
        sGeoAspectRatio *= 1.1f;
#endif

        guPerspective(mtx, &perspNorm, node->fov, sGeoAspectRatio, SCALE_WORLD_NODE(node->near), SCALE_WORLD_NODE(node->far), 1.0f);
#ifdef HIGH_FPS_PC
        if (gGlobalTimer == node->prevTimestamp + 1 && gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
            f32 fovInterpolated = (node->prevFov + node->fov) / 2.0f;
            Mtx *mtxInterpolated = alloc_display_list(sizeof(*mtxInterpolated));
            guPerspective(mtxInterpolated, &perspNorm, fovInterpolated, sGeoAspectRatio, SCALE_WORLD_NODE(node->near), SCALE_WORLD_NODE(node->far), 1.0f);
            gSPPerspNormalize(gDisplayListHead++, perspNorm);

            sPerspectivePos = gDisplayListHead;
            sPerspectiveMtx = mtx;
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtxInterpolated),
                      G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        } else {
            gSPPerspNormalize(gDisplayListHead++, perspNorm);
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        }
        node->prevFov = node->fov;
        node->prevTimestamp = gGlobalTimer;
#else
        gSPPerspNormalize(gDisplayListHead++, perspNorm);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
#endif

        gCurGraphNodeCamFrustum = node;
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamFrustum = NULL;
    }
}

/**
 * Process a level of detail node. From the current transformation matrix,
 * the perpendicular distance to the camera is extracted and the children
 * of this node are only processed if that distance is within the render
 * range of this node.
 */
void geo_process_level_of_detail(struct GraphNodeLevelOfDetail *node) {
#ifdef TARGET_N64
    f32 distanceFromCam = -gMatStack[gMatStackIndex][3][2]; // z-component of the translation column
#else
    // We assume modern hardware is powerful enough to draw the most detailed variant
    f32 distanceFromCam = 0;
#endif

    if ((f32)node->minDistance <= distanceFromCam && distanceFromCam < (f32)node->maxDistance) {
        if (node->node.children != 0) {
            geo_process_node_and_siblings(node->node.children);
        }
    }
}

/**
 * Process a switch case node. The node's selection function is called
 * if it is 0, and among the node's children, only the selected child is
 * processed next.
 */
void geo_process_switch(struct GraphNodeSwitchCase *node) {
    struct GraphNode *selectedChild = node->fnNode.node.children;
    s32 i;

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    for (i = 0; selectedChild != NULL && node->selectedCase > i; i++) {
        selectedChild = selectedChild->next;
    }
    if (selectedChild != NULL) {
        geo_process_node_and_siblings(selectedChild);
    }
}

#ifdef HIGH_FPS_PC
void interpolate_vectors(Vec3f res, Vec3f a, Vec3f b) {
    res[0] = (a[0] + b[0]) / 2.0f;
    res[1] = (a[1] + b[1]) / 2.0f;
    res[2] = (a[2] + b[2]) / 2.0f;
}

void interpolate_vectors_s16(Vec3s res, Vec3s a, Vec3s b) {
    res[0] = (a[0] + b[0]) / 2;
    res[1] = (a[1] + b[1]) / 2;
    res[2] = (a[2] + b[2]) / 2;
}

static s16 interpolate_angle(s16 a, s16 b) {
    s32 absDiff = b - a;
    if (absDiff < 0) {
        absDiff = -absDiff;
    }
    if (absDiff >= 0x4000 && absDiff <= 0xC000) {
        return b;
    }
    if (absDiff <= 0x8000) {
        return (a + b) / 2;
    } else {
        return (a + b) / 2 + 0x8000;
    }
}

static void interpolate_angles(Vec3s res, Vec3s a, Vec3s b) {
    res[0] = interpolate_angle(a[0], b[0]);
    res[1] = interpolate_angle(a[1], b[1]);
    res[2] = interpolate_angle(a[2], b[2]);
}
#endif

/**
 * Process a camera node.
 */
void geo_process_camera(struct GraphNodeCamera *node) {
    Mat4 cameraTransform;
    Mtx *rollMtx = alloc_display_list(sizeof(*rollMtx));

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    mtxf_rotate_xy(rollMtx, node->rollScreen);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(rollMtx), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);

    mtxf_lookat(cameraTransform, node->pos, node->focus, node->roll);
    mtxf_mul(gMatStack[gMatStackIndex + 1], cameraTransform, gMatStack[gMatStackIndex]);

#ifdef HIGH_FPS_PC
    Vec3f posInterpolated;
    Vec3f focusInterpolated;

    if (gGlobalTimer == node->prevTimestamp + 1 && gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
        interpolate_vectors(posInterpolated, node->prevPos, node->pos);
        interpolate_vectors(focusInterpolated, node->prevFocus, node->focus);
        float magnitude = 0;
        int i;
        for (i = 0; i < 3; i++) {
            float diff = node->pos[i] - node->prevPos[i];
            magnitude += sqr(diff);
        }
        if (magnitude > 500000) {
            // Observed ~479000 in BBH when toggling R camera
            // Can get over 3 million in VCUTM though...
            vec3f_copy(posInterpolated, node->pos);
            vec3f_copy(focusInterpolated, node->focus);
        }
    } else {
        vec3f_copy(posInterpolated, node->pos);
        vec3f_copy(focusInterpolated, node->focus);
    }
    vec3f_copy(node->prevPos, node->pos);
    vec3f_copy(node->prevFocus, node->focus);
    node->prevTimestamp = gGlobalTimer;
    mtxf_lookat(cameraTransform, posInterpolated, focusInterpolated, node->roll);
    mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], cameraTransform, gMatStackInterpolated[gMatStackIndex]);
#endif
    inc_mat_stack();

    if (node->fnNode.node.children != 0) {
        gCurGraphNodeCamera = node;
        node->matrixPtr = &gMatStack[gMatStackIndex];
#ifdef HIGH_FPS_PC
        node->matrixPtrInterpolated = &gMatStackInterpolated[gMatStackIndex];
#endif
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamera = NULL;
    }
    gMatStackIndex--;
}

/**
 * Process a translation / rotation node. A transformation matrix based
 * on the node's translation and rotation is created and pushed on both
 * the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_translation_rotation(struct GraphNodeTranslationRotation *node) {
    Mat4 mtxf;
    Vec3f translation;

    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate(mtxf, translation, node->rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
#ifdef HIGH_FPS_PC
    mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], mtxf, gMatStackInterpolated[gMatStackIndex]);
#endif

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a translation node. A transformation matrix based on the node's
 * translation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_translation(struct GraphNodeTranslation *node) {
    Mat4 mtxf;
    Vec3f translation;

    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate(mtxf, translation, gVec3sZero);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
#ifdef HIGH_FPS_PC
    mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], mtxf, gMatStackInterpolated[gMatStackIndex]);
#endif

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a rotation node. A transformation matrix based on the node's
 * rotation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_rotation(struct GraphNodeRotation *node) {
    Mat4 mtxf;

    mtxf_rotate_zxy_and_translate(mtxf, gVec3fZero, node->rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
#ifdef HIGH_FPS_PC
    if (gGlobalTimer == node->prevTimestamp + 1) {
        Vec3s rotationInterpolated;
        interpolate_angles(rotationInterpolated, node->prevRotation, node->rotation);
        mtxf_rotate_zxy_and_translate(mtxf, gVec3fZero, rotationInterpolated);
    }
    vec3s_copy(node->prevRotation, node->rotation);
    node->prevTimestamp = gGlobalTimer;
    mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], mtxf, gMatStackInterpolated[gMatStackIndex]);
#endif

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a scaling node. A transformation matrix based on the node's
 * scale is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_scale(struct GraphNodeScale *node) {
    UNUSED Mat4 transform;
    Vec3f scaleVec;

    vec3f_set(scaleVec, node->scale, node->scale, node->scale);
    mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], scaleVec);
#ifdef HIGH_FPS_PC
    mtxf_scale_vec3f(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex], scaleVec);
#endif

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a billboard node. A transformation matrix is created that makes its
 * children face the camera, and it is pushed on the floating point and fixed
 * point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_billboard(struct GraphNodeBillboard *node) {
    Vec3f translation;
    Vec3f scale;

    vec3s_to_vec3f(translation, node->translation);

    if (gCurGraphNodeHeldObject != NULL) {
        vec3f_copy(scale, gCurGraphNodeHeldObject->objNode->header.gfx.scale);
    } else if (gCurGraphNodeObject != NULL) {
        vec3f_copy(scale, gCurGraphNodeObject->scale);
    } else {
        vec3_same(scale, 1.0f);
    }

    mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], translation, scale, gCurGraphNodeCamera->roll);
#ifdef HIGH_FPS_PC
    mtxf_billboard(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex], translation, scale, gCurGraphNodeCamera->roll);
#endif

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a display list node. It draws a display list without first pushing
 * a transformation on the stack, so all transformations are inherited from the
 * parent node. It processes its children if it has them.
 */
void geo_process_display_list(struct GraphNodeDisplayList *node) {
    append_dl_and_return((struct GraphNodeDisplayList *)node);

    gMatStackIndex++;
}

/**
 * Process a generated list. Instead of storing a pointer to a display list,
 * the list is generated on the fly by a function.
 */
void geo_process_generated_list(struct GraphNodeGenerated *node) {
    if (node->fnNode.func != NULL) {
        Gfx *list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node,
                                     (struct AllocOnlyPool *) gMatStack[gMatStackIndex]);

        if (list != NULL) {
            geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(list), node->fnNode.node.flags >> 8);
        }
    }
    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

/**
 * Process a background node. Tries to retrieve a background display list from
 * the function of the node. If that function is null or returns null, a black
 * rectangle is drawn instead.
 */
void geo_process_background(struct GraphNodeBackground *node) {
    Gfx *list = NULL;
#ifdef HIGH_FPS_PC
    Gfx *listInterpolated = NULL;
#endif

    if (node->fnNode.func != NULL) {
#ifdef HIGH_FPS_PC
        Vec3f posCopy;
        Vec3f focusCopy;
        Vec3f posInterpolated;
        Vec3f focusInterpolated;

        if (gGlobalTimer == node->prevCameraTimestamp + 1 &&
            gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
            interpolate_vectors(posInterpolated, node->prevCameraPos, gLakituState.pos);
            interpolate_vectors(focusInterpolated, node->prevCameraFocus, gLakituState.focus);
        } else {
            vec3f_copy(posInterpolated, gLakituState.pos);
            vec3f_copy(focusInterpolated, gLakituState.focus);
        }
        vec3f_copy(node->prevCameraPos, gLakituState.pos);
        vec3f_copy(node->prevCameraFocus, gLakituState.focus);
        node->prevCameraTimestamp = gGlobalTimer;
#endif

        list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node,
                                 (struct AllocOnlyPool *) gMatStack[gMatStackIndex]);
#ifdef HIGH_FPS_PC
        vec3f_copy(posCopy, gLakituState.pos);
        vec3f_copy(focusCopy, gLakituState.focus);
        vec3f_copy(gLakituState.pos, posInterpolated);
        vec3f_copy(gLakituState.focus, focusInterpolated);
        listInterpolated = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, NULL);
        vec3f_copy(gLakituState.pos, posCopy);
        vec3f_copy(gLakituState.focus, focusCopy);
#endif
    }
    if (list != NULL) {
        GEO_APPEND_DISPLAY_LIST_EXTRA(list, node->fnNode.node.flags >> 8);
    } else if (gCurGraphNodeMasterList != NULL) {
#ifdef TARGET_N3DS // avoid crashes
        Gfx *gfxStart = alloc_display_list(sizeof(Gfx) * 12);
#else
        Gfx *gfxStart = alloc_display_list(sizeof(Gfx) * 8);
#endif
        Gfx *gfx = gfxStart;

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetFillColor(gfx++, node->background);
#ifdef TARGET_N3DS
        gDPForceFlush(gfx++);
        gDPSet2d(gfx++, 1);
#endif
        gDPFillRectangle(gfx++, GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(0), BORDER_HEIGHT,
        GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(0) - 1, SCREEN_HEIGHT - BORDER_HEIGHT - 1);
#ifdef TARGET_N3DS
        gDPForceFlush(gfx++);
        gDPSet2d(gfx++, 0);
#endif
        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gSPEndDisplayList(gfx++);

        geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(gfxStart), 0);
    }
    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

void process_animated_part_type(Vec3f translation, Vec3s rotation, u8 *animType, s16 animFrame, u16 **animAttribute) {
    switch (*animType) {
        case ANIM_TYPE_TRANSLATION:
            translation[0] += gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)] * gCurrAnimTranslationMultiplier;
            translation[1] += gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)] * gCurrAnimTranslationMultiplier;
            translation[2] += gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)] * gCurrAnimTranslationMultiplier;
            *animType = ANIM_TYPE_ROTATION;
            break;
        case ANIM_TYPE_VERTICAL_TRANSLATION:
            *animAttribute += 2;
            translation[1] += gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)] * gCurrAnimTranslationMultiplier;
            *animAttribute += 2;
            *animType = ANIM_TYPE_ROTATION;
            break;
        case ANIM_TYPE_LATERAL_TRANSLATION:
            translation[0] += gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)] * gCurrAnimTranslationMultiplier;
            *animAttribute += 2;
            translation[2] += gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)] * gCurrAnimTranslationMultiplier;
            *animType = ANIM_TYPE_ROTATION;
            break;
        case ANIM_TYPE_NO_TRANSLATION:
            *animAttribute += 6;
            *animType = ANIM_TYPE_ROTATION;
            break;
    }

    if (*animType == ANIM_TYPE_ROTATION) {
        rotation[0] = gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)];
        rotation[1] = gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)];
        rotation[2] = gCurrAnimData[retrieve_animation_index(animFrame, animAttribute)];
    }
}

/**
 * Render an animated part. The current animation state is not part of the node
 * but set in global variables. If an animated part is skipped, everything afterwards desyncs.
 */
void geo_process_animated_part(struct GraphNodeAnimatedPart *node) {
    Mat4 matrix;
    Vec3s rotation;
    Vec3f translation;
#ifdef HIGH_FPS_PC
    Vec3s rotationInterpolated;
    Vec3f translationInterpolated;
    u16 *animAttribute = gCurrAnimAttribute;
    u8 animType = gCurrAnimType;
#endif

    vec3s_copy(rotation, gVec3sZero);
    vec3f_set(translation, node->translation[0], node->translation[1], node->translation[2]);
#ifdef HIGH_FPS_PC
    vec3s_copy(rotationInterpolated, rotation);
    vec3f_copy(translationInterpolated, translation);
#endif

#ifdef HIGH_FPS_PC
    process_animated_part_type(translationInterpolated, rotationInterpolated, &animType, gPrevAnimFrame, &animAttribute);
#endif
    process_animated_part_type(translation, rotation, &gCurrAnimType, gCurrAnimFrame, &gCurrAnimAttribute);
#ifdef HIGH_FPS_PC
    interpolate_vectors(translationInterpolated, translationInterpolated, translation);
    interpolate_angles(rotationInterpolated, rotationInterpolated, rotation);
#endif

    mtxf_rotate_xyz_and_translate(matrix, translation, rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], matrix, gMatStack[gMatStackIndex]);
#ifdef HIGH_FPS_PC
    mtxf_rotate_xyz_and_translate(matrix, translationInterpolated, rotationInterpolated);
    mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], matrix, gMatStackInterpolated[gMatStackIndex]);
#endif

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Initialize the animation-related global variables for the currently drawn
 * object's animation.
 */
void geo_set_animation_globals(struct AnimInfo *node, s32 hasAnimation) {
    struct Animation *anim = node->curAnim;

    if (hasAnimation) {
        node->animFrame = geo_update_animation_frame(node, &node->animFrameAccelAssist);
    }
    node->animTimer = gAreaUpdateCounter;
    if (anim->flags & ANIM_FLAG_HOR_TRANS) {
        gCurrAnimType = ANIM_TYPE_VERTICAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_VERT_TRANS) {
        gCurrAnimType = ANIM_TYPE_LATERAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_6) {
        gCurrAnimType = ANIM_TYPE_NO_TRANSLATION;
    } else {
        gCurrAnimType = ANIM_TYPE_TRANSLATION;
    }

    gCurrAnimFrame = node->animFrame;
#ifdef HIGH_FPS_PC
    if (node->prevAnimPtr == anim && node->prevAnimID == node->animID &&
        gGlobalTimer == node->prevAnimFrameTimestamp + 1) {
        gPrevAnimFrame = node->prevAnimFrame;
    } else {
        gPrevAnimFrame = node->animFrame;
    }
    node->prevAnimPtr = anim;
    node->prevAnimID = node->animID;
    node->prevAnimFrame = node->animFrame;
    node->prevAnimFrameTimestamp = gGlobalTimer;
#endif

    gCurrAnimEnabled = (anim->flags & ANIM_FLAG_5) == 0;
    gCurrAnimAttribute = segmented_to_virtual((void *) anim->index);
    gCurrAnimData = segmented_to_virtual((void *) anim->values);

    if (anim->animYTransDivisor == 0) {
        gCurrAnimTranslationMultiplier = 1.0f;
    } else {
        gCurrAnimTranslationMultiplier = (f32) node->animYTrans / (f32) anim->animYTransDivisor;
    }
}

/**
 * Process a shadow node. Renders a shadow under an object offset by the
 * translation of the first animated component and rotated according to
 * the floor below it.
 */
void geo_process_shadow(struct GraphNodeShadow *node) {
    if (gCurGraphNodeCamera != NULL && gCurGraphNodeObject != NULL) {
        Vec3f shadowPos;
#if OPTIMIZED_SHADOWS
        f32 shadowScale = node->shadowScale * 0.5f;
#else
        f32 shadowScale = node->shadowScale;
#endif
        if (gCurGraphNodeHeldObject != NULL) {
            get_pos_from_transform_mtx(shadowPos, gMatStack[gMatStackIndex],
                                       *gCurGraphNodeCamera->matrixPtr);
            shadowScale *= gCurGraphNodeHeldObject->objNode->header.gfx.scale[0];
        } else {
            vec3f_copy(shadowPos, gCurGraphNodeObject->pos);
            shadowScale *= gCurGraphNodeObject->scale[0];
        }

        s8 shifted = (gCurrAnimEnabled
                      && (gCurrAnimType == ANIM_TYPE_TRANSLATION
                       || gCurrAnimType == ANIM_TYPE_LATERAL_TRANSLATION)
        );

        if (shifted) {
            struct GraphNode *geo = node->node.children;
            f32 objScale = 1.0f;
            if (geo != NULL && geo->type == GRAPH_NODE_TYPE_SCALE) {
                objScale = ((struct GraphNodeScale *) geo)->scale;
            }
            f32 animScale = gCurrAnimTranslationMultiplier * objScale;
            Vec3f animOffset;
            animOffset[0] = gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * animScale;
            animOffset[1] = 0.0f;
            gCurrAnimAttribute += 2;
            animOffset[2] = gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * animScale;
            gCurrAnimAttribute -= 6;

            // simple matrix rotation so the shadow offset rotates along with the object
            f32 sinAng = sins(gCurGraphNodeObject->angle[1]);
            f32 cosAng = coss(gCurGraphNodeObject->angle[1]);

            shadowPos[0] += ( animOffset[0] * cosAng) + (animOffset[2] * sinAng);
            shadowPos[2] += (-animOffset[0] * sinAng) + (animOffset[2] * cosAng);
        }

#if OPTIMIZED_SHADOWS
        Vec3f floorNormal;
        Vec3f scaleVec;
        s8 isDecal;
#endif
#ifdef HIGH_FPS_PC
        Vec3f shadowPosInterpolated;
        if (gCurGraphNodeHeldObject != NULL) {
            if (gGlobalTimer == gCurGraphNodeHeldObject->prevShadowPosTimestamp + 1) {
                interpolate_vectors(shadowPosInterpolated, gCurGraphNodeHeldObject->prevShadowPos, shadowPos);
            } else {
                vec3f_copy(shadowPosInterpolated, shadowPos);
            }
            vec3f_copy(gCurGraphNodeHeldObject->prevShadowPos, shadowPos);
            gCurGraphNodeHeldObject->prevShadowPosTimestamp = gGlobalTimer;
        } else {
            if (gGlobalTimer == gCurGraphNodeObject->prevShadowPosTimestamp + 1 &&
                gGlobalTimer != gCurGraphNodeObject->skipInterpolationTimestamp) {
                interpolate_vectors(shadowPosInterpolated, gCurGraphNodeObject->prevShadowPos, shadowPos);
            } else {
                vec3f_copy(shadowPosInterpolated, shadowPos);
            }
            vec3f_copy(gCurGraphNodeObject->prevShadowPos, shadowPos);
            gCurGraphNodeObject->prevShadowPosTimestamp = gGlobalTimer;
        }

    #if OPTIMIZED_SHADOWS
        Gfx *shadowListInterpolated = create_shadow_below_xyz(shadowPosInterpolated, floorNormal, scaleVec, shadowScale,
                                                         node->shadowSolidity, node->shadowType, shifted, &isDecal);
    #else
        Gfx *shadowListInterpolated = create_shadow_below_xyz(shadowPosInterpolated[0], shadowPosInterpolated[1],
                                                         shadowPosInterpolated[2], shadowScale,
                                                         node->shadowSolidity, node->shadowType);
    #endif
#endif

#if OPTIMIZED_SHADOWS
        Gfx *shadowList = create_shadow_below_xyz(shadowPos, floorNormal, scaleVec, shadowScale,
                                                  node->shadowSolidity, node->shadowType, shifted, &isDecal);
#else
        Gfx *shadowList = create_shadow_below_xyz(shadowPos[0], shadowPos[1], shadowPos[2], shadowScale,
                                             node->shadowSolidity, node->shadowType);
#endif
#ifdef HIGH_FPS_PC
        if (shadowListInterpolated != NULL && shadowList != NULL)
#else
        if (shadowList != NULL)
#endif
        {
#if OPTIMIZED_SHADOWS
            mtxf_shadow(gMatStack[gMatStackIndex + 1], *gCurGraphNodeCamera->matrixPtr,
                floorNormal, shadowPos, scaleVec, gCurGraphNodeObject->angle[1]);
    #ifdef HIGH_FPS_PC
            mtxf_shadow(gMatStackInterpolated[gMatStackIndex + 1], *gCurGraphNodeCamera->matrixPtrInterpolated,
                floorNormal, shadowPosInterpolated, scaleVec, gCurGraphNodeObject->angle[1]);
    #endif
#else
            Mat4 mtxf;
            mtxf_translate(mtxf, shadowPos);
            mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, *gCurGraphNodeCamera->matrixPtr);
    #ifdef HIGH_FPS_PC
            mtxf_translate(mtxf, shadowPosInterpolated);
            mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], mtxf, *gCurGraphNodeCamera->matrixPtrInterpolated);
    #endif
#endif
            inc_mat_stack();

#if OPTIMIZED_SHADOWS
            GEO_APPEND_DISPLAY_LIST_EXTRA(shadowList, isDecal ? LAYER_TRANSPARENT_DECAL : LAYER_TRANSPARENT);
#else
            if (gShadowAboveWaterOrLava == TRUE) {
                GEO_APPEND_DISPLAY_LIST_EXTRA(shadowList, LAYER_ALPHA);
            } else if (gMarioOnIceOrCarpet == TRUE) {
                GEO_APPEND_DISPLAY_LIST_EXTRA(shadowList, LAYER_TRANSPARENT);
    #if WATER_SURFACES
            } else if (gShadowAboveCustomWater == TRUE) {
                GEO_APPEND_DISPLAY_LIST_EXTRA(shadowList, LAYER_TRANSPARENT);
    #endif
            } else {
                GEO_APPEND_DISPLAY_LIST_EXTRA(shadowList, LAYER_TRANSPARENT_DECAL);
            }
#endif
            gMatStackIndex--;
        }
    }

    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Check whether an object is in view to determine whether it should be drawn.
 * This is known as frustum culling.
 * It checks whether the object is far away, very close / behind the camera,
 * or horizontally out of view. It does not check whether it is vertically
 * out of view. It assumes a sphere of 300 units around the object's position
 * unless the object has a culling radius node that specifies otherwise.
 *
 * The matrix parameter should be the top of the matrix stack, which is the
 * object's transformation matrix times the camera 'look-at' matrix. The math
 * is counter-intuitive, but it checks column 3 (translation vector) of this
 * matrix to determine where the origin (0,0,0) in object space will be once
 * transformed to camera space (x+ = right, y+ = up, z = 'coming out the screen').
 * In 3D graphics, you typically model the world as being moved in front of a
 * static camera instead of a moving camera through a static world, which in
 * this case simplifies calculations. Note that the perspective matrix is not
 * on the matrix stack, so there are still calculations with the fov to compute
 * the slope of the lines of the frustum.
 *
 *        z-
 *
 *  \     |     /
 *   \    |    /
 *    \   |   /
 *     \  |  /
 *      \ | /
 *       \|/
 *        C       x+
 *
 * Since (0,0,0) is unaffected by rotation, columns 0, 1 and 2 are ignored.
 */
s32 obj_is_in_view(struct GraphNodeObject *node, Mat4 matrix) {
    s16 cullingRadius;
    s16 halfFov; // half of the fov in in-game angle units instead of degrees
    struct GraphNode *geo;
    f32 hScreenEdge;

    if (node->node.flags & GRAPH_RENDER_INVISIBLE) {
        return FALSE;
    }

    geo = node->sharedChild;

    // ! @bug The aspect ratio is not accounted for. When the fov value is 45,
    // the horizontal effective fov is actually 60 degrees, so you can see objects
    // visibly pop in or out at the edge of the screen.
    halfFov = (gCurGraphNodeCamFrustum->fov / 2.0f + 1.0f) * 32768.0f / 180.0f + 0.5f;

    hScreenEdge = -matrix[3][2] * sins(halfFov) / coss(halfFov);
    // -matrix[3][2] is the depth, which gets multiplied by tan(halfFov) to get
    // the amount of units between the center of the screen and the horizontal edge
    // given the distance from the object to the camera.

    // This multiplication should really be performed on 4:3 as well,
    // but the issue will be more apparent on widescreen.
#ifdef TARGET_N64
    hScreenEdge *= sGeoAspectRatio;
#else
    hScreenEdge *= GFX_DIMENSIONS_ASPECT_RATIO;
#endif

    if (geo != NULL && geo->type == GRAPH_NODE_TYPE_CULLING_RADIUS) {
        cullingRadius = ((struct GraphNodeCullingRadius *) geo)->cullingRadius;
    } else {
        cullingRadius = 300;
    }

    // Don't render if the object is close to or behind the camera
    if (matrix[3][2] > -100.0f + cullingRadius) {
        return FALSE;
    }

    //! This makes the HOLP not update when the camera is far away, and it
    //  makes PU travel safe when the camera is locked on the main map.
    //  If Mario were rendered with a depth over 65536 it would cause overflow
    //  when converting the transformation matrix to a fixed point matrix.
    if (matrix[3][2] < -20000.0f - cullingRadius) {
        return FALSE;
    }

    // Check whether the object is horizontally in view
    if (matrix[3][0] > hScreenEdge + cullingRadius) {
        return FALSE;
    }
    if (matrix[3][0] < -hScreenEdge - cullingRadius) {
        return FALSE;
    }
    return TRUE;
}

#ifdef HIGH_FPS_PC
static void interpolate_matrix(Mat4 result, Mat4 a, Mat4 b) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            result[i][j] = (a[i][j] + b[i][j]) / 2.0f;
        }
    }
}

void process_object_scale_interpolated(struct Object *node, Vec3f scaleInterpolated) {
    if (gGlobalTimer == node->header.gfx.prevScaleTimestamp + 1 &&
        gGlobalTimer != node->header.gfx.skipInterpolationTimestamp) {
        interpolate_vectors(scaleInterpolated, node->header.gfx.prevScale, node->header.gfx.scale);
    } else {
        vec3f_copy(scaleInterpolated, node->header.gfx.scale);
    }
    vec3f_copy(node->header.gfx.prevScale, node->header.gfx.scale);
    node->header.gfx.prevScaleTimestamp = gGlobalTimer;
}
#endif

/**
 * Process an object node.
 */
void geo_process_object(struct Object *node) {
#ifdef HIGH_FPS_PC
    Vec3f scaleInterpolated;
#endif

    if (node->header.gfx.areaIndex == gCurGraphNodeRoot->areaIndex) {
        if (node->header.gfx.throwMatrix != NULL) {
#ifdef HIGH_FPS_PC
            // Interpolate throwMatrix
            Mat4 mtxfInterpolated;
            if (gGlobalTimer == node->header.gfx.prevThrowMatrixTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp) {
                interpolate_matrix(mtxfInterpolated, *node->header.gfx.throwMatrix, node->header.gfx.prevThrowMatrix);
            } else {
                mtxf_copy(mtxfInterpolated, *node->header.gfx.throwMatrix);
            }
            mtxf_copy(node->header.gfx.prevThrowMatrix, *node->header.gfx.throwMatrix);
            node->header.gfx.prevThrowMatrixTimestamp = gGlobalTimer;

            // Interpolate scale
            process_object_scale_interpolated(node, scaleInterpolated);
#endif
            mtxf_mul(gMatStack[gMatStackIndex + 1], *node->header.gfx.throwMatrix, gMatStack[gMatStackIndex]);
            mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], node->header.gfx.scale);
#ifdef HIGH_FPS_PC
            mtxf_mul(gMatStackInterpolated[gMatStackIndex + 1], mtxfInterpolated, gMatStackInterpolated[gMatStackIndex]);
            mtxf_scale_vec3f(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex + 1], scaleInterpolated);
#endif
        } else if (node->header.gfx.node.flags & (GRAPH_RENDER_BILLBOARD | GRAPH_RENDER_CYLBOARD)) {
#ifdef HIGH_FPS_PC
            // Interpolate position
            Vec3f posInterpolated;
            if (gGlobalTimer == node->header.gfx.prevTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp) {
                interpolate_vectors(posInterpolated, node->header.gfx.prevPos, node->header.gfx.pos);
            } else {
                vec3f_copy(posInterpolated, node->header.gfx.pos);
            }
            vec3f_copy(node->header.gfx.prevPos, node->header.gfx.pos);
            node->header.gfx.prevTimestamp = gGlobalTimer;

            // Interpolate scale
            process_object_scale_interpolated(node, scaleInterpolated);
#endif
            if (node->header.gfx.node.flags & GRAPH_RENDER_CYLBOARD) {
                mtxf_cylboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex],
                               node->header.gfx.pos, node->header.gfx.scale, gCurGraphNodeCamera->roll);
#ifdef HIGH_FPS_PC
                mtxf_cylboard(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex],
                               posInterpolated, scaleInterpolated, gCurGraphNodeCamera->roll);
#endif
            } else { // GRAPH_RENDER_BILLBOARD
                mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex],
                               node->header.gfx.pos, node->header.gfx.scale, gCurGraphNodeCamera->roll);
#ifdef HIGH_FPS_PC
                mtxf_billboard(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex],
                               posInterpolated, scaleInterpolated, gCurGraphNodeCamera->roll);
#endif
            }
        } else {
#ifdef HIGH_FPS_PC
            // Interpolate position and angle
            Vec3f posInterpolated;
            Vec3s angleInterpolated;
            if (gGlobalTimer == node->header.gfx.prevTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp) {
                interpolate_vectors(posInterpolated, node->header.gfx.prevPos, node->header.gfx.pos);
                interpolate_angles(angleInterpolated, node->header.gfx.prevAngle, node->header.gfx.angle);
            } else {
                vec3f_copy(posInterpolated, node->header.gfx.pos);
                vec3s_copy(angleInterpolated, node->header.gfx.angle);
            }
            vec3f_copy(node->header.gfx.prevPos, node->header.gfx.pos);
            vec3s_copy(node->header.gfx.prevAngle, node->header.gfx.angle);
            node->header.gfx.prevTimestamp = gGlobalTimer;
#endif
            mtxf_rotate_zxy_and_translate_and_mul(node->header.gfx.angle, node->header.gfx.pos, gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex]);
#ifdef HIGH_FPS_PC
            mtxf_rotate_zxy_and_translate_and_mul(angleInterpolated, posInterpolated, gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex]);
#endif

#ifdef HIGH_FPS_PC
            // Interpolate scale
            process_object_scale_interpolated(node, scaleInterpolated);
#endif
            mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], node->header.gfx.scale);
#ifdef HIGH_FPS_PC
            mtxf_scale_vec3f(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex + 1], scaleInterpolated);
#endif
        }

        node->header.gfx.throwMatrix = &gMatStack[gMatStackIndex + 1];
#ifdef HIGH_FPS_PC
        node->header.gfx.throwMatrixInterpolated = &gMatStackInterpolated[gMatStackIndex + 1];
#endif
        vec3f_copy(node->header.gfx.cameraToObject, gMatStack[gMatStackIndex + 1][3]);

        // FIXME: correct types
        if (node->header.gfx.animInfo.curAnim != NULL) {
            geo_set_animation_globals(&node->header.gfx.animInfo, (node->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0);
        }

        if (obj_is_in_view(&node->header.gfx, gMatStack[gMatStackIndex + 1])) {
            inc_mat_stack();

            if (node->header.gfx.sharedChild != NULL) {
                gCurGraphNodeObject = (struct GraphNodeObject *) node;
                node->header.gfx.sharedChild->parent = &node->header.gfx.node;
                geo_process_node_and_siblings(node->header.gfx.sharedChild);
                node->header.gfx.sharedChild->parent = NULL;
                gCurGraphNodeObject = NULL;
            }
            if (node->header.gfx.node.children != NULL) {
                geo_process_node_and_siblings(node->header.gfx.node.children);
            }

            gMatStackIndex--;
        }
#ifdef HIGH_FPS_PC
        else {
            node->header.gfx.prevThrowMatrixTimestamp = 0;
            node->header.gfx.prevTimestamp = 0;
            node->header.gfx.prevScaleTimestamp = 0;
        }
#endif
        gCurrAnimType = ANIM_TYPE_NONE;
        node->header.gfx.throwMatrix = NULL;
#ifdef HIGH_FPS_PC
        node->header.gfx.throwMatrixInterpolated = NULL;
#endif
    }
}

/**
 * Process an object parent node. Temporarily assigns itself as the parent of
 * the subtree rooted at 'sharedChild' and processes the subtree, after which the
 * actual children are be processed. (in practice they are null though)
 */
void geo_process_object_parent(struct GraphNodeObjectParent *node) {
    if (node->sharedChild != NULL) {
        node->sharedChild->parent = (struct GraphNode *) node;
        geo_process_node_and_siblings(node->sharedChild);
        node->sharedChild->parent = NULL;
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a held object node.
 */
void geo_process_held_object(struct GraphNodeHeldObject *node) {
    Vec3f translation;

#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, &lookAt);
#endif

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    if (node->objNode != NULL && node->objNode->header.gfx.sharedChild != NULL) {
        vec3_prod_val(translation, node->translation, 0.25f);

#ifdef HIGH_FPS_PC
        Vec3f scaleInterpolated;
        if (gGlobalTimer == node->objNode->header.gfx.prevScaleTimestamp + 1) {
            interpolate_vectors(scaleInterpolated, node->objNode->header.gfx.prevScale, node->objNode->header.gfx.scale);
        } else {
            vec3f_copy(scaleInterpolated, node->objNode->header.gfx.scale);
        }
        vec3f_copy(node->objNode->header.gfx.prevScale, node->objNode->header.gfx.scale);
        node->objNode->header.gfx.prevScaleTimestamp = gGlobalTimer;
#endif

        mtxf_held_object(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex],
                         *gCurGraphNodeObject->throwMatrix, translation, node->objNode->header.gfx.scale);
#ifdef HIGH_FPS_PC
        mtxf_held_object(gMatStackInterpolated[gMatStackIndex + 1], gMatStackInterpolated[gMatStackIndex],
                         *gCurGraphNodeObject->throwMatrixInterpolated, translation, scaleInterpolated);
#endif

        if (node->fnNode.func != NULL) {
            node->fnNode.func(GEO_CONTEXT_HELD_OBJ, &node->fnNode.node, (struct AllocOnlyPool *) gMatStack[gMatStackIndex + 1]);
        }

        inc_mat_stack();
        u8 tempType = gCurrAnimType;
        u8 tempEnabled = gCurrAnimEnabled;
        s16 tempFrame = gCurrAnimFrame;
        f32 tempTranslationMultiplier = gCurrAnimTranslationMultiplier;
        u16 *tempAttribute = gCurrAnimAttribute;
        s16 *tempData = gCurrAnimData;
#ifdef HIGH_FPS_PC
        s16 tempPrevFrame = gPrevAnimFrame;
#endif
        gCurrAnimType = 0;
        gCurGraphNodeHeldObject = (void *) node;
        if (node->objNode->header.gfx.animInfo.curAnim != NULL) {
            geo_set_animation_globals(&node->objNode->header.gfx.animInfo, (node->objNode->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0);
        }

        geo_process_node_and_siblings(node->objNode->header.gfx.sharedChild);
        gCurGraphNodeHeldObject = NULL;
        gCurrAnimType = tempType;
        gCurrAnimEnabled = tempEnabled;
        gCurrAnimFrame = tempFrame;
        gCurrAnimTranslationMultiplier = tempTranslationMultiplier;
        gCurrAnimAttribute = tempAttribute;
        gCurrAnimData = tempData;
#ifdef HIGH_FPS_PC
        gPrevAnimFrame = tempPrevFrame;
#endif
        gMatStackIndex--;
    }

    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

/**
 * Processes the children of the given GraphNode if it has any
 */
void geo_try_process_children(struct GraphNode *node) {
    if (node->children != NULL) {
        geo_process_node_and_siblings(node->children);
    }
}

typedef void (*GeoProcessFunc)();

// See enum 'GraphNodeTypes' in 'graph_node.h'.
static GeoProcessFunc sGeoProcessJumpTable[] = {
    [GRAPH_NODE_TYPE_ORTHO_PROJECTION    ] = geo_process_ortho_projection,
    [GRAPH_NODE_TYPE_PERSPECTIVE         ] = geo_process_perspective,
    [GRAPH_NODE_TYPE_MASTER_LIST         ] = geo_process_master_list,
    [GRAPH_NODE_TYPE_LEVEL_OF_DETAIL     ] = geo_process_level_of_detail,
    [GRAPH_NODE_TYPE_SWITCH_CASE         ] = geo_process_switch,
    [GRAPH_NODE_TYPE_CAMERA              ] = geo_process_camera,
    [GRAPH_NODE_TYPE_TRANSLATION_ROTATION] = geo_process_translation_rotation,
    [GRAPH_NODE_TYPE_TRANSLATION         ] = geo_process_translation,
    [GRAPH_NODE_TYPE_ROTATION            ] = geo_process_rotation,
    [GRAPH_NODE_TYPE_OBJECT              ] = geo_process_object,
    [GRAPH_NODE_TYPE_ANIMATED_PART       ] = geo_process_animated_part,
    [GRAPH_NODE_TYPE_BILLBOARD           ] = geo_process_billboard,
    [GRAPH_NODE_TYPE_DISPLAY_LIST        ] = geo_process_display_list,
    [GRAPH_NODE_TYPE_SCALE               ] = geo_process_scale,
    [GRAPH_NODE_TYPE_SHADOW              ] = geo_process_shadow,
    [GRAPH_NODE_TYPE_OBJECT_PARENT       ] = geo_process_object_parent,
    [GRAPH_NODE_TYPE_GENERATED_LIST      ] = geo_process_generated_list,
    [GRAPH_NODE_TYPE_BACKGROUND          ] = geo_process_background,
    [GRAPH_NODE_TYPE_HELD_OBJ            ] = geo_process_held_object,
    [GRAPH_NODE_TYPE_CULLING_RADIUS      ] = geo_try_process_children,
    [GRAPH_NODE_TYPE_ROOT                ] = geo_try_process_children,
    [GRAPH_NODE_TYPE_START               ] = geo_try_process_children,
};

/**
 * Process a generic geo node and its siblings.
 * The first argument is the start node, and all its siblings will
 * be iterated over.
 */
void geo_process_node_and_siblings(struct GraphNode *firstNode) {
    s16 iterateChildren = TRUE;
    struct GraphNode *curGraphNode = firstNode;
    struct GraphNode *parent = curGraphNode->parent;

    // In the case of a switch node, exactly one of the children of the node is
    // processed instead of all children like usual
    if (parent != NULL) {
        iterateChildren = (parent->type != GRAPH_NODE_TYPE_SWITCH_CASE);
    }

    do {
        if (curGraphNode->flags & GRAPH_RENDER_ACTIVE) {
            if (curGraphNode->flags & GRAPH_RENDER_CHILDREN_FIRST) {
                geo_try_process_children(curGraphNode);
            } else {
                sGeoProcessJumpTable[curGraphNode->type](curGraphNode);
            }
        } else {
            if (curGraphNode->type == GRAPH_NODE_TYPE_OBJECT) {
                ((struct GraphNodeObject *) curGraphNode)->throwMatrix = NULL;
            }
        }
    } while (iterateChildren && (curGraphNode = curGraphNode->next) != firstNode);
}

/**
 * Process a root node. This is the entry point for processing the scene graph.
 * The root node itself sets up the viewport, then all its children are processed
 * to set up the projection and draw display lists.
 */
void geo_process_root(struct GraphNodeRoot *node, Vp *b, Vp *c, s32 clearColor) {
    UNUSED u8 filler[4];

    if (node->node.flags & GRAPH_RENDER_ACTIVE) {
        Mtx *initialMatrix;
        Vp *viewport = alloc_display_list(sizeof(*viewport));
#ifdef HIGH_FPS_PC
        Vp *viewportInterpolated = viewport;
#endif

#ifdef USE_SYSTEM_MALLOC
        gDisplayListHeap = alloc_only_pool_init();
#else
        gDisplayListHeap = alloc_only_pool_init(main_pool_available() - sizeof(struct AllocOnlyPool),
                                                MEMORY_POOL_LEFT);
#endif
        initialMatrix = alloc_display_list(sizeof(*initialMatrix));
        gMatStackIndex = 0;
        gCurrAnimType = 0;
        vec3s_set(viewport->vp.vtrans, node->x * 4, node->y * 4, 511);
        vec3s_set(viewport->vp.vscale, node->width * 4, node->height * 4, 511);
        if (b != NULL) {
            clear_framebuffer(clearColor);
#ifdef HIGH_FPS_PC
            viewportInterpolated = alloc_display_list(sizeof(*viewportInterpolated));
            interpolate_vectors_s16(viewportInterpolated->vp.vtrans, sPrevViewport.vp.vtrans, b->vp.vtrans);
            interpolate_vectors_s16(viewportInterpolated->vp.vscale, sPrevViewport.vp.vscale, b->vp.vscale);

            sViewportPos = gDisplayListHead;
            make_viewport_clip_rect(viewportInterpolated);
#else
            make_viewport_clip_rect(b);
#endif
            *viewport = *b;
        }

        else if (c != NULL) {
            clear_framebuffer(clearColor);
            make_viewport_clip_rect(c);
        }
#ifdef HIGH_FPS_PC
        sPrevViewport = *viewport;
#endif

        mtxf_identity(gMatStack[gMatStackIndex]);
        mtxf_to_mtx(initialMatrix, gMatStack[gMatStackIndex]);
        gMatStackFixed[gMatStackIndex] = initialMatrix;

#ifdef HIGH_FPS_PC
        mtxf_identity(gMatStackInterpolated[gMatStackIndex]);
        gMatStackInterpolatedFixed[gMatStackIndex] = initialMatrix;

        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(viewportInterpolated));
#else
        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(viewport));
#endif

        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(gMatStackFixed[gMatStackIndex]),
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gCurGraphNodeRoot = node;
        if (node->node.children != NULL) {
            geo_process_node_and_siblings(node->node.children);
        }
        gCurGraphNodeRoot = NULL;
        if (gShowDebugText) {
#ifndef USE_SYSTEM_MALLOC
            print_text_fmt_int(180, 36, "MEM %d",
                               gDisplayListHeap->totalSpace - gDisplayListHeap->usedSpace);
#endif
        }
        main_pool_free(gDisplayListHeap);
    }
}
