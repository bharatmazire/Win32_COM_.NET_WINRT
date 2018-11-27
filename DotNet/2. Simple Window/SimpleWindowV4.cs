using System;
using System.Drawing;
using System.Windows.Forms;

public class SimpleWindowV4 : Form
{
    public static void Main()
    {
        Application.Run(new SimpleWindowV4());
    }
    public SimpleWindowV4()
    {
        Icon = new Icon("github.ico");
        ResizeRedraw = true;
        Width = 800;
        Height = 600;
    }
}
