Below is research from the sunvox forum as relates to loading the sunvox dll into a plugin in c++ and juce:

https://warmplace.ru/forum/viewtopic.php?p=20738&hilit=sunvox+dll+plugin#p20738

Sunvox and Juce

Search this topic…
3 posts • Page 1 of 1
mrev
Posts: 46
Joined: Sun May 27, 2012 5:24 pm
Contact: Contact mrev
Sunvox and Juce
Post by mrev » Wed Oct 20, 2021 9:11 am

Starting to learn Juce in order to build plugins and am interested in whether it would feasible to include the Sunvox dll with a plugin. I am just learning and am trying to figure out if I am on the right track with what I'm picturing. Should these scenarios be possible?

1 - Host a sunvox file via the dll in a Juce app. Receive midi from a gui built with juce, note and cc control. Juce app receives the audio from the dll somehow, which outputs (a buffer?) Juce can work with.

2 - Same thing but set up an effects processing chain. So I guess pass a buffer through the dll and receive the processed buffer?

In my naive fantasy world I imagine that I can load the dll, initialize it in my Juce app with sv_open_slot( 0 ), and have access to the full dll api within my Juce code. I know its probably not going to be that simple, I'm just wondering should it be possible. Any feedback appreciated!

Thanks
Top
User avatar
NightRadio
Site Admin
Posts: 4094
Joined: Thu Jan 22, 2004 11:28 am
Location: Ekaterinburg. Russia
Contact: Contact NightRadio
Re: Sunvox and Juce
Post by NightRadio » Thu Oct 21, 2021 10:08 pm

Hi!
It is definitely possible :)

App start:
Code: Select all

sv_load_dll();
sv_init( 0, sample_rate, 2, SV_INIT_FLAG_OFFLINE );
sv_open_slot( 0 );
//make some connections or load a project file
sv_update_input();
//now start some audio stream (outside the SunVox)
App end:
Code: Select all

sv_close_slot( 0 );
sv_deinit();
sv_unload_sll();
Simplified view of the audio callback (I don't know what it actually looks like in Juce, but probably something similar):
Code: Select all

void audio_callback( int channels, int number_of_frames, float* in[ channels ], float* out[ channels ] )
{
  float temp_buf1[ number_of_frames * channels ];
  float temp_buf2[ number_of_frames * channels ];
  sv_audio_callback2( temp_buf1, number_of_frames, 0, sv_get_ticks(), 1, channels, temp_buf2 );
  for( int c = 0; c < channels; c++ )
  {
    for( int i = 0; i < number_of_frames; i++ )
    {
      out[ c ][ i ] = temp_buf1[ i * channels + c ];
      in[ c ][ i ] = temp_buf2[ i * channels + c ];
    }
  }
}
Top
mrev
Posts: 46
Joined: Sun May 27, 2012 5:24 pm
Contact: Contact mrev
Re: Sunvox and Juce
Post by mrev » Thu Oct 21, 2021 10:31 pm

Amazing, thank you Alex!!
Much appreciated
