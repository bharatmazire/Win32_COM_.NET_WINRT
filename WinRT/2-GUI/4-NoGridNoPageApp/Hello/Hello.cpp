#include"Hello.h"
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;

void MyCallbackMethod(Windows::UI::Xaml::ApplicationInitializationCallbackParams^ param)
{
	App^ app = ref new App();
}

int main(Array < String ^ > ^ args)
{
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(MyCallbackMethod);
	Application::Start(callback);
	return(0);
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args)
{
	//Grid^ grid = ref new Grid();
	//grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);
	TextBlock^ textBlock = ref new TextBlock();
	textBlock->Text = "Hello World !!";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Pink);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	//grid->Children->Append(textBlock);

	Window::Current->Content = textBlock;
	Window::Current->Activate();

}