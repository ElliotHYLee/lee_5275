<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.SerialComTab = New System.Windows.Forms.TabControl()
        Me.MuanualCom = New System.Windows.Forms.TabPage()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.txtMessage = New System.Windows.Forms.TextBox()
        Me.cmdSend = New System.Windows.Forms.Button()
        Me.FileCom = New System.Windows.Forms.TabPage()
        Me.cmdAbort = New System.Windows.Forms.Button()
        Me.cmdOpen = New System.Windows.Forms.Button()
        Me.cmdFileSend = New System.Windows.Forms.Button()
        Me.cmdBrowse = New System.Windows.Forms.Button()
        Me.txtFilePath = New System.Windows.Forms.TextBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.comboPorts = New System.Windows.Forms.ComboBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.comboBaud = New System.Windows.Forms.ComboBox()
        Me.cmdConnect = New System.Windows.Forms.Button()
        Me.cmdDisconnect = New System.Windows.Forms.Button()
        Me.lblConnection = New System.Windows.Forms.Label()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.cmdClear = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.txtProgress = New System.Windows.Forms.TextBox()
        Me.lblTotalLine = New System.Windows.Forms.Label()
        Me.lblCurrent = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ExitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SerialComTab.SuspendLayout
        Me.MuanualCom.SuspendLayout
        Me.FileCom.SuspendLayout
        Me.MenuStrip1.SuspendLayout
        Me.SuspendLayout
        '
        'SerialPort1
        '
        '
        'SerialComTab
        '
        Me.SerialComTab.Controls.Add(Me.MuanualCom)
        Me.SerialComTab.Controls.Add(Me.FileCom)
        Me.SerialComTab.Location = New System.Drawing.Point(35, 116)
        Me.SerialComTab.Name = "SerialComTab"
        Me.SerialComTab.SelectedIndex = 0
        Me.SerialComTab.Size = New System.Drawing.Size(741, 151)
        Me.SerialComTab.TabIndex = 1
        '
        'MuanualCom
        '
        Me.MuanualCom.Controls.Add(Me.Label3)
        Me.MuanualCom.Controls.Add(Me.txtMessage)
        Me.MuanualCom.Controls.Add(Me.cmdSend)
        Me.MuanualCom.Location = New System.Drawing.Point(4, 22)
        Me.MuanualCom.Name = "MuanualCom"
        Me.MuanualCom.Padding = New System.Windows.Forms.Padding(3)
        Me.MuanualCom.Size = New System.Drawing.Size(733, 125)
        Me.MuanualCom.TabIndex = 0
        Me.MuanualCom.Text = "Manual Sending"
        Me.MuanualCom.UseVisualStyleBackColor = true
        '
        'Label3
        '
        Me.Label3.AutoSize = true
        Me.Label3.Location = New System.Drawing.Point(36, 33)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(106, 13)
        Me.Label3.TabIndex = 3
        Me.Label3.Text = "Type Serial Message"
        '
        'txtMessage
        '
        Me.txtMessage.Location = New System.Drawing.Point(39, 49)
        Me.txtMessage.Name = "txtMessage"
        Me.txtMessage.Size = New System.Drawing.Size(535, 20)
        Me.txtMessage.TabIndex = 1
        '
        'cmdSend
        '
        Me.cmdSend.Location = New System.Drawing.Point(628, 49)
        Me.cmdSend.Name = "cmdSend"
        Me.cmdSend.Size = New System.Drawing.Size(75, 23)
        Me.cmdSend.TabIndex = 0
        Me.cmdSend.Text = "Send"
        Me.cmdSend.UseVisualStyleBackColor = true
        '
        'FileCom
        '
        Me.FileCom.Controls.Add(Me.cmdAbort)
        Me.FileCom.Controls.Add(Me.cmdOpen)
        Me.FileCom.Controls.Add(Me.cmdFileSend)
        Me.FileCom.Controls.Add(Me.cmdBrowse)
        Me.FileCom.Controls.Add(Me.txtFilePath)
        Me.FileCom.Controls.Add(Me.Label5)
        Me.FileCom.Location = New System.Drawing.Point(4, 22)
        Me.FileCom.Name = "FileCom"
        Me.FileCom.Padding = New System.Windows.Forms.Padding(3)
        Me.FileCom.Size = New System.Drawing.Size(733, 125)
        Me.FileCom.TabIndex = 1
        Me.FileCom.Text = "File Sending"
        Me.FileCom.UseVisualStyleBackColor = true
        '
        'cmdAbort
        '
        Me.cmdAbort.Location = New System.Drawing.Point(284, 64)
        Me.cmdAbort.Name = "cmdAbort"
        Me.cmdAbort.Size = New System.Drawing.Size(114, 33)
        Me.cmdAbort.TabIndex = 18
        Me.cmdAbort.Text = "StopSending"
        Me.cmdAbort.UseVisualStyleBackColor = true
        '
        'cmdOpen
        '
        Me.cmdOpen.Enabled = false
        Me.cmdOpen.Location = New System.Drawing.Point(20, 64)
        Me.cmdOpen.Name = "cmdOpen"
        Me.cmdOpen.Size = New System.Drawing.Size(108, 33)
        Me.cmdOpen.TabIndex = 14
        Me.cmdOpen.Text = "Open File"
        Me.cmdOpen.UseVisualStyleBackColor = true
        '
        'cmdFileSend
        '
        Me.cmdFileSend.Location = New System.Drawing.Point(150, 64)
        Me.cmdFileSend.Name = "cmdFileSend"
        Me.cmdFileSend.Size = New System.Drawing.Size(114, 33)
        Me.cmdFileSend.TabIndex = 12
        Me.cmdFileSend.Text = "Send"
        Me.cmdFileSend.UseVisualStyleBackColor = true
        '
        'cmdBrowse
        '
        Me.cmdBrowse.Location = New System.Drawing.Point(628, 16)
        Me.cmdBrowse.Name = "cmdBrowse"
        Me.cmdBrowse.Size = New System.Drawing.Size(75, 23)
        Me.cmdBrowse.TabIndex = 11
        Me.cmdBrowse.Text = "Browse"
        Me.cmdBrowse.UseVisualStyleBackColor = true
        '
        'txtFilePath
        '
        Me.txtFilePath.Enabled = false
        Me.txtFilePath.Location = New System.Drawing.Point(71, 18)
        Me.txtFilePath.Name = "txtFilePath"
        Me.txtFilePath.Size = New System.Drawing.Size(534, 20)
        Me.txtFilePath.TabIndex = 10
        '
        'Label5
        '
        Me.Label5.AutoSize = true
        Me.Label5.Location = New System.Drawing.Point(17, 18)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(48, 13)
        Me.Label5.TabIndex = 9
        Me.Label5.Text = "File Path"
        '
        'comboPorts
        '
        Me.comboPorts.FormattingEnabled = true
        Me.comboPorts.Location = New System.Drawing.Point(106, 36)
        Me.comboPorts.Name = "comboPorts"
        Me.comboPorts.Size = New System.Drawing.Size(132, 21)
        Me.comboPorts.TabIndex = 2
        '
        'Label1
        '
        Me.Label1.AutoSize = true
        Me.Label1.Location = New System.Drawing.Point(34, 44)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(55, 13)
        Me.Label1.TabIndex = 3
        Me.Label1.Text = "Serial Port"
        '
        'Label2
        '
        Me.Label2.AutoSize = true
        Me.Label2.Location = New System.Drawing.Point(36, 75)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(58, 13)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "Buad Rate"
        '
        'comboBaud
        '
        Me.comboBaud.FormattingEnabled = true
        Me.comboBaud.Items.AddRange(New Object() {"9600", "115200"})
        Me.comboBaud.Location = New System.Drawing.Point(106, 75)
        Me.comboBaud.Name = "comboBaud"
        Me.comboBaud.Size = New System.Drawing.Size(132, 21)
        Me.comboBaud.TabIndex = 4
        '
        'cmdConnect
        '
        Me.cmdConnect.Location = New System.Drawing.Point(260, 34)
        Me.cmdConnect.Name = "cmdConnect"
        Me.cmdConnect.Size = New System.Drawing.Size(75, 23)
        Me.cmdConnect.TabIndex = 6
        Me.cmdConnect.Text = "Connect"
        Me.cmdConnect.UseVisualStyleBackColor = true
        '
        'cmdDisconnect
        '
        Me.cmdDisconnect.Location = New System.Drawing.Point(260, 70)
        Me.cmdDisconnect.Name = "cmdDisconnect"
        Me.cmdDisconnect.Size = New System.Drawing.Size(75, 23)
        Me.cmdDisconnect.TabIndex = 7
        Me.cmdDisconnect.Text = "Disconnect"
        Me.cmdDisconnect.UseVisualStyleBackColor = true
        '
        'lblConnection
        '
        Me.lblConnection.AutoSize = true
        Me.lblConnection.Location = New System.Drawing.Point(370, 39)
        Me.lblConnection.Name = "lblConnection"
        Me.lblConnection.Size = New System.Drawing.Size(73, 13)
        Me.lblConnection.TabIndex = 8
        Me.lblConnection.Text = "Disconnected"
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'cmdClear
        '
        Me.cmdClear.Location = New System.Drawing.Point(420, 302)
        Me.cmdClear.Name = "cmdClear"
        Me.cmdClear.Size = New System.Drawing.Size(75, 23)
        Me.cmdClear.TabIndex = 11
        Me.cmdClear.Text = "Clear"
        Me.cmdClear.UseVisualStyleBackColor = true
        '
        'Label4
        '
        Me.Label4.AutoSize = true
        Me.Label4.Location = New System.Drawing.Point(40, 286)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(104, 13)
        Me.Label4.TabIndex = 10
        Me.Label4.Text = "Received Messages"
        '
        'RichTextBox1
        '
        Me.RichTextBox1.Location = New System.Drawing.Point(35, 304)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.Size = New System.Drawing.Size(364, 221)
        Me.RichTextBox1.TabIndex = 9
        Me.RichTextBox1.Text = ""
        '
        'txtProgress
        '
        Me.txtProgress.Location = New System.Drawing.Point(562, 305)
        Me.txtProgress.Name = "txtProgress"
        Me.txtProgress.Size = New System.Drawing.Size(57, 20)
        Me.txtProgress.TabIndex = 12
        '
        'lblTotalLine
        '
        Me.lblTotalLine.AutoSize = true
        Me.lblTotalLine.Location = New System.Drawing.Point(607, 337)
        Me.lblTotalLine.Name = "lblTotalLine"
        Me.lblTotalLine.Size = New System.Drawing.Size(0, 13)
        Me.lblTotalLine.TabIndex = 13
        '
        'lblCurrent
        '
        Me.lblCurrent.AutoSize = true
        Me.lblCurrent.Location = New System.Drawing.Point(559, 337)
        Me.lblCurrent.Name = "lblCurrent"
        Me.lblCurrent.Size = New System.Drawing.Size(13, 13)
        Me.lblCurrent.TabIndex = 14
        Me.lblCurrent.Text = "0"
        '
        'Label7
        '
        Me.Label7.AutoSize = true
        Me.Label7.Location = New System.Drawing.Point(589, 337)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(12, 13)
        Me.Label7.TabIndex = 15
        Me.Label7.Text = "/"
        '
        'Label8
        '
        Me.Label8.AutoSize = true
        Me.Label8.Location = New System.Drawing.Point(625, 307)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(61, 13)
        Me.Label8.TabIndex = 16
        Me.Label8.Text = "% complete"
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(794, 24)
        Me.MenuStrip1.TabIndex = 17
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ExitToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(37, 20)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'ExitToolStripMenuItem
        '
        Me.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem"
        Me.ExitToolStripMenuItem.Size = New System.Drawing.Size(92, 22)
        Me.ExitToolStripMenuItem.Text = "Exit"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 13!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(794, 542)
        Me.Controls.Add(Me.Label8)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.lblCurrent)
        Me.Controls.Add(Me.lblTotalLine)
        Me.Controls.Add(Me.txtProgress)
        Me.Controls.Add(Me.cmdClear)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.RichTextBox1)
        Me.Controls.Add(Me.lblConnection)
        Me.Controls.Add(Me.cmdDisconnect)
        Me.Controls.Add(Me.cmdConnect)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.comboBaud)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.comboPorts)
        Me.Controls.Add(Me.SerialComTab)
        Me.Controls.Add(Me.MenuStrip1)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "Form1"
        Me.Text = "SerialCommunication"
        Me.SerialComTab.ResumeLayout(false)
        Me.MuanualCom.ResumeLayout(false)
        Me.MuanualCom.PerformLayout
        Me.FileCom.ResumeLayout(false)
        Me.FileCom.PerformLayout
        Me.MenuStrip1.ResumeLayout(false)
        Me.MenuStrip1.PerformLayout
        Me.ResumeLayout(false)
        Me.PerformLayout

End Sub
    Friend WithEvents SerialPort1 As System.IO.Ports.SerialPort
    Friend WithEvents SerialComTab As System.Windows.Forms.TabControl
    Friend WithEvents MuanualCom As System.Windows.Forms.TabPage
    Friend WithEvents FileCom As System.Windows.Forms.TabPage
    Friend WithEvents comboPorts As System.Windows.Forms.ComboBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents comboBaud As System.Windows.Forms.ComboBox
    Friend WithEvents cmdConnect As System.Windows.Forms.Button
    Friend WithEvents cmdDisconnect As System.Windows.Forms.Button
    Friend WithEvents lblConnection As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtMessage As System.Windows.Forms.TextBox
    Friend WithEvents cmdSend As System.Windows.Forms.Button
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents cmdFileSend As System.Windows.Forms.Button
    Friend WithEvents cmdBrowse As System.Windows.Forms.Button
    Friend WithEvents txtFilePath As System.Windows.Forms.TextBox
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents cmdOpen As System.Windows.Forms.Button
    Friend WithEvents cmdClear As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents RichTextBox1 As System.Windows.Forms.RichTextBox
    Friend WithEvents txtProgress As System.Windows.Forms.TextBox
    Friend WithEvents lblTotalLine As System.Windows.Forms.Label
    Friend WithEvents lblCurrent As System.Windows.Forms.Label
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents FileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ExitToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents cmdAbort As System.Windows.Forms.Button

End Class
