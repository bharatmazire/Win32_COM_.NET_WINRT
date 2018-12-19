#pragma once
#include"pch.h"
#include"MyPage.h"

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::Activation;

ref class App sealed : public Windows::UI::Xaml::Application
{
public:
	App();
	virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args)override;
};
