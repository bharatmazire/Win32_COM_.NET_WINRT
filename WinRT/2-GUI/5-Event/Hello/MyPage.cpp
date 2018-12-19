#include"pch.h"
#include"NoApp.h"
#include"MyPage.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;
using namespace Windows::UI;
using namespace Windows::Foundation;

MyPage::MyPage()
{
	Window::Current->CoreWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this,&MyPage::OnKeyDown);

	Grid^ grid = ref new Grid();
	
	textBlock = ref new TextBlock();
	textBlock->Text = "Event Handler !!";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Silver);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	grid->Children->Append(textBlock);

	Button^ button = ref new Button();
	button->Content = "Click Me !!";
	button->Width = 100;
	button->Height = 40;
	button->BorderThickness = 12;
	button->BorderBrush = ref new SolidColorBrush(Colors::Gold);
	button->Foreground = ref new SolidColorBrush(Colors::Red);
	button->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI");
	button->FontSize = 10;
	button->FontWeight = Windows::UI::Text::FontWeights::Bold;
	button->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	button->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	button->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
	button->Click += ref new RoutedEventHandler(this, &MyPage::OnButtonClick);

	grid->Children->Append(button);
	this->Content = grid;
}

void MyPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	textBlock->Text = "Key is Pressed";
	//if (args->VirtualKey == VirtualKey::Space)
	//{
	//	textBlock->Text = "Space pressed !!";
	//}
}

void MyPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
	textBlock->Text = "Mouse clicked !!";
}

