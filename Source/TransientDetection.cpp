#include "TransientDetection.h"
#include "TransientView.h"
#include "Mediator.h"
#include <QVBoxLayout>
#include <QTabWidget>

TransientDetection::TransientDetection()
{

}

void TransientDetection::AddControls(QWidget* widget)
{
	auto hBoxLayout = new QHBoxLayout(widget);
	transientSettings_.AddSettings(hBoxLayout);
	transientView_.AddControls(hBoxLayout);
}

void TransientDetection::Update()
{
	transientView_.Update();
}

TransientView* TransientDetection::GetTransientView()
{
	return &transientView_;
}

void TransientDetection::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
	transientSettings_.SetMediator(mediator);
	transientView_.SetMediator(mediator);
}

void TransientDetection::ResetSettingsToDefaults()
{
	transientSettings_.ResetToDefaults();
}