#pragma once
#include"pch.h"
using namespace Platform;

ref class App sealed : public Windows::UI::Xaml::Application
{
public:
	virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) override;
};
