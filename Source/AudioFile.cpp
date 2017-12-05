#include <AudioFile.h>
#include <algorithm>
#include <Utilities/Exception.h>

void AudioFile::Initialize(const std::string& waveFileName)
{
	auto temp = new WaveFile::WaveFileReader(waveFileName);
	waveFileReader_.reset(temp);
	waveFileName_ = waveFileName;
	audioData_ = waveFileReader_->GetAudioData()[0].GetData();  // Cache the audio data
	transientDetector_.reset(new Signal::TransientDetector(waveFileReader_->GetSampleRate()));
	transientDetector_->FindTransients(audioData_, transients_);
}

std::shared_ptr<WaveFile::WaveFileReader> AudioFile::GetWaveFile()
{
	return waveFileReader_;
}

const std::vector<double>& AudioFile::GetAudioData()
{
	return audioData_;
}

std::shared_ptr<Signal::TransientDetector> AudioFile::GetTransientDetector()
{
	return transientDetector_;
}

std::size_t AudioFile::GetTransientCount()
{
	return transients_.size();
}

std::size_t AudioFile::GetTransient(std::size_t transientNumber)
{
	if(transientNumber >= transients_.size())
	{
		Utilities::ThrowException("Attempting to get transient that doesn't exist");
	}

	return transients_[transientNumber];
}

const std::vector<std::size_t> AudioFile::GetTransients() const
{
	return transients_;
}

void AudioFile::RefreshTransients()
{
	transients_.clear();
	transientDetector_->FindTransients(audioData_, transients_);
}
