#ifndef __MEMORY_BASE_H__
#define __MEMORY_BASE_H__

#include <stdlib.h>
#include <stdint.h>

namespace zeta {

// ---------------------------------------------------------------------------

class MemoryBase
{
public:
    MemoryBase(void* heap, ssize_t offset, size_t size);
    virtual ~MemoryBase();
    virtual void* getMemory(ssize_t* offset, size_t* size) const;

protected:
    size_t getSize() const { return mSize; }
    ssize_t getOffset() const { return mOffset; }
    const void* getHeap() const { return mHeap; }

private:
    size_t          mSize;
    ssize_t         mOffset;
    void* mHeap;
};

// ---------------------------------------------------------------------------
}; // namespace zeta

#endif // __MEMORY_BASE_H__
