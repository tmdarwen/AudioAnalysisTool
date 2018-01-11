#pragma once

#include <string>
#include <TransientSettings.h>
#include <TransientView.h>

class QVBoxLayout;
class QWidget;
class Mediator;

class TransientDetection
{
	public:
		TransientDetection();
		void AddControls(QWidget* widget);
		void Update();

		void SetMediator(Mediator* mediator);

		TransientView* GetTransientView();

	private:
		TransientSettings transientSettings_;
		TransientView transientView_;
		Mediator* mediator_;
};
