#include <AudioFile.h>

void AudioFile::Initialize(const std::string& waveFileName)
{
	auto temp = new WaveFile::WaveFileReader(waveFileName);
	waveFileReader_.reset(temp);
	waveFileName_ = waveFileName;
}

std::shared_ptr<WaveFile::WaveFileReader> AudioFile::GetWaveFile()
{
	return waveFileReader_;
}