using System;
using System.Drawing;
using System.Windows.Forms;

public class SimpleWindowV1 : Form
{
    public static void Main()
    {
        Application.Run(new SimpleWindowV1());
    }

    public SimpleWindowV1()
    {
        Width = 800;
        Height = 600;
        ResizeRedraw = true;
    }
}