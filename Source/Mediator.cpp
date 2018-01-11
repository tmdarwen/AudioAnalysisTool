#include "Mediator.h"
#include "TransientView.h"
#include "TransientChart.h"
#include "WaveformView.h"
#include "AudioFile.h"

Mediator::Mediator()
{

}
void Mediator::AddTransientView(TransientView* transientView)
{
	transientView_ = transientView;
}

void Mediator::AddWaveformView(WaveformView* waveformView)
{
	waveformView_ = waveformView;
}

void Mediator::UpdateTransientChart(std::size_t rowStart, std::size_t rowEnd)
{
	auto chart{transientView_->GetTransientChart()};
	chart->Update(rowStart, rowEnd);
}

void Mediator::UpdateWaveformAnalysisArea(std::size_t sampleStartPosition, std::size_t sampleEndPosition)
{
	waveformView_->UpdateAnalysisArea(sampleStartPosition, sampleEndPosition);
}

void Mediator::TransientCheckBoxChanged(int state)
{
	if(state == 0)
	{
		waveformView_->DisplayTransients(false);
	}
	else
	{
		waveformView_->DisplayTransients(true);
	}
}

void Mediator::HighlightWaveformCheckBoxChanged(int state)
{
	if(state == 0)
	{
		waveformView_->HighlightAnalysisArea(false);
	}
	else
	{
		waveformView_->HighlightAnalysisArea(true);
	}
}

void Mediator::PeakThresholdUpdated(double newPeakThreshold)
{
	// Update the transient detector with the new value
	auto transientDetector{AudioFile::GetInstance().GetTransientDetector()};

	// If no audio file is loaded, or the new value is the same as the old value, there's nothing we need to do.
	if(!AudioFile::GetInstance().FileLoaded() || transientDetector->GetMinimumPeakLevel() == newPeakThreshold)
	{
		return;
	}

	// Update the transient detector with the new value
	transientDetector->Reset();
	transientDetector->SetMinimumPeakLevel(newPeakThreshold);
	AudioFile().GetInstance().RefreshTransients();

	// Update the waveform view
	waveformView_->Update();

	// Update the transient view
	transientView_->Update();
}

void Mediator::ValleyToPeakThresholdUpdated(double newValleyToPeakThreshold)
{
	// Update the transient detector with the new value
	auto transientDetector{AudioFile::GetInstance().GetTransientDetector()};

	// If no audio file is loaded, or the new value is the same as the old value, there's nothing we need to do.
	if(!AudioFile::GetInstance().FileLoaded() || transientDetector->GetValleyToPeakRatio() == newValleyToPeakThreshold)
	{
		return;
	}

	// Update the transient detector with the new value
	transientDetector->Reset();
	transientDetector->SetValleyToPeakRatio(newValleyToPeakThreshold);
	AudioFile().GetInstance().RefreshTransients();

	// Update the waveform view
	waveformView_->Update();

	// Update the transient view
	transientView_->Update();
}

void Mediator::StepSizeUpdated(std::size_t newFirstLevelStepSize)
{
	// Update the transient detector with the new value
	auto transientDetector{AudioFile::GetInstance().GetTransientDetector()};

	// If no audio file is loaded, or the new value is the same as the old value, there's nothing we need to do.
	if(!AudioFile::GetInstance().FileLoaded() || transientDetector->GetStepInSamples(Signal::TransientDetector::Step::First) == newFirstLevelStepSize)
	{
		return;
	}

	// Update the transient detector with the new value
	transientDetector->Reset();
	transientDetector->SetStepInSamples(newFirstLevelStepSize, Signal::TransientDetector::Step::First);
	AudioFile().GetInstance().RefreshTransients();

	// Update the waveform view
	waveformView_->Update();

	// Update the transient view
	transientView_->SetFirstLevelStepSize(newFirstLevelStepSize);
	transientView_->Update();
}

void Mediator::PointCountUpdated(std::size_t newValue)
{
	// Update the transient view
	transientView_->SetChartPointCount(newValue);
	transientView_->Update();
}