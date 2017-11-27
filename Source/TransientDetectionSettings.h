#pragma once

class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;

class TransientDetectionSettings
{
	public:
		TransientDetectionSettings();
		void AddSettings(QHBoxLayout* hBoxLayout);

	private:
		void AddPeakSettings(QVBoxLayout* vBoxLayout);
		void AddFrequencyDecimationSettings(QVBoxLayout* vBoxLayout);

		QLineEdit* peakThresholdLineEdit_;
		QLineEdit* valleyToPeakRatioLineEdit_;

		QLineEdit* firstLevelLineEdit_;
		QLineEdit* secondLevelLineEdit_;
		QLineEdit* thirdLevelLineEdit_;
};