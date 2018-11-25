#ifndef __CAMERA_HEAP_MEMORY_H__
#define __CAMERA_HEAP_MEMORY_H__
namespace zeta {
static void __put_memory(camera_memory_t *data);

class CameraHeapMemory
{
public:
	CameraHeapMemory(int fd, size_t buf_size, unsigned int num_buffers = 1) :
		mBufSize(buf_size),
		mNumBufs(num_buffers)
	{
		mHeap = mmap(NULL, buf_size * num_buffers, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		commonInitialization();
	}

	CameraHeapMemory(size_t buf_size, unsigned int num_buffers = 1) :
		mBufSize(buf_size),
		mNumBufs(num_buffers)
	{		
		mHeap = malloc(buf_size * num_buffers);
		commonInitialization();
	}

	void commonInitialization()
	{
		handle.data = mHeap;
		handle.size = mBufSize * mNumBufs;
		handle.handle = this;

		mBuffers = new MemoryBase*[mNumBufs];
		for (unsigned int i = 0; i < mNumBufs; i++)
			mBuffers[i] = new MemoryBase(mHeap,
										 i * mBufSize,
										 mBufSize);

		handle.release = __put_memory;
	}

	~CameraHeapMemory()
	{
		delete [] mBuffers;
		mBuffers = NULL;
		free(mHeap);
		mHeap = NULL;
	}

	size_t mBufSize;
	unsigned int mNumBufs;
	void *mHeap;
	MemoryBase* *mBuffers;

	camera_memory_t handle;
};

static void __put_memory(camera_memory_t *data)
{
	
	if (!data)
		return;

	CameraHeapMemory *mem = static_cast<CameraHeapMemory *>(data->handle);
	delete mem;
}

static camera_memory_t* __get_memory(int fd, size_t buf_size, unsigned int num_bufs,
									 void *user __attribute__((unused)))
{
	
	CameraHeapMemory *mem;
	if (fd < 0)
		mem = new CameraHeapMemory(buf_size, num_bufs);
	else
		mem = new CameraHeapMemory(fd, buf_size, num_bufs);

	return &mem->handle;
}

}; // namespace zeta
#endif //__CAMERA_HEAP_MEMORY_H__
