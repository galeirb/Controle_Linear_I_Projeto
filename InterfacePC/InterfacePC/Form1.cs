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
        string RxString; 

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
                if (txtBoxValor1.Text != "")
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
                }

                /*
                if (txtBoxValor2.Text != "")
                {
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
                }
                */

                /*
                if (txtBoxValor3.Text != "")
                {
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
                }*/


            }
            catch
            {
                DialogResult res = MessageBox.Show("É necessário revisar os dados colocados" + "\n" + "Obs.: Verifique se no lugar do ponto foi colocado uma vírgula", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        /* 
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
        */

        private void btnConectar_Click_1(object sender, EventArgs e)
        {
            if (SerialPort.IsOpen == false)
            {
                try
                {
                    SerialPort.PortName = cBoxCOMs.Items[cBoxCOMs.SelectedIndex].ToString();
                    SerialPort.Open();
                    txtBoxSerialRx.Text = "Arduino Conectado!";
                    // Mandar instrução para aparecer no display que está conectado
                    SerialPort.Write("status_arduino,1");
                    btnLimpar.Enabled = true; // Habilita o botão de limpar

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
            radioButton1.Enabled = true;
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
            SerialPort.Write("status_arduino,0");
            btnConectar.Enabled = true;
            btnDesconectar.Enabled = false;
            btnLimpar.Enabled = false; // Desabilita o botão de limpar
            btnLeituraRapida.Enabled = false; // Botão de leitura rápida
            radioButton2.Checked = true; // Deixa apenas selecionado o OFF
            radioButton1.Enabled = false; // Mantém o botão desativado
            cBoxCOMs.Enabled = true;
            txtBoxSerialRx.Text = "Arduino Desconectado!";



            SerialPort.Close();
        }

        private void btnLimpar_Click(object sender, EventArgs e)
        {

            SerialPort.Write("status_arduino,0"); // Avisa que o arduino foi desconectado
            btnLimpar.Enabled = false; // Desabilita o botão de limpar
            txtBoxValor1.Text = "";
            //txtBoxValor2.Text = "";
            //txtBoxValor3.Text = "";
            cBoxCOMs.SelectedIndex = -1;
            cBoxPeso1.SelectedIndex = 0;
            //cBoxPeso2.SelectedIndex = 0;
            //cBoxPeso3.SelectedIndex = 0;
            txtBoxRRecebida.Text = "";
            txtBoxSerialRx.Text = "";
            btnDesconectar.Enabled = false;
            btnLeituraRapida.Enabled = false;
            radioButton1.Enabled = false; // Mantém o botão desativado
            cBoxCOMs.Enabled = true;
            btnConectar.Enabled = true;
            txtBoxSerialRx.Text = "Arduino Desconectado!";
            

            // Mandar uma instrução para limpar a tela LCD
            SerialPort.Close();
            
            radioButton2.Checked = true; // Deixa marcado o botão de off da leitura externa

        }

        private async void btnIniciar_Click(object sender, EventArgs e)
        {
            try
            {
                //new Working().Show(); //Melhorá a tela de carregamento
     
                calculaValores(); // Pega os dados inseridos e coloca-se os pesos


                string send1 = String.Format(Convert.ToString(valor1)); // Manda o valor 1
                //string send2 = String.Format(Convert.ToString(valor2)); // Manda o valor 2
               // string send3 = String.Format(Convert.ToString(valor3)); // Manda o valor 3
                               

                // Valores recebidos do Arduino (Confirmação)
                SerialPort.Write("receberv1,");
                SerialPort.Write(send1);


                await Task.Delay(2000);

                //SerialPort.Write("receberv2,");
                //SerialPort.Write(send2);

                //await Task.Delay(2000);

                // SerialPort.Write("receberv3,");
                //SerialPort.Write(send3);

                // await Task.Delay(1500);

                txtBoxSerialRx.Text = "Valor enviado para o Arduino!";

                //ativarMotor();

                // Adicionar um código que faça sumir a janela de carregamento
            }
            catch
            {
                // Adicionar um código que faça sumir a janela de carregamento

                DialogResult res = MessageBox.Show("Verifique se o Arduino está conectado e as resistências foram inseridas.", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /*
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
        */


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
            //cBoxPeso2.SelectedIndex = 0;
            //cBoxPeso3.SelectedIndex = 0;
            txtBoxSerialRx.Text = "Bem vindo! Conecte ao arduiuno!";

            


        }

        private void groupBoxControleMotor_Enter(object sender, EventArgs e)
        {

        }

        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void txtBoxSerialRx_TextChanged(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
                   if (this.radioButton1.Checked == true)
            {
                SerialPort.Write("leitura,2"); // 2- Para ser mostrado tbm no display que está habilitado
                txtBoxValor1.Text = "";
                //txtBoxValor2.Text = "";
                //txtBoxValor3.Text = "";
                //cBoxCOMs.SelectedIndex = -1;
                cBoxPeso1.SelectedIndex = 0;
                //cBoxPeso2.SelectedIndex = 0;
                //cBoxPeso3.SelectedIndex = 0;
                txtBoxRRecebida.Text = ""; // Resistências lidas
                txtBoxSerialRx.Text = "Habilitado a opção de leitura externa!";

                btnLeituraRapida.Enabled = true;
            }


            if (SerialPort.IsOpen == true)
            {

            }


        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void cBoxPeso2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void txtBoxValor1_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnAuto_Click(object sender, EventArgs e)
        {
            txtBoxValor1.Text = "220";
            //txtBoxValor2.Text = "1";
            //txtBoxValor3.Text = "1.5";
            cBoxPeso1.SelectedIndex = 0;
            //cBoxPeso2.SelectedIndex = 1;
            //cBoxPeso3.SelectedIndex = 2;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SerialPort.Write("leitura,1"); // 1- DESEJAMOS SABER O VALOR LIDO


        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton2.Checked == true & this.btnLimpar.Enabled == true)
            {
                //txtBoxRRecebida.Text = ""; // Resistências lidas
                txtBoxSerialRx.Text = "Desabilitado a opção de leitura externa!";
                btnLeituraRapida.Enabled = false;

                SerialPort.Write("leitura,0"); //Cancelos a leitura rápida
            }
            
            

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //SerialPort.Write("status_arduino,2");
            SerialPort.Close();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void cBoxCOMs_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        { //Quando temos alguma coisa na porta Serial, chamamos "trataDadoRecebido" 
            RxString = SerialPort.ReadExisting();
            this.Invoke(new EventHandler(trataDadoRecebido));
        }

        private void trataDadoRecebido(object sender, EventArgs e)
        {
            txtBoxRRecebida.AppendText(RxString); // Mostra todos os dados recebidos pelo arduino

        }

    }
}