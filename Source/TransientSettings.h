#pragma once

#include <QLineEdit>
#include <QCheckBox>

class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QCheckBox;
class Mediator;

class PeakThresholdEdit : public QLineEdit
{
	Q_OBJECT;

	public:
		PeakThresholdEdit();
		void SetMediator(Mediator* mediator);

	private slots:
		void ValueChanged();

	private:
		Mediator* mediator_;
};


class ValleyToPeakThresholdEdit : public QLineEdit
{
	Q_OBJECT;

	public:
		ValleyToPeakThresholdEdit();
		void SetMediator(Mediator* mediator);

	private slots:
		void ValueChanged();

	private:
		Mediator* mediator_;
};


class StepSizeEdit : public QLineEdit
{
	Q_OBJECT;

	public:
		StepSizeEdit();
		void SetMediator(Mediator* mediator);

	private slots:
		void ValueChanged();

	private:
		Mediator* mediator_;
};


class PointCountEdit : public QLineEdit
{
	Q_OBJECT;

	public:
		PointCountEdit();
		void SetMediator(Mediator* mediator);

	private slots:
		void ValueChanged();

	private:
		Mediator* mediator_;
};


class DisplayTransientsCheckbox : public QCheckBox
{
	Q_OBJECT;

	public:
		DisplayTransientsCheckbox(const std::string& description);
		void SetMediator(Mediator* mediator);

	private slots:
		void ValueChanged(int state);

	private:
		Mediator* mediator_;
};


class HighlightWaveformCheckbox : public QCheckBox
{
	Q_OBJECT;

	public:
		HighlightWaveformCheckbox(const std::string& description);
		void SetMediator(Mediator* mediator);

	private slots:
		void ValueChanged(int state);

	private:
		Mediator* mediator_;
};


class TransientSettings
{
	public:
		TransientSettings();
		void AddSettings(QHBoxLayout* hBoxLayout);
		void SetMediator(Mediator* mediator);
		void ResetToDefaults();

	private:
		void AddPeakSettings(QVBoxLayout* vBoxLayout);

		Mediator* mediator_;

		PeakThresholdEdit* peakThresholdLineEdit_;
		ValleyToPeakThresholdEdit* valleyToPeakRatioLineEdit_;
		StepSizeEdit* stepSizeLineEdit_;
		PointCountEdit* pointCountLineEdit_;

		DisplayTransientsCheckbox* transientCheckBox_;
		HighlightWaveformCheckbox* highlightWaveformCheckBox_;
};