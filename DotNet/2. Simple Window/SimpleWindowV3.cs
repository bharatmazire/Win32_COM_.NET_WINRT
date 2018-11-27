using System;
using System.Drawing;
using System.Windows.Forms;

public class SimpleWindowsV3 : Form
{
    public static void Main()
    {
        Application.Run(new SimpleWindowsV3());
    }

    public SimpleWindowsV3()
    {
        Width = 800;
        Height = 600;
        BackColor = Color.Black;
        ResizeRedraw = true;

        this.KeyDown += new KeyEventHandler(MyKeydown);
        this.MouseDown += new MouseEventHandler(MyMousedown);
    }
    void MyKeydown(Object sender, KeyEventArgs e)
    {
        MessageBox.Show("Some key pressed !!!");
    }

    void MyMousedown(Object sender, MouseEventArgs e)
    {
        MessageBox.Show("Some mouse clicked !!!");
    }
}