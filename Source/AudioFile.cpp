#include <AudioFile.h>
#include <algorithm>
#include <Utilities/Exception.h>

void AudioFile::Initialize(const std::string& waveFileName)
{
	waveFileReader_.reset(new WaveFile::WaveFileReader(waveFileName));
	waveFileName_ = waveFileName;
	audioData_ = waveFileReader_->GetAudioData()[0];  // Cache the audio data
	transientDetector_.reset(new Signal::TransientDetector(waveFileReader_->GetSampleRate()));
	transientDetector_->FindTransients(audioData_, transients_);
	peakValues_ = transientDetector_->GetFirstStepValues(audioData_);
}

bool AudioFile::FileLoaded()
{
	if(waveFileReader_.get() == nullptr)
	{
		return false;
	}

	return true;
}

std::shared_ptr<WaveFile::WaveFileReader> AudioFile::GetWaveFile()
{
	return waveFileReader_;
}

const AudioData& AudioFile::GetAudioData()
{
	return audioData_;
}

std::vector<double> AudioFile::GetPeakValues()
{
	return peakValues_;
}

std::shared_ptr<Signal::TransientDetector> AudioFile::GetTransientDetector()
{
	return transientDetector_;
}

std::size_t AudioFile::GetTransientCount()
{
	return transients_.size();
}

std::vector<std::size_t> AudioFile::GetFirstStepPeakPositions()
{
	return transientDetector_->GetFirstLevelPeakSamplePositions();
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
	peakValues_ = transientDetector_->GetFirstStepValues(audioData_);
}

std::size_t AudioFile::GetSampleCount()
{
	return waveFileReader_->GetSampleCount();
}