using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfacePC
{
    public partial class wallpaper : Form
    {
        public wallpaper()
        {
            InitializeComponent();
        }

        private async void wallpaper_Load(object sender, EventArgs e)
        {
            await Task.Delay(5000);
            this.Close();
        }
    }
}
