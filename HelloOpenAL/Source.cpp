//====Reference====
//Source Code: https://github.com/cpp-wrappers/openal-wrapper/blob/master/src/source.cpp
//Audio Source: https://opengameart.org/content/spell-4-fire

#include <sndfile.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <array>

#include <cstdlib>

using namespace std;

int main()
{
	const char* const fName = "src/foom_0.wav";

	SF_INFO sfInfo;
	SNDFILE* myWAV = sf_open(fName, SFM_READ, &sfInfo);

	cout << "samplerate: " << sfInfo.samplerate << endl;
	cout << "frames: " << sfInfo.frames << endl;
	cout << "channels: " << sfInfo.channels << endl;
	cout << "format: " << sfInfo.format << endl;

	array<int16_t, 304940> rawWAV;
	array<int16_t, 304940>::iterator i;
	sf_read_short(myWAV, rawWAV.data(), rawWAV.size());
	
	ALCdevice* myDevice = alcOpenDevice(nullptr);
	ALCcontext* myContext = alcCreateContext(myDevice, nullptr);
	alcMakeContextCurrent(myContext);

	const ALfloat pitch = 0.5f;
	ALuint myBuf, mySrc;
	alGenBuffers(1, &myBuf);
	alGenSources(1, &mySrc);

	alBufferData(myBuf, sfInfo.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
		rawWAV.data(), rawWAV.size() * sizeof(uint16_t), sfInfo.samplerate);
	alSourcei(mySrc, AL_BUFFER, myBuf);
	alSourcef(mySrc, AL_PITCH, pitch);

	alSourcePlay(mySrc);
	system("pause");

	sf_close(myWAV);

	return 0;
}