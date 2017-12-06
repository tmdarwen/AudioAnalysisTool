#pragma once

class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QCheckBox;

class TransientDetectionSettings
{
	public:
		TransientDetectionSettings();
		void AddSettings(QHBoxLayout* hBoxLayout);

		QLineEdit* GetPeakThresholdLineEdit();
		QLineEdit* GetValleyToPeakRatioLineEdit();
		QCheckBox* GetTransientCheckBox();

	private:
		void AddPeakSettings(QVBoxLayout* vBoxLayout);
		void AddFrequencyDecimationSettings(QVBoxLayout* vBoxLayout);
		void AddTransientCheckBox(QVBoxLayout* vBoxLayout);

		QLineEdit* peakThresholdLineEdit_;
		QLineEdit* valleyToPeakRatioLineEdit_;

		QLineEdit* firstLevelLineEdit_;
		QLineEdit* secondLevelLineEdit_;
		QLineEdit* thirdLevelLineEdit_;

		QCheckBox* transientCheckBox_;
};