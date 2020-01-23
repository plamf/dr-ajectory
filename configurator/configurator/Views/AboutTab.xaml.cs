using System.Diagnostics;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace configurator.Views
{
    public partial class AboutTab : UserControl
    {
        public AboutTab()
        {
            InitializeComponent();
        }

        private void Hyperlink_OnRequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            e.Handled = true;
        }
    }
}