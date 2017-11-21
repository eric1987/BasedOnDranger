/*
根据dranger的tutorial改写
实现不同地址可以不间断播放功能

FFmpeg3.3

author: Eric Cui
*/

#include <>


class MediaState
{
public:
	MediaState();
	~MediaState();
	
	int OpenInput();

private:
	AVFormatContext *pFormatCtx;
	int audioIndex, videoIndex;

	int av_sync_type;
	double external_clock;
	int64_t external_clock_time;

	int seekReq;
	int seekFlags;
	int64_t seekPos;

	SDL_mutex       *pictq_mutex;
  	SDL_cond        *pictq_cond;

	SDL_Thread *parse_tid;

	char filename[1024];
	int quit;
};

int decode_thread