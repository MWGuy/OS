#include <memory.h>

MemoryManager* MemoryManager::activeMemoryManager = nullptr;

MemoryManager::MemoryManager(size_t start, size_t size) {
    activeMemoryManager = this;

    if(size < sizeof(MemoryChunk)) {
        first = nullptr;
    } else {
        first = (MemoryChunk *) start;
        first->allocated = false;
        first->prev = nullptr;
        first->next = nullptr;
        first->size = size - sizeof(MemoryChunk);
    }
}

MemoryManager::~MemoryManager() {
    if(activeMemoryManager == this)
        activeMemoryManager = nullptr;
}

void * MemoryManager::malloc(size_t size) {
    MemoryChunk * result = nullptr;

    for(MemoryChunk* chunk = first; chunk != nullptr && result == nullptr; chunk = chunk->next)
        if(chunk->size > size && !chunk->allocated)
            result = chunk;

    if(result == nullptr)
        return nullptr;

    if(result->size >= size + sizeof(MemoryChunk) + 1)
    {
        auto * temp = (MemoryChunk *)(result + sizeof(MemoryChunk) + size);

        temp->allocated = false;
        temp->size = result->size - size - sizeof(MemoryChunk);
        temp->prev = result;
        temp->next = result->next;
        if(temp->next != nullptr)
            temp->next->prev = temp;

        result->size = size;
        result->next = temp;
    }

    result->allocated = true;
    return (void *)((result) + sizeof(MemoryChunk));
}

void MemoryManager::free(void * ptr)
{
    auto * chunk = (MemoryChunk*)((unsigned long)ptr - sizeof(MemoryChunk));

    chunk -> allocated = false;

    if(chunk->prev != nullptr && !chunk->prev->allocated)
    {
        chunk->prev->next = chunk->next;
        chunk->prev->size += chunk->size + sizeof(MemoryChunk);
        if(chunk->next != nullptr)
            chunk->next->prev = chunk->prev;

        chunk = chunk->prev;
    }

    if(chunk->next != nullptr && !chunk->next->allocated)
    {
        chunk->size += chunk->next->size + sizeof(MemoryChunk);
        chunk->next = chunk->next->next;
        if(chunk->next != 0)
            chunk->next->prev = chunk;
    }

}

void * operator new(unsigned int size) {
    if(MemoryManager::activeMemoryManager == nullptr)
        return nullptr;
    return MemoryManager::activeMemoryManager->malloc(size);
}

void * operator new[](unsigned int size) {
    if(MemoryManager::activeMemoryManager == nullptr)
        return nullptr;
    return MemoryManager::activeMemoryManager->malloc(size);
}

void * operator new(unsigned int size, void * ptr) {
    return ptr;
}

void * operator new[](unsigned int size, void * ptr) {
    return ptr;
}

void operator delete(void * ptr) {
    if(MemoryManager::activeMemoryManager != nullptr)
        MemoryManager::activeMemoryManager->free(ptr);
}

void operator delete[](void * ptr) {
    if(MemoryManager::activeMemoryManager != nullptr)
        MemoryManager::activeMemoryManager->free(ptr);
}