﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace TApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer updateTimer = new DispatcherTimer();
        public MainWindow()
        {
            InitializeComponent();
        }


        public override void BeginInit()
        {
            updateTimer.Interval = new TimeSpan(160000);
            updateTimer.Tick += new EventHandler(updateTimer_Tick);
            updateTimer.Start();
            base.BeginInit();
        }

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            base.OnClosing(e);

            if (!e.Cancel)
            {
                if (null != updateTimer)
                {
                    updateTimer.Stop();
                    updateTimer = null;
                }
            }
        }

        private void updateTimer_Tick(object sender, EventArgs e)
        {
            if (null != DOfficeGLView &&
                null != DOfficeGLView.Child)
            {
                DOfficeGLView.Child.InvalidateVisual();
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            HwndHost host = new TBWrapper.GLWrapperHwnd();
            DOfficeGLView.Child = host;
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                e.Handled = true;
                this.Close();
            }
        }
    }
}
