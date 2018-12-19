#pragma once
#include"pch.h"
#include"NoApp.h"

using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml;

ref class MyPage sealed : Page
{
private:
	TextBlock^ textBlock = ref new TextBlock();
public:
	MyPage();
	void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);
	void OnButtonClick(Object^ sender, RoutedEventArgs^ args);
};
