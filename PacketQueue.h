/*
根据dranger的tutorial改写
实现不同地址可以不间断播放功能

FFmpeg3.3

author: Eric Cui
*/

#include <queue>

extern "C"
{
	#include <>
}

class PacketQueue
{
public:
	std::queue<AVPacket*> q;
	int nb_packets;
	int size;
	SDL_mutex *mutex;
	SDL_cond *cond;
}

void PacketQueueInit(PacketQueue *q);

int PacketQueuePut(PacketQueue *q, AVPacket *pkt);

static int PacketQueueGet(PacketQueue *q, AVPacket *pkt, int block);

static void PacketQueueFlush(PacketQueue *q);