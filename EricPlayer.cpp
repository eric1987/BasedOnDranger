
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

int prepare()
{
    av_register_all();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
}

int open_codec()
{ 
    avcodec_alloc_context3();
    avcodec_parameters_to_context();
    av_codec_set_pkt_timebase();
    avcodec_find_decoder();
    avcodec_open2();
}

int audio_play()
{
    SDL_AudioSpec desired;
    desired.freq = audio_ctx->sample_rate;  //采样率
    desired.channels = audio_ctx->channels; //声道数
    desired.format = AUDIO_S16SYS;      //AUDIO_S16SYS;         //格式
    desired.samples = 1024;                 //缓存区大小
    desired.silence = 0;                    //静音值
    desired.userdata = this;                //回调函数中使用的数据指针
    desired.callback = audio_callback;      //回调函数

    if (SDL_OpenAudio(&desired, nullptr) < 0)
    {
        return false;
    }

    SDL_PauseAudio(0); // playing

    return true;
}

int video_play()
{
    
}

int seek()
{

}

int play()
{
    avformat_open_input();
    avformat_find_stream_info();
    
    find audio stream index;
    find video stream index;
    
    open_codec(audio);
    open_codec(video);

    audio_play();    //play audio thread
    video_play();    //play video thread

    while(1)
    {
        if(!url.empty)//playing, parse packets from stream 
        {
            while(1)
            {
                if(quit)
                {
                    flush_packet_queue();
                    break;
                }
                if(pause)
                {
                    SDL_Wait();
                    break;
                }
                if(seek_req)
                    seek();
                else
                {
                    av_read_frame();
                        if(EOF)    //end of stream. set url empty, break and wait for next stream.
                        {
                            url = "";
                            break;
                        }
                }
            }
        }
        else
        {
            if(url_list.empty)    //url_list is empty, wait for more url.
                SDL_Wait();
            else
                {
                    url = url_list.front();
                    avformat_open_input();
                    avformat_find_stream_info();
                }
        }
    }    
}
