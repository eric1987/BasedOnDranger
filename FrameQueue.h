/*
根据dranger的tutorial改写
实现不同地址可以不间断播放功能

FFmpeg3.3

author: Eric Cui
*/

#include <queue>



class FrameQueue
{
public:
	FrameQueue();
	~FrameQueue();
	
	std::queue<AVFrame*> q;
	int nb_packets;
	int size;
	SDL_mutex *mutex;
	SDL_cond *cond;
};

int FrameQueuePut(FrameQueue *q, AVFrame *frame);

static int FrameQueueGet(FrameQueue *q, AVFrame *frame, int block);

static void FrameQueueFlush(FrameQueue *q);