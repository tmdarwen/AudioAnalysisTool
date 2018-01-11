#include "TransientSettings.h"
#include "Mediator.h"
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QObject>


PeakThresholdEdit::PeakThresholdEdit()
{
	QMetaObject::connectSlotsByName(this);
	QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(ValueChanged()));
}

void PeakThresholdEdit::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void PeakThresholdEdit::ValueChanged()
{
	auto newValue{text().toDouble()};
	if(newValue < .01) { newValue = 0.1;  }
	else if(newValue > 1.0) { newValue = 1.0;  }

	// Update the UI with the actual value
	setText(QString::number(newValue, 'f', 2));

	mediator_->PeakThresholdUpdated(newValue);
}


ValleyToPeakThresholdEdit::ValleyToPeakThresholdEdit()
{
	QMetaObject::connectSlotsByName(this);
	QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(ValueChanged()));
}

void ValleyToPeakThresholdEdit::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void ValleyToPeakThresholdEdit::ValueChanged()
{
	auto newValue{text().toDouble()};
	if(newValue < 0.1) { newValue = 0.1;  }
	else if(newValue > 100.0) { newValue = 100.0;  }

	// Update the UI with the actual value
	setText(QString::number(newValue, 'f', 2));

	mediator_->ValleyToPeakThresholdUpdated(newValue);
}


StepSizeEdit::StepSizeEdit()
{
	QMetaObject::connectSlotsByName(this);
	QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(ValueChanged()));
}

void StepSizeEdit::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void StepSizeEdit::ValueChanged()
{
	auto newValue{text().toInt()};
	if(newValue < 32) { newValue = 32;  }
	else if(newValue > 4192) { newValue = 4192;  }

	// Update the UI with the actual value
	setText(QString::number(newValue));

	mediator_->StepSizeUpdated(newValue);
}


PointCountEdit::PointCountEdit()
{
	QMetaObject::connectSlotsByName(this);
	QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(ValueChanged()));
}

void PointCountEdit::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void PointCountEdit::ValueChanged()
{
	auto newValue{text().toInt()};
	if(newValue < 10) { newValue = 10;  }
	else if(newValue > 100) { newValue = 100;  }

	// Update the UI with the actual value
	setText(QString::number(newValue));

	mediator_->PointCountUpdated(newValue);
}


DisplayTransientsCheckbox::DisplayTransientsCheckbox(const std::string& description) : QCheckBox(description.c_str())
{
	QMetaObject::connectSlotsByName(this);
	QObject::connect(this, SIGNAL(stateChanged(int)), this, SLOT(ValueChanged(int)));
}

void DisplayTransientsCheckbox::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void DisplayTransientsCheckbox::ValueChanged(int state)
{
	mediator_->TransientCheckBoxChanged(state);
}


HighlightWaveformCheckbox::HighlightWaveformCheckbox(const std::string& description) : QCheckBox(description.c_str())
{
	QMetaObject::connectSlotsByName(this);
	QObject::connect(this, SIGNAL(stateChanged(int)), this, SLOT(ValueChanged(int)));
}

void HighlightWaveformCheckbox::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void HighlightWaveformCheckbox::ValueChanged(int state)
{
	mediator_->HighlightWaveformCheckBoxChanged(state);
}


TransientSettings::TransientSettings()
{

}

void TransientSettings::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
	peakThresholdLineEdit_->SetMediator(mediator);
	valleyToPeakRatioLineEdit_->SetMediator(mediator);
	stepSizeLineEdit_->SetMediator(mediator);
	pointCountLineEdit_->SetMediator(mediator);
	transientCheckBox_->SetMediator(mediator);
	highlightWaveformCheckBox_->SetMediator(mediator);
}

void TransientSettings::AddSettings(QHBoxLayout* hBoxLayout)
{
	auto vBoxLayout = new QVBoxLayout();
	hBoxLayout->addLayout(vBoxLayout);

	AddPeakSettings(vBoxLayout);

	vBoxLayout->addStretch();
}

void TransientSettings::AddPeakSettings(QVBoxLayout* vBoxLayout)
{
	auto peakSettingsGroupBox_ = new QFrame();
	peakSettingsGroupBox_->setFrameStyle(QFrame::StyledPanel);

	vBoxLayout->addWidget(peakSettingsGroupBox_);

	auto qGridLayout = new QGridLayout();

	auto peakTitleLabel = new QLabel();
	peakTitleLabel->setText(QObject::tr("<b>Peak Settings</b>"));
	qGridLayout->addWidget(peakTitleLabel, 0, 0, 1, 2);

	auto peakThresholdLevel = new QLabel(peakSettingsGroupBox_);
	peakThresholdLevel->setText("Peak Threshold Level:");
	qGridLayout->addWidget(peakThresholdLevel, 1, 0);

	peakThresholdLineEdit_ = new PeakThresholdEdit();
	peakThresholdLineEdit_->setAlignment(Qt::AlignRight);
	peakThresholdLineEdit_->setText("0.10");
	peakThresholdLineEdit_->setMaximumWidth(50);
	peakThresholdLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(peakThresholdLineEdit_, 1, 1);

	auto valleyToPeakRatioLabel = new QLabel();
	valleyToPeakRatioLabel->setText("Valley-to-Peak Ratio:");
	qGridLayout->addWidget(valleyToPeakRatioLabel, 2, 0);

	valleyToPeakRatioLineEdit_ = new ValleyToPeakThresholdEdit();
	valleyToPeakRatioLineEdit_->setAlignment(Qt::AlignRight);
	valleyToPeakRatioLineEdit_->setText("1.50");
	valleyToPeakRatioLineEdit_->setMaximumWidth(50);
	valleyToPeakRatioLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(valleyToPeakRatioLineEdit_, 2, 1);

	auto stepSizeLabel = new QLabel();
	stepSizeLabel->setText("Step Size:");
	qGridLayout->addWidget(stepSizeLabel, 3, 0);

	stepSizeLineEdit_ = new StepSizeEdit();
	stepSizeLineEdit_->setAlignment(Qt::AlignRight);
	stepSizeLineEdit_->setText("512");
	stepSizeLineEdit_->setMaximumWidth(50);
	stepSizeLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(stepSizeLineEdit_, 3, 1);

	auto pointCountLabel = new QLabel();
	pointCountLabel->setText("Points In Chart:");
	qGridLayout->addWidget(pointCountLabel, 4, 0);

	pointCountLineEdit_ = new PointCountEdit();
	pointCountLineEdit_->setAlignment(Qt::AlignRight);
	pointCountLineEdit_->setText("40");
	pointCountLineEdit_->setMaximumWidth(50);
	pointCountLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(pointCountLineEdit_, 4, 1);

	transientCheckBox_ = new DisplayTransientsCheckbox("Display Transient Positions");
	transientCheckBox_->setChecked(false);
	qGridLayout->addWidget(transientCheckBox_, 5, 0, 1, 2);

	highlightWaveformCheckBox_ = new HighlightWaveformCheckbox("Highlight Analysis Area");
	highlightWaveformCheckBox_->setChecked(false);
	qGridLayout->addWidget(highlightWaveformCheckBox_, 6, 0, 1, 2);

	peakSettingsGroupBox_->setLayout(qGridLayout);
}