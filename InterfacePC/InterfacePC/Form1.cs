using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace InterfacePC
{
    public partial class Form1 : Form
    {

        double valor1, valor2, valor3; //Variáveis para guardar os valores recebidos
        string direcao, RxString;  // Ver depois para tirar essa variável de direção

        public Form1()
        {
            new wallpaper().Show();
            Thread.Sleep(5000);

            InitializeComponent();
        }

        private void atualizaListaCOMs()
        {
            int i;
            bool quantDiferente; //flag para sinalizar que a quantidade de portas mudou

            i = 0;
            quantDiferente = false;

            //se a quantidade de portas mudou
            if (cBoxCOMs.Items.Count == SerialPort.GetPortNames().Length)
            {
                foreach (string s in SerialPort.GetPortNames())
                {
                    if (cBoxCOMs.Items[i++].Equals(s) == false)
                    {
                        quantDiferente = true;
                    }
                }
            }
            else
            {
                quantDiferente = true;
            }

            //Se não foi detectado diferença
            if (quantDiferente == false)
            {
                return;                     //retorna
            }

            //limpa comboBox
            cBoxCOMs.Items.Clear();

            //adiciona todas as COM diponíveis na lista
            foreach (string s in SerialPort.GetPortNames())
            {
                cBoxCOMs.Items.Add(s);
            }
            //seleciona a primeira posição da lista
            //cBoxCOMs.SelectedIndex = 0;
        }

        private void timerCOM_Tick(object sender, EventArgs e)
        {
            atualizaListaCOMs();
        }

        private void btnConectar_Click(object sender, EventArgs e)
        {
            if (SerialPort.IsOpen == false)
            {
                try
                {
                    SerialPort.PortName = cBoxCOMs.Items[cBoxCOMs.SelectedIndex].ToString();
                    SerialPort.Open();
                }
                catch
                {
                    return;
                }
                if (SerialPort.IsOpen)
                {
                    btnConectar.Text = "Desconectar";
                    cBoxCOMs.Enabled = false;
                }
            }
            else
            {
                try
                {
                    SerialPort.Close();
                    cBoxCOMs.Enabled = true;
                    btnConectar.Text = "Conectar";
                }
                catch
                {
                    return;
                }
            }
        }

        private void calculaValores()
        {
            try
            {
                switch (cBoxPeso1.SelectedIndex)
                {
                    case 0:
                        valor1 = Convert.ToDouble(txtBoxValor1.Text);
                        break;
                    case 1:
                        valor1 = Convert.ToDouble(txtBoxValor1.Text) * (1000);
                        break;
                    case 2:
                        valor1 = Convert.ToDouble(txtBoxValor1.Text) * (1000000);
                        break;

                }
                switch (cBoxPeso2.SelectedIndex)
                {
                    case 0:
                        valor2 = Convert.ToDouble(txtBoxValor2.Text);
                        break;
                    case 1:
                        valor2 = Convert.ToDouble(txtBoxValor2.Text) * (1000);
                        break;
                    case 2:
                        valor2 = Convert.ToDouble(txtBoxValor2.Text) * (1000000);
                        break;

                }
                switch (cBoxPeso3.SelectedIndex)
                {
                    case 0:
                        valor3 = Convert.ToDouble(txtBoxValor3.Text);
                        break;
                    case 1:
                        valor3 = Convert.ToDouble(txtBoxValor3.Text) * (1000);
                        break;
                    case 2:
                        valor3 = Convert.ToDouble(txtBoxValor3.Text) * (1000000);
                        break;

                }
            }
            catch
            {
                DialogResult res = MessageBox.Show("É necessário revisar os dados colocados" + "\n" + "Obs.: Verifique se no lugar do ponto foi colocado uma vírgula", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private async void ativarMotor()
        {

            string velocidade = Convert.ToString(numericVelocidade.Value);

            if (rBtnHorario.Checked)
            {
                direcao = "horario";
            }

            if (rBtnAntiHorario.Checked)
            {
                direcao = "antihorario";
            }

            SerialPort.WriteLine("velocidade,");
            SerialPort.WriteLine(velocidade);
            await Task.Delay(1500);
            SerialPort.WriteLine("direcao,");
            SerialPort.WriteLine(direcao);
        }

        private void btnConectar_Click_1(object sender, EventArgs e)
        {
            if (SerialPort.IsOpen == false)
            {
                try
                {
                    SerialPort.PortName = cBoxCOMs.Items[cBoxCOMs.SelectedIndex].ToString();
                    SerialPort.Open();
                    // Mandar instrução para aparecer no display que está conectado
                }
                catch
                {
                    return;

                }
                if (SerialPort.IsOpen)
                {
                    cBoxCOMs.Enabled = false;
                }
            }
            else
            {
                try
                {
                    SerialPort.Close();
                    cBoxCOMs.Enabled = true;
                    btnConectar.Text = "Conectar";
                }
                catch
                {
                    return;
                }

            }
            btnConectar.Enabled = false;
            btnDesconectar.Enabled = true;
        }

        private void desativarMotor()
        {
            SerialPort.WriteLine("desativarmotor,");
        }

        private void btnDesliga_Click(object sender, EventArgs e)
        {
            SerialPort.Write("desliga,");
        }

        private void btnDesconectar_Click(object sender, EventArgs e)
        {
            SerialPort.Close();
            btnConectar.Enabled = true;
            btnDesconectar.Enabled = false;
            cBoxCOMs.Enabled = true;
        }

        private void btnLimpar_Click(object sender, EventArgs e)
        {
            txtBoxValor1.Text = "";
            txtBoxValor2.Text = "";
            txtBoxValor3.Text = "";
            cBoxCOMs.SelectedIndex = -1;
            cBoxPeso1.SelectedIndex = 0;
            cBoxPeso2.SelectedIndex = 0;
            cBoxPeso3.SelectedIndex = 0;
            txtBoxRRecebida.Text = "";
            txtBoxSerialRx.Text = "";
            btnDesconectar.Enabled = false;
            cBoxCOMs.Enabled = true;
            btnConectar.Enabled = true;

            // Mandar uma instrução para limpar a tela LCD
            SerialPort.Close();

        }

        private async void btnIniciar_Click(object sender, EventArgs e)
        {
            try
            {
                new Working().Show();
     
                calculaValores(); // Pega os dados inseridos e coloca-se os pesos
                string send1 = String.Format(Convert.ToString(valor1)); // Manda o valor 1
                string send2 = String.Format(Convert.ToString(valor2)); // Manda o valor 2
                string send3 = String.Format(Convert.ToString(valor3)); // Manda o valor 3

                // Valores recebidos do Arduino (Confirmação)
                SerialPort.Write("receberv1,");
                SerialPort.Write(send1);

                await Task.Delay(2000);

                SerialPort.Write("receberv2,");
                SerialPort.Write(send2);

                await Task.Delay(2000);

                SerialPort.Write("receberv3,");
                SerialPort.Write(send3);

                await Task.Delay(1500);

                //ativarMotor();

                // Adicionar um código que faça sumir a janela de carregamento
            }
            catch
            {
                // Adicionar um código que faça sumir a janela de carregamento

                DialogResult res = MessageBox.Show("Tem erro aê meu parsero...", "Ih rapaz...", MessageBoxButtons.OK, MessageBoxIcon.Error);
                
            }
        }

        private async void numericVelocidade_ValueChanged(object sender, EventArgs e)
        {
            
            try
            {
                string velocidade = numericVelocidade.Value.ToString().PadLeft(3, '0');
                SerialPort.Write("velocidade_");
                SerialPort.Write(String.Format(velocidade,','));

                await Task.Delay(1500);
            }
            catch
            {
                DialogResult res = MessageBox.Show("Vc tem que tá conectado ao arduino amigão.....", "Assim não rola.....", MessageBoxButtons.OK, MessageBoxIcon.Error);            
            }
        }

        private void btnNaoClica_Click(object sender, EventArgs e)
        {
            //DialogResult res = MessageBox.Show("YOU HAVE CHURAS??", "ARE YOU SURE???", MessageBoxButtons.YesNo, MessageBoxIcon.Stop);

            //if (res == DialogResult.Yes)
           // {
                new Sobre().Show();
           // }
           // if (res == DialogResult.No)
           // {
           //     DialogResult LEL = MessageBox.Show("Fez bem, otário", "MEDROSÃO", MessageBoxButtons.OK, MessageBoxIcon.Warning);
           // }
        }

        private void txtBoxRRecebida_TextChanged(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void cBoxPeso1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        // Estou adicionando isso para poder deixar selecioado já em ohms
        private void Form1_Shown(object sender, EventArgs e)
        {
            cBoxPeso1.SelectedIndex = 0;
            cBoxPeso2.SelectedIndex = 0;
            cBoxPeso3.SelectedIndex = 0;
        }

        private void btnAuto_Click(object sender, EventArgs e)
        {
            txtBoxValor1.Text = "220";
            txtBoxValor2.Text = "1";
            txtBoxValor3.Text = "1.5";
            cBoxPeso1.SelectedIndex = 0;
            cBoxPeso2.SelectedIndex = 1;
            cBoxPeso3.SelectedIndex = 2;
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            RxString = SerialPort.ReadExisting();
            this.Invoke(new EventHandler(trataDadoRecebido));
        }

        private void trataDadoRecebido(object sender, EventArgs e)
        {
            txtBoxRRecebida.AppendText(RxString);

        }

    }
}