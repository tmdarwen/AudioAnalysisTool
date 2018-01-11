#pragma once

#include <cstddef>

class TransientView;
class WaveformView;

class Mediator
{
	public:
		Mediator();

		void AddTransientView(TransientView*);
		void AddWaveformView(WaveformView*);

		void UpdateTransientChart(std::size_t rowStart, std::size_t rowEnd);
		void UpdateWaveformAnalysisArea(std::size_t sampleStartPosition, std::size_t sampleEndPosition);
		void PeakThresholdUpdated(double newPeakThreshold);
		void ValleyToPeakThresholdUpdated(double newPeakThreshold);
		void StepSizeUpdated(std::size_t newValue);
		void PointCountUpdated(std::size_t newValue);
		void TransientCheckBoxChanged(int state);
		void HighlightWaveformCheckBoxChanged(int state);

	private:
		TransientView* transientView_;
		WaveformView* waveformView_;
};
