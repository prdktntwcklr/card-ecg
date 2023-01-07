#include "ring_buffer.h"
#include "my_assert.h"

#if USE_PRINTF || defined (TEST)

#define RING_SIZE (64U)
STATIC_ASSERT(RING_SIZE >= 2U, ring_size_cannot_be_less_than_two);
STATIC_ASSERT(RING_SIZE % 2 == 0, ring_size_should_be_multiple_of_two);

typedef uint8_t ring_pos_t;

static volatile uint8_t ring_data[RING_SIZE] = {0};
static volatile ring_pos_t ring_head = 0;
static volatile ring_pos_t ring_tail = 0;
static const ring_pos_t ring_max = RING_SIZE;

/**
 * @brief Resets the ring buffer to default state.
 */
extern void ring_buffer_reset(void)
{
    ring_head = 0;
    ring_tail = 0;
}

/**
 * @brief Adds value in byte to the ring buffer.
 *
 * @note  Returns true if successfull.
 */
extern bool ring_buffer_put(uint8_t byte)
{
    bool put_success = false;
    
    if(!ring_buffer_is_full())
    {
        /* there is room, place character in buffer */
        ring_data[ring_head] = byte;
        
        /* update head position */
        if(++ring_head == ring_max)
        {
            ring_head = 0;
        }
                
        put_success = true;
    }

    return put_success;
}

/**
 * @brief Gets an element from ring buffer into byte.
 *
 * @note  Returns true if successfull.
 */
extern bool ring_buffer_get(uint8_t *byte)
{    
    bool get_success = false;

    /* trying to use MY_ASSERT(byte) will result in compiler warning */    
    if(byte && (!ring_buffer_is_empty()))
    {
        /* ring buffer is not empty */
        *byte = ring_data[ring_tail];
        
        /* update tail position */
        if(++ring_tail == ring_max)
        {
            ring_tail = 0;
        }
        
        get_success = true;
    }
    
    return get_success;
}

/**
 * @brief  Returns true if ring buffer is empty (contains no elements).
 */
extern bool ring_buffer_is_empty(void)
{    
    bool buffer_empty = false;
    
    if(ring_head == ring_tail)
    {
        buffer_empty = true;
    }
    
    return buffer_empty;
}

/**
 * @brief  Returns true if ring buffer is full.
 */
extern bool ring_buffer_is_full(void)
{
    bool buffer_full = false;
    
    ring_pos_t next_head = (ring_head + 1U) % RING_SIZE;
    
    if(next_head == ring_tail)
    {
        buffer_full = true;
    }
    
    return buffer_full;
}

#else // USE_PRINTF == false

/* stub out beeper functions if USE_PRINTF is false */
extern void ring_buffer_reset(void) {}
extern bool ring_buffer_put(uint8_t byte) {UNUSED(byte); return false;}
extern bool ring_buffer_get(uint8_t *byte)
{
    UNUSED(byte);
    *byte = 0;
    return false;
}
extern bool ring_buffer_is_empty(void){return true;}
extern bool ring_buffer_is_full(void){return true;}

#endif // USE_PRINTF
/*** end of file ***/
