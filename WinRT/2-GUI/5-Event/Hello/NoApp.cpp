#include"pch.h"
#include"NoApp.h"
#include"MyPage.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;
using namespace Windows::UI;


void MyCallback(Windows::UI::Xaml::ApplicationInitializationCallbackParams^ param)
{
	App^ app = ref new App();
}

App::App()
{
	//constructor
}



int main(Array < String^> ^ args)
{
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(MyCallback);
	Application::Start(callback);
	return(0);
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args)
{
	MyPage^ page = ref new MyPage();
	/*TextBlock^ textBlock = ref new TextBlock();
	textBlock->Text = "Hello World !!";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Silver);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;*/

	Window::Current->Content = page;
	Window::Current->Activate();

}

