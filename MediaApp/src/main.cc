#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "audio_device.h"
#include "file_wrapper.h"
#include "list_wrapper.h"
#include "sleep.h"
#define MAX_AUDIO_PACKET 256
using namespace webrtc;

namespace webrtc
{
	typedef struct AudioPacket
	{
		WebRtc_UWord8 dataBuffer[4 * 960];
		WebRtc_UWord16 nSamples;
		WebRtc_UWord16 nBytesPerSample;
		WebRtc_UWord8 nChannels;
		WebRtc_UWord32 samplesPerSec;
	}AudioPacket;
	class AudioTransportImpl: public AudioTransport
	{
	public:
		virtual WebRtc_Word32
			RecordedDataIsAvailable(const void* audioSamples,
			const WebRtc_UWord32 nSamples,
			const WebRtc_UWord8 nBytesPerSample,
			const WebRtc_UWord8 nChannels,
			const WebRtc_UWord32 samplesPerSec,
			const WebRtc_UWord32 totalDelayMS,
			const WebRtc_Word32 clockDrift,
			const WebRtc_UWord32 currentMicLevel,
			WebRtc_UWord32& newMicLevel);

		virtual WebRtc_Word32 NeedMorePlayData(const WebRtc_UWord32 nSamples,
			const WebRtc_UWord8 nBytesPerSample,
			const WebRtc_UWord8 nChannels,
			const WebRtc_UWord32 samplesPerSec,
			void* audioSamples,
			WebRtc_UWord32& nSamplesOut);
		AudioPacket* GetPacket();
		AudioTransportImpl():_recCount(0), _playCount(0)
		{
			packet_semaphore = CreateSemaphore(NULL, 0, MAX_AUDIO_PACKET, L"packet_semaphore");
		};
		~AudioTransportImpl(){};		
	private:		
		WebRtc_UWord32 _recCount;
		WebRtc_UWord32 _playCount;	
		ListWrapper _audioList;
		HANDLE packet_semaphore;
	};
	AudioPacket* AudioTransportImpl::GetPacket()
	{
		WaitForSingleObject(packet_semaphore, INFINITE);		
		ListItem* item = _audioList.First();
		AudioPacket* packet = (AudioPacket*)item->GetItem();
		_audioList.PopFront();		
		return packet;
	}
	WebRtc_Word32 AudioTransportImpl::NeedMorePlayData(const WebRtc_UWord32 nSamples,
			const WebRtc_UWord8 nBytesPerSample,
			const WebRtc_UWord8 nChannels,
			const WebRtc_UWord32 samplesPerSec,
			void* audioSamples,
			WebRtc_UWord32& nSamplesOut)
	{
		return 0;
	}
	WebRtc_Word32 AudioTransportImpl::RecordedDataIsAvailable(const void* audioSamples,
			const WebRtc_UWord32 nSamples,
			const WebRtc_UWord8 nBytesPerSample,
			const WebRtc_UWord8 nChannels,
			const WebRtc_UWord32 samplesPerSec,
			const WebRtc_UWord32 totalDelayMS,
			const WebRtc_Word32 clockDrift,
			const WebRtc_UWord32 currentMicLevel,
			WebRtc_UWord32& newMicLevel)
	{
		long packet_count = 0;
		AudioPacket* packet = new AudioPacket();
        memcpy(packet->dataBuffer, audioSamples, nSamples * nBytesPerSample);
        packet->nSamples = (WebRtc_UWord16) nSamples;
        packet->nBytesPerSample = nBytesPerSample;
        packet->nChannels = nChannels;
        packet->samplesPerSec = samplesPerSec;
        _audioList.PushBack(packet);
		ReleaseSemaphore(packet_semaphore, 1, &packet_count);
		return 0;
	}
}
int main()
{
	
	AudioDeviceModule* audio_device = CreateAudioDeviceModule(0, AudioDeviceModule::kPlatformDefaultAudio);
	AudioTransportImpl* audio_callback = new AudioTransportImpl();
	audio_device->Init();
	{
		int devices_count = audio_device->RecordingDevices();
		char device_name[256];
		char guid[256];
		for (int i = 0; i < devices_count; i++)
		{
			audio_device->RecordingDeviceName(i, device_name, guid);
			printf("The %dth device's name: %s, guid: %s. \n", i, device_name, guid);
		}
	}
	//AudioTransport* callBack = webrtc::
	
	audio_device->RegisterAudioCallback(audio_callback);

	
	audio_device->SetRecordingDevice(0);
	audio_device->SetRecordingSampleRate(24000);
	audio_device->InitRecording();
	int ret = audio_device->StartRecording();

	FileWrapper* file = FileWrapper::Create();
	file->OpenFile("record.pcm", false);
	while (true)
	{		
		AudioPacket* packet = audio_callback->GetPacket();
		file->Write(packet->dataBuffer, packet->nSamples*packet->nBytesPerSample);		
	}
}