#include "TransientDetectionSettings.h"

#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QObject>

TransientDetectionSettings::TransientDetectionSettings()
{

}

void TransientDetectionSettings::AddSettings(QHBoxLayout* hBoxLayout)
{
	auto vBoxLayout = new QVBoxLayout();
	hBoxLayout->addLayout(vBoxLayout);

	auto transientSettingsLabel = new QLabel();
	transientSettingsLabel->setText(QObject::tr("<h3><center>Transient Detection Settings</center></h3>"));
	vBoxLayout->addWidget(transientSettingsLabel);

	AddPeakSettings(vBoxLayout);

	AddFrequencyDecimationSettings(vBoxLayout);

	vBoxLayout->addStretch();
}

void TransientDetectionSettings::AddPeakSettings(QVBoxLayout* vBoxLayout)
{
	auto peakSettingsGroupBox_ = new QGroupBox();
	vBoxLayout->addWidget(peakSettingsGroupBox_);

	auto qGridLayout = new QGridLayout();

	auto peakTitleLabel = new QLabel();
	peakTitleLabel->setText(QObject::tr("<b>Peak Settings</b>"));
	qGridLayout->addWidget(peakTitleLabel, 0, 0, 1, 2);

	auto peakThresholdLevel = new QLabel(peakSettingsGroupBox_);
	peakThresholdLevel->setText("Peak Threshold Level:");
	qGridLayout->addWidget(peakThresholdLevel, 1, 0);

	peakThresholdLineEdit_ = new QLineEdit();
	peakThresholdLineEdit_->setAlignment(Qt::AlignRight);
	peakThresholdLineEdit_->setText("0.10");
	peakThresholdLineEdit_->setMaximumWidth(50);
	peakThresholdLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(peakThresholdLineEdit_, 1, 1);

	auto valleyToPeakRatioLabel = new QLabel();
	valleyToPeakRatioLabel->setText("Valley-to-Peak Ratio:");
	qGridLayout->addWidget(valleyToPeakRatioLabel, 2, 0);

	valleyToPeakRatioLineEdit_ = new QLineEdit();
	valleyToPeakRatioLineEdit_->setAlignment(Qt::AlignRight);
	valleyToPeakRatioLineEdit_->setText("1.50");
	valleyToPeakRatioLineEdit_->setMaximumWidth(50);
	valleyToPeakRatioLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(valleyToPeakRatioLineEdit_, 2, 1);

	peakSettingsGroupBox_->setLayout(qGridLayout);
}

void TransientDetectionSettings::AddFrequencyDecimationSettings(QVBoxLayout* vBoxLayout)
{
	auto frequencyDecimationGroupBox = new QGroupBox();
	vBoxLayout->addWidget(frequencyDecimationGroupBox);

	auto gridLayout = new QGridLayout();
	frequencyDecimationGroupBox->setLayout(gridLayout);

	auto titleLabel = new QLabel();
	titleLabel->setText(QObject::tr("<b>Frequency Decimation</b>"));
	gridLayout->addWidget(titleLabel, 0, 0, 1, 3);

	auto firstLevelLabel = new QLabel();
	firstLevelLabel->setText("First Level:              ");
	gridLayout->addWidget(firstLevelLabel, 1, 0);

	firstLevelLineEdit_ = new QLineEdit();
	firstLevelLineEdit_->setAlignment(Qt::AlignRight);
	firstLevelLineEdit_->setText("11.61");
	firstLevelLineEdit_->setMaximumWidth(50);
	firstLevelLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	gridLayout->addWidget(firstLevelLineEdit_, 1, 1);

	auto firstMsLabel = new QLabel();
	firstMsLabel->setText("ms");
	firstMsLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	gridLayout->addWidget(firstMsLabel, 1, 2);

	auto secondLevelLabel = new QLabel();
	secondLevelLabel->setText("Second Level:");
	gridLayout->addWidget(secondLevelLabel, 2, 0);

	secondLevelLineEdit_ = new QLineEdit();
	secondLevelLineEdit_->setAlignment(Qt::AlignRight);
	secondLevelLineEdit_->setText("5.80");
	secondLevelLineEdit_->setMaximumWidth(50);
	secondLevelLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	gridLayout->addWidget(secondLevelLineEdit_, 2, 1);

	auto secondMsLabel = new QLabel();
	secondMsLabel->setText("ms");
	secondMsLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	gridLayout->addWidget(secondMsLabel, 2, 2);

	auto thirdLevelLabel = new QLabel();
	thirdLevelLabel->setText("Third Level:");
	gridLayout->addWidget(thirdLevelLabel, 3, 0);

	thirdLevelLineEdit_ = new QLineEdit();
	thirdLevelLineEdit_->setAlignment(Qt::AlignRight);
	thirdLevelLineEdit_->setText("0.73");
	thirdLevelLineEdit_->setMaximumWidth(50);
	thirdLevelLineEdit_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	gridLayout->addWidget(thirdLevelLineEdit_, 3, 1);

	auto thirdMsLabel = new QLabel();
	thirdMsLabel->setText("ms");
	thirdMsLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	gridLayout->addWidget(thirdMsLabel, 3, 2);
}
