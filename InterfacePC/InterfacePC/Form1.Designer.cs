namespace InterfacePC
{
    partial class Form1
    {
        /// <summary>
        /// Variável de designer necessária.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpar os recursos que estão sendo usados.
        /// </summary>
        /// <param name="disposing">true se for necessário descartar os recursos gerenciados; caso contrário, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código gerado pelo Windows Form Designer

        /// <summary>
        /// Método necessário para suporte ao Designer - não modifique 
        /// o conteúdo deste método com o editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label4 = new System.Windows.Forms.Label();
            this.txtBoxSerialRx = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.rBtnAntiHorario = new System.Windows.Forms.RadioButton();
            this.rBtnHorario = new System.Windows.Forms.RadioButton();
            this.groupBoxControleMotor = new System.Windows.Forms.GroupBox();
            this.numericVelocidade = new System.Windows.Forms.NumericUpDown();
            this.SerialPort = new System.IO.Ports.SerialPort(this.components);
            this.timerCOM = new System.Windows.Forms.Timer(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.btnConectar = new System.Windows.Forms.Button();
            this.cBoxCOMs = new System.Windows.Forms.ComboBox();
            this.txtBoxRRecebida = new System.Windows.Forms.TextBox();
            this.cBoxPeso3 = new System.Windows.Forms.ComboBox();
            this.txtBoxValor3 = new System.Windows.Forms.TextBox();
            this.cBoxPeso2 = new System.Windows.Forms.ComboBox();
            this.txtBoxValor2 = new System.Windows.Forms.TextBox();
            this.cBoxPeso1 = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtBoxValor1 = new System.Windows.Forms.TextBox();
            this.btnIniciar = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnDesconectar = new System.Windows.Forms.Button();
            this.btnLimpar = new System.Windows.Forms.Button();
            this.btnAuto = new System.Windows.Forms.Button();
            this.btnNaoClica = new System.Windows.Forms.Button();
            this.groupBoxControleMotor.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericVelocidade)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(519, 251);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 13);
            this.label4.TabIndex = 22;
            this.label4.Text = "Monitor serial";
            // 
            // txtBoxSerialRx
            // 
            this.txtBoxSerialRx.Location = new System.Drawing.Point(322, 161);
            this.txtBoxSerialRx.Multiline = true;
            this.txtBoxSerialRx.Name = "txtBoxSerialRx";
            this.txtBoxSerialRx.ReadOnly = true;
            this.txtBoxSerialRx.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtBoxSerialRx.Size = new System.Drawing.Size(445, 85);
            this.txtBoxSerialRx.TabIndex = 20;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(87, 90);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Velocidade";
            // 
            // rBtnAntiHorario
            // 
            this.rBtnAntiHorario.AutoSize = true;
            this.rBtnAntiHorario.Location = new System.Drawing.Point(113, 30);
            this.rBtnAntiHorario.Name = "rBtnAntiHorario";
            this.rBtnAntiHorario.Size = new System.Drawing.Size(78, 17);
            this.rBtnAntiHorario.TabIndex = 2;
            this.rBtnAntiHorario.Text = "Anti-horário";
            this.rBtnAntiHorario.UseVisualStyleBackColor = true;
            // 
            // rBtnHorario
            // 
            this.rBtnHorario.AutoSize = true;
            this.rBtnHorario.Checked = true;
            this.rBtnHorario.Location = new System.Drawing.Point(48, 30);
            this.rBtnHorario.Name = "rBtnHorario";
            this.rBtnHorario.Size = new System.Drawing.Size(59, 17);
            this.rBtnHorario.TabIndex = 1;
            this.rBtnHorario.TabStop = true;
            this.rBtnHorario.Text = "Horário";
            this.rBtnHorario.UseVisualStyleBackColor = true;
            // 
            // groupBoxControleMotor
            // 
            this.groupBoxControleMotor.Controls.Add(this.numericVelocidade);
            this.groupBoxControleMotor.Controls.Add(this.label2);
            this.groupBoxControleMotor.Controls.Add(this.rBtnAntiHorario);
            this.groupBoxControleMotor.Controls.Add(this.rBtnHorario);
            this.groupBoxControleMotor.Location = new System.Drawing.Point(23, 161);
            this.groupBoxControleMotor.Name = "groupBoxControleMotor";
            this.groupBoxControleMotor.Size = new System.Drawing.Size(239, 119);
            this.groupBoxControleMotor.TabIndex = 19;
            this.groupBoxControleMotor.TabStop = false;
            this.groupBoxControleMotor.Text = "Controle do motor";
            // 
            // numericVelocidade
            // 
            this.numericVelocidade.Location = new System.Drawing.Point(95, 65);
            this.numericVelocidade.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericVelocidade.Name = "numericVelocidade";
            this.numericVelocidade.Size = new System.Drawing.Size(45, 20);
            this.numericVelocidade.TabIndex = 25;
            this.numericVelocidade.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericVelocidade.ValueChanged += new System.EventHandler(this.numericVelocidade_ValueChanged);
            // 
            // SerialPort
            // 
            this.SerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort_DataReceived);
            // 
            // timerCOM
            // 
            this.timerCOM.Enabled = true;
            this.timerCOM.Interval = 1000;
            this.timerCOM.Tick += new System.EventHandler(this.timerCOM_Tick);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(619, 131);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 13);
            this.label3.TabIndex = 21;
            this.label3.Text = "Resistências lidas";
            // 
            // btnConectar
            // 
            this.btnConectar.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnConectar.Location = new System.Drawing.Point(19, 46);
            this.btnConectar.Name = "btnConectar";
            this.btnConectar.Size = new System.Drawing.Size(75, 23);
            this.btnConectar.TabIndex = 18;
            this.btnConectar.Text = "Conectar...";
            this.btnConectar.UseVisualStyleBackColor = true;
            this.btnConectar.Click += new System.EventHandler(this.btnConectar_Click_1);
            // 
            // cBoxCOMs
            // 
            this.cBoxCOMs.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cBoxCOMs.FormattingEnabled = true;
            this.cBoxCOMs.Location = new System.Drawing.Point(63, 19);
            this.cBoxCOMs.Name = "cBoxCOMs";
            this.cBoxCOMs.Size = new System.Drawing.Size(75, 21);
            this.cBoxCOMs.TabIndex = 17;
            // 
            // txtBoxRRecebida
            // 
            this.txtBoxRRecebida.Location = new System.Drawing.Point(550, 31);
            this.txtBoxRRecebida.Multiline = true;
            this.txtBoxRRecebida.Name = "txtBoxRRecebida";
            this.txtBoxRRecebida.ReadOnly = true;
            this.txtBoxRRecebida.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtBoxRRecebida.Size = new System.Drawing.Size(228, 97);
            this.txtBoxRRecebida.TabIndex = 15;
            this.txtBoxRRecebida.TextChanged += new System.EventHandler(this.txtBoxRRecebida_TextChanged);
            // 
            // cBoxPeso3
            // 
            this.cBoxPeso3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cBoxPeso3.FormattingEnabled = true;
            this.cBoxPeso3.Items.AddRange(new object[] {
            "Ω",
            "kΩ",
            "MΩ"});
            this.cBoxPeso3.Location = new System.Drawing.Point(208, 71);
            this.cBoxPeso3.Name = "cBoxPeso3";
            this.cBoxPeso3.Size = new System.Drawing.Size(47, 21);
            this.cBoxPeso3.TabIndex = 8;
            // 
            // txtBoxValor3
            // 
            this.txtBoxValor3.Location = new System.Drawing.Point(154, 71);
            this.txtBoxValor3.MaxLength = 5;
            this.txtBoxValor3.Name = "txtBoxValor3";
            this.txtBoxValor3.Size = new System.Drawing.Size(48, 20);
            this.txtBoxValor3.TabIndex = 7;
            // 
            // cBoxPeso2
            // 
            this.cBoxPeso2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cBoxPeso2.FormattingEnabled = true;
            this.cBoxPeso2.Items.AddRange(new object[] {
            "Ω",
            "kΩ",
            "MΩ"});
            this.cBoxPeso2.Location = new System.Drawing.Point(208, 44);
            this.cBoxPeso2.Name = "cBoxPeso2";
            this.cBoxPeso2.Size = new System.Drawing.Size(47, 21);
            this.cBoxPeso2.TabIndex = 6;
            // 
            // txtBoxValor2
            // 
            this.txtBoxValor2.Location = new System.Drawing.Point(154, 44);
            this.txtBoxValor2.MaxLength = 5;
            this.txtBoxValor2.Name = "txtBoxValor2";
            this.txtBoxValor2.Size = new System.Drawing.Size(48, 20);
            this.txtBoxValor2.TabIndex = 5;
            // 
            // cBoxPeso1
            // 
            this.cBoxPeso1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cBoxPeso1.FormattingEnabled = true;
            this.cBoxPeso1.Items.AddRange(new object[] {
            "Ω",
            "kΩ",
            "MΩ"});
            this.cBoxPeso1.Location = new System.Drawing.Point(208, 17);
            this.cBoxPeso1.Name = "cBoxPeso1";
            this.cBoxPeso1.Size = new System.Drawing.Size(47, 21);
            this.cBoxPeso1.TabIndex = 4;
            this.cBoxPeso1.SelectedIndexChanged += new System.EventHandler(this.cBoxPeso1_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cBoxPeso3);
            this.groupBox1.Controls.Add(this.txtBoxValor3);
            this.groupBox1.Controls.Add(this.cBoxPeso2);
            this.groupBox1.Controls.Add(this.txtBoxValor2);
            this.groupBox1.Controls.Add(this.cBoxPeso1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtBoxValor1);
            this.groupBox1.Location = new System.Drawing.Point(23, 31);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(271, 108);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Seleção de resistores";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(121, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Resistências desejadas:";
            // 
            // txtBoxValor1
            // 
            this.txtBoxValor1.Location = new System.Drawing.Point(154, 17);
            this.txtBoxValor1.MaxLength = 5;
            this.txtBoxValor1.Name = "txtBoxValor1";
            this.txtBoxValor1.Size = new System.Drawing.Size(48, 20);
            this.txtBoxValor1.TabIndex = 0;
            // 
            // btnIniciar
            // 
            this.btnIniciar.Location = new System.Drawing.Point(322, 116);
            this.btnIniciar.Name = "btnIniciar";
            this.btnIniciar.Size = new System.Drawing.Size(100, 34);
            this.btnIniciar.TabIndex = 16;
            this.btnIniciar.Text = "Iniciar";
            this.btnIniciar.UseVisualStyleBackColor = true;
            this.btnIniciar.Click += new System.EventHandler(this.btnIniciar_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnDesconectar);
            this.groupBox2.Controls.Add(this.cBoxCOMs);
            this.groupBox2.Controls.Add(this.btnConectar);
            this.groupBox2.Location = new System.Drawing.Point(322, 27);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 83);
            this.groupBox2.TabIndex = 23;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Conexão com Arduino";
            this.groupBox2.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // btnDesconectar
            // 
            this.btnDesconectar.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnDesconectar.Enabled = false;
            this.btnDesconectar.Location = new System.Drawing.Point(100, 46);
            this.btnDesconectar.Name = "btnDesconectar";
            this.btnDesconectar.Size = new System.Drawing.Size(81, 23);
            this.btnDesconectar.TabIndex = 19;
            this.btnDesconectar.Text = "Desconectar";
            this.btnDesconectar.UseVisualStyleBackColor = true;
            this.btnDesconectar.Click += new System.EventHandler(this.btnDesconectar_Click);
            // 
            // btnLimpar
            // 
            this.btnLimpar.Location = new System.Drawing.Point(447, 122);
            this.btnLimpar.Name = "btnLimpar";
            this.btnLimpar.Size = new System.Drawing.Size(75, 23);
            this.btnLimpar.TabIndex = 24;
            this.btnLimpar.Text = "Limpar";
            this.btnLimpar.UseVisualStyleBackColor = true;
            this.btnLimpar.Click += new System.EventHandler(this.btnLimpar_Click);
            // 
            // btnAuto
            // 
            this.btnAuto.Location = new System.Drawing.Point(711, 265);
            this.btnAuto.Name = "btnAuto";
            this.btnAuto.Size = new System.Drawing.Size(75, 23);
            this.btnAuto.TabIndex = 25;
            this.btnAuto.Text = "Auto";
            this.btnAuto.UseVisualStyleBackColor = true;
            this.btnAuto.Click += new System.EventHandler(this.btnAuto_Click);
            // 
            // btnNaoClica
            // 
            this.btnNaoClica.BackColor = System.Drawing.Color.White;
            this.btnNaoClica.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnNaoClica.Location = new System.Drawing.Point(363, 251);
            this.btnNaoClica.Name = "btnNaoClica";
            this.btnNaoClica.Size = new System.Drawing.Size(97, 38);
            this.btnNaoClica.TabIndex = 20;
            this.btnNaoClica.Text = "Sobre";
            this.btnNaoClica.UseVisualStyleBackColor = false;
            this.btnNaoClica.Click += new System.EventHandler(this.btnNaoClica_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.BackgroundImage = global::InterfacePC.Properties.Resources._130938339377;
            this.ClientSize = new System.Drawing.Size(800, 291);
            this.Controls.Add(this.btnNaoClica);
            this.Controls.Add(this.btnAuto);
            this.Controls.Add(this.btnLimpar);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtBoxSerialRx);
            this.Controls.Add(this.groupBoxControleMotor);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtBoxRRecebida);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnIniciar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "UI de seleção";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.groupBoxControleMotor.ResumeLayout(false);
            this.groupBoxControleMotor.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericVelocidade)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtBoxSerialRx;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RadioButton rBtnAntiHorario;
        private System.Windows.Forms.RadioButton rBtnHorario;
        private System.Windows.Forms.GroupBox groupBoxControleMotor;
        private System.IO.Ports.SerialPort SerialPort;
        private System.Windows.Forms.Timer timerCOM;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnConectar;
        private System.Windows.Forms.ComboBox cBoxCOMs;
        private System.Windows.Forms.TextBox txtBoxRRecebida;
        private System.Windows.Forms.ComboBox cBoxPeso3;
        private System.Windows.Forms.TextBox txtBoxValor3;
        private System.Windows.Forms.ComboBox cBoxPeso2;
        private System.Windows.Forms.TextBox txtBoxValor2;
        private System.Windows.Forms.ComboBox cBoxPeso1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtBoxValor1;
        private System.Windows.Forms.Button btnIniciar;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnDesconectar;
        private System.Windows.Forms.Button btnLimpar;
        private System.Windows.Forms.NumericUpDown numericVelocidade;
        private System.Windows.Forms.Button btnAuto;
        private System.Windows.Forms.Button btnNaoClica;
    }
}

