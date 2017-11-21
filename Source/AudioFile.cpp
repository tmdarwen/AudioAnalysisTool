#include <AudioFile.h>
#include <algorithm>

void AudioFile::Initialize(const std::string& waveFileName)
{
	auto temp = new WaveFile::WaveFileReader(waveFileName);
	waveFileReader_.reset(temp);
	waveFileName_ = waveFileName;
	audioData_ = waveFileReader_->GetAudioData()[0].GetData();  // Cache the audio data
}

std::shared_ptr<WaveFile::WaveFileReader> AudioFile::GetWaveFile()
{
	return waveFileReader_;
}

const std::vector<double>& AudioFile::GetAudioData()
{
	return audioData_;
}
