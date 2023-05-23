#ifdef USE_SYSTEM_MALLOC
#include <stdlib.h>
#ifdef __APPLE__
// No malloc on mac
#else
#include <malloc.h>
#endif
#endif
#include <PR/ultratypes.h>

#include "audio/external.h"
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "level_table.h"
#include "memory.h"
#include "object_constants.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "spawn_object.h"
#include "types.h"

#if 0 // Old version of this file

/**
 * An unused linked list struct that seems to have been replaced by ObjectNode.
 */
struct LinkedList {
    struct LinkedList *next;
    struct LinkedList *prev;
};

/**
 * Clear the doubly linked usedList. Singly link each item in the pool into
 * a list, and return this list in pFreeList.
 * Appears to have been replaced by init_free_object_list.
 */
void unused_init_free_list(struct LinkedList *usedList, struct LinkedList **pFreeList,
                           struct LinkedList *pool, s32 itemSize, s32 poolLength) {
    s32 i;
    struct LinkedList *node = pool;

    usedList->next = usedList;
    usedList->prev = usedList;

    *pFreeList = pool;

    for (i = 0; i < poolLength - 1; i++) {
        // Add next node to free list
        node = (struct LinkedList *) ((u8 *) node + itemSize);
        pool->next = node;
        pool = node;
    }

    // End the list
    pool->next = NULL;
}

/**
 * Attempt to allocate a node from freeList (singly linked) and append it
 * to the end of destList (doubly linked). Return the object, or NULL if
 * freeList is empty.
 * Appears to have been replaced by try_allocate_object.
 */
struct LinkedList *unused_try_allocate(struct LinkedList *destList,
                                       struct LinkedList *freeList) {
    struct LinkedList *node = freeList->next;

    if (node != NULL) {
        // Remove from free list
        freeList->next = node->next;

        // Insert at the end of destination list
        node->prev = destList->prev;
        node->next = destList;
        destList->prev->next = node;
        destList->prev = node;
    }

    return node;
}

/**
 * Remove the node from the doubly linked list it's in, and place it in the
 * singly linked freeList.
 * This function seems to have been replaced by deallocate_object.
 */
void unused_deallocate(struct LinkedList *freeList, struct LinkedList *node) {
    // Remove from doubly linked list
    node->next->prev = node->prev;
    node->prev->next = node->next;

    // Insert at beginning of singly linked list
    node->next = freeList->next;
    freeList->next = node;
}

/**
 * Delete the leaf graph nodes under obj and obj's siblings.
 */
UNUSED static void unused_delete_leaf_nodes(struct Object *obj) {
    struct Object *children;
    struct Object *sibling;
    struct Object *obj0 = obj;

    if ((children = (struct Object *) obj->header.gfx.node.children) != NULL) {
        unused_delete_leaf_nodes(children);
    } else {
        // No children
        obj_mark_for_deletion(obj);
    }

    while ((sibling = (struct Object *) obj->header.gfx.node.next) != obj0) {
        unused_delete_leaf_nodes(sibling);
        obj = (struct Object *) sibling->header.gfx.node.next;
    }
}
#endif

/**
 * Attempt to allocate an object from freeList (singly linked) and append it
 * to the end of destList (doubly linked). Return the object, or NULL if
 * freeList is empty.
 */
struct Object *try_allocate_object(struct ObjectNode *destList, struct ObjectNode *freeList) {
    struct ObjectNode *nextObj;

    if ((nextObj = freeList->next) != NULL) {
        // Remove from free list
        freeList->next = nextObj->next;

        // Insert at end of destination list
        nextObj->prev = destList->prev;
        nextObj->next = destList;
        destList->prev->next = nextObj;
        destList->prev = nextObj;
    } else {
#ifdef USE_SYSTEM_MALLOC
        nextObj = (struct ObjectNode *) MALLOC_FUNCTION(sizeof(struct Object));
        if (nextObj == NULL) {
            abort();
        }
        // Insert at end of destination list
        nextObj->prev = destList->prev;
        nextObj->next = destList;
        destList->prev->next = nextObj;
        destList->prev = nextObj;
#else
        return NULL;
#endif
    }

#ifdef USE_SYSTEM_MALLOC
    init_graph_node_object(NULL, &nextObj->gfx, 0, gVec3fZero, gVec3sZero, gVec3fOne);
#else
    geo_remove_child(&nextObj->gfx.node);
#endif
    geo_add_child(&gObjParentGraphNode, &nextObj->gfx.node);

    return (struct Object *) nextObj;
}

/**
 * Remove the given object from the object list that it's currently in, and
 * insert it at the beginning of the free list (singly linked).
 */
static void deallocate_object(struct ObjectNode *freeList, struct ObjectNode *obj) {
    // Remove from object list
    obj->next->prev = obj->prev;
    obj->prev->next = obj->next;

    // Insert at beginning of free list
    obj->next = freeList->next;
    freeList->next = obj;
}

#ifndef USE_SYSTEM_MALLOC
/**
 * Add every object in the pool to the free object list.
 */
void init_free_object_list(void) {
    s32 i;
    s32 poolLength = OBJECT_POOL_CAPACITY;

    // Add the first object in the pool to the free list
    struct Object *obj = &gObjectPool[0];
    gFreeObjectList.next = (struct ObjectNode *) obj;

    // Link each object in the pool to the following object
    for (i = 0; i < poolLength - 1; i++) {
        obj->header.next = &(obj + 1)->header;
        obj++;
    }

    // End the list
    obj->header.next = NULL;
}
#endif

/**
 * Clear each object list, without adding the objects back to the free list.
 */
void clear_object_lists(struct ObjectNode *objLists) {
    s32 i;

    for (i = 0; i < NUM_OBJ_LISTS; i++) {
#ifdef USE_SYSTEM_MALLOC
        struct ObjectNode *list = objLists + i;
        struct ObjectNode *node = list->next;

        while (node != NULL && node != list) {
            struct Object *obj = (struct Object *) node;
            node = node->next;

            unload_object(obj);
        }
#endif
        objLists[i].next = &objLists[i];
        objLists[i].prev = &objLists[i];
    }
}

/**
 * Free the given object.
 */
void unload_object(struct Object *obj) {
    obj_mark_for_deletion(obj);
    obj->prevObj = NULL;

    obj->header.gfx.throwMatrix = NULL;
    stop_sounds_from_source(obj->header.gfx.cameraToObject);
    geo_remove_child(&obj->header.gfx.node);
#ifndef USE_SYSTEM_MALLOC
    geo_add_child(&gObjParentGraphNode, &obj->header.gfx.node);
#endif

    obj->header.gfx.node.flags &= ~(GRAPH_RENDER_BILLBOARD | GRAPH_RENDER_CYLBOARD | GRAPH_RENDER_ACTIVE);

    deallocate_object(&gFreeObjectList, &obj->header);
}

/**
 * Attempt to allocate a new object slot into the given object list, freeing
 * an unimportant object if necessary. If this is not possible, hang using an
 * infinite loop.
 */
struct Object *allocate_object(struct ObjectNode *objList) {
    s32 i;
    struct Object *obj = try_allocate_object(objList, &gFreeObjectList);

#ifndef USE_SYSTEM_MALLOC
    // The object list is full if the newly created pointer is NULL.
    // If this happens, we first attempt to unload unimportant objects
    // in order to finish allocating the object.
    if (obj == NULL) {
        // Look for an unimportant object to kick out.
        struct Object *unimportantObj = find_unimportant_object();

        // If no unimportant object exists, then the object pool is exhausted.
        if (unimportantObj == NULL) {
            // We've met with a terrible fate.
            while (TRUE) {
            }
        } else {
            // If an unimportant object does exist, unload it and take its slot.
            unload_object(unimportantObj);
            obj = try_allocate_object(objList, &gFreeObjectList);
            if (gCurrentObject == obj) {
                //! Uh oh, the unimportant object was in the middle of
                //  updating! This could cause some interesting logic errors,
                //  but I don't know of any unimportant objects that spawn
                //  other objects.
            }
        }
    }
#endif

    // Initialize object fields

    obj->activeFlags = ACTIVE_FLAG_ACTIVE;
    obj->parentObj = obj;
    obj->prevObj = NULL;
    obj->collidedObjInteractTypes = 0;
    obj->numCollidedObjs = 0;

#if IS_64_BIT
    for (i = 0; i < MAX_OBJECT_FIELDS; i++) {
        obj->rawData.asS32[i] = 0;
        obj->ptrData.asVoidPtr[i] = NULL;
    }
#else
    for (i = 0; i < MAX_OBJECT_FIELDS; i++) {
        obj->rawData.asS32[i] = 0;
    }
#endif

    obj->unused1 = 0;
    obj->bhvStackIndex = 0;
    obj->bhvDelayTimer = 0;

    obj->hitboxRadius = 50.0f;
    obj->hitboxHeight = 100.0f;
    obj->hurtboxRadius = 0.0f;
    obj->hurtboxHeight = 0.0f;
    obj->hitboxDownOffset = 0.0f;
    obj->unused2 = 0;

    obj->platform = NULL;
    obj->collisionData = NULL;
    obj->oIntangibleTimer = -1;
    obj->oDamageOrCoinValue = 0;
    obj->oHealth = 2048;

    mtxf_identity(obj->transform);

    obj->respawnInfo = 0;
    obj->respawnInfoPointer = NULL;

    obj->oDistanceToMario = F32_MAX;
    obj->oRoom = -1;

    // ex-alo change
    // Set these distances to 0 to prevent early collision and drawing load
    // Proper values are set when ACTIVE_FLAG_ALLOCATED active flag is set
    obj->oCollisionDistance = 0.0f;
    obj->oDrawingDistance = 0.0f;

    obj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    vec3_zero(obj->header.gfx.pos);
    obj->header.gfx.throwMatrix = NULL;

    return obj;
}

/**
 * Spawn an object at the origin with the behavior script at virtual address bhvScript.
 */
struct Object *create_object(const BehaviorScript *bhvScript) {
    struct Object *obj;
    struct ObjectNode *objList;

    u32 objListIndex = get_object_list_from_behavior(bhvScript);

    objList = &gObjectLists[objListIndex];
    obj = allocate_object(objList);

    obj->curBhvCommand = bhvScript;
    obj->behavior = bhvScript;

    if (objListIndex == OBJ_LIST_UNIMPORTANT) {
        obj->activeFlags |= ACTIVE_FLAG_UNIMPORTANT;
    }

    obj->activeFlags |= ACTIVE_FLAG_ALLOCATED;

    return obj;
}
