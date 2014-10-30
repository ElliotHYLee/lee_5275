Imports System
Imports System.Threading
Imports System.IO.Ports
Imports System.ComponentModel
Imports System.IO



Public Class Form1
    Dim myPort As Array
    Dim fileNum As Integer = FreeFile()
    Dim fileName As String
    Delegate Sub SetTextCallback(ByVal [text] As String) 'Added to prevent threading errors during receiveing of data
    Delegate Sub threadTest(ByRef index As Integer, ByRef element As String)
    Delegate Sub progess(ByRef current As Double, ByRef total As Double)
    Private myThread As System.Threading.Thread
    Dim line As String
    Dim element(24) As String
    Dim rawElement() As String
    Dim rawIndex As Integer
    Dim index As Integer
    Public totalLine As Double
    Public currentLine As Double

    Private Sub cmdBrowse_Click(sender As System.Object, e As System.EventArgs) Handles cmdBrowse.Click

        OpenFileDialog1.ShowDialog()
        ' get file name
        fileName = OpenFileDialog1.FileName
        ' print file name
        txtFilePath.Text = fileName
        cmdOpen.Enabled = True
        totalLine = 0
        Dim readLine As New System.IO.StreamReader(fileName)
        Do Until readLine.EndOfStream
            totalLine = totalLine + 1
            readLine.ReadLine()
        Loop

        lblTotalLine.Text = (totalLine)
        lblCurrent.Text = 0
        txtProgress.Text = 0


    End Sub
    Private Sub Form_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        Dim response As MsgBoxResult

        If cmdAbort.Enabled = True Then
            MsgBox("Stop sending messages first")
            e.Cancel = True
            Exit Sub
        Else

            response = MsgBox("Do you want to close?", MsgBoxStyle.Question + MsgBoxStyle.YesNo, "Confirm")
            If response = MsgBoxResult.Yes Then
                Me.Dispose()
            ElseIf response = MsgBoxResult.No Then
                e.Cancel = True
                Exit Sub
            End If
        End If


    End Sub
    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load

        myPort = IO.Ports.SerialPort.GetPortNames()
        comboPorts.Items.AddRange(myPort)
        cmdDisconnect.Enabled = False
        cmdSend.Enabled = False
        cmdFileSend.Enabled = False
        cmdAbort.Enabled = False

    End Sub
    Private Sub updateText(ByRef index As Integer, ByRef element As String)
        If Me.InvokeRequired Then
            Dim x As New threadTest(AddressOf updateText)
            Me.Invoke(x, New Object() {(index), (element)})
        Else

            'MsgBox([text])

            Me.RichTextBox1.AppendText(index & "th Element: " & element & vbCrLf)
            Me.RichTextBox1.ScrollToCaret()
        End If



    End Sub
    Private Sub showProgress(ByRef current As Double, ByRef total As Double)
        Dim progress As Double
        If Me.InvokeRequired Then
            Dim x As New progess(AddressOf showProgress)
            Me.Invoke(x, New Object() {(current), (total)})
            'Me.Invoke(x, New Object() {})
        Else
            progress = current / total * 100
            If Me.txtProgress.Text <> progress.ToString Then
                Me.txtProgress.Text = progress.ToString
                Me.lblCurrent.Text = current

                'MsgBox("updated")
            End If

        End If


        'End While
    End Sub


    Private Sub cmdConnect_Click(sender As System.Object, e As System.EventArgs) Handles cmdConnect.Click
        SerialPort1.PortName = comboPorts.Text
        SerialPort1.BaudRate = comboBaud.Text
        SerialPort1.Open()
        cmdConnect.Enabled = False
        cmdDisconnect.Enabled = True
        cmdSend.Enabled = True
        cmdFileSend.Enabled = True
        lblConnection.Text = "USB Connected"

    End Sub

    Private Sub cmdDisconnect_Click(sender As System.Object, e As System.EventArgs) Handles cmdDisconnect.Click
        SerialPort1.Close()
        cmdConnect.Enabled = True
        cmdDisconnect.Enabled = False
        cmdSend.Enabled = False
        cmdFileSend.Enabled = False
        lblConnection.Text = "Disconnected"
    End Sub

    Private Sub cmdSend_Click(sender As System.Object, e As System.EventArgs) Handles cmdSend.Click
        SerialPort1.Write(txtMessage.Text & " ") 'concatenate with '_'
    End Sub

    Private Sub SerialPort1_DataReceived(sender As System.Object, e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        ReceivedText(SerialPort1.ReadExisting())
    End Sub

    Private Sub ReceivedText(ByVal [text] As String) 'input from ReadExisting
        If Me.RichTextBox1.InvokeRequired Then
            Dim x As New SetTextCallback(AddressOf ReceivedText)
            Me.Invoke(x, New Object() {(text)})
        Else

            'MsgBox([text])
            
            Me.RichTextBox1.AppendText([text])
            Me.RichTextBox1.ScrollToCaret()
        End If


    End Sub


    Private Sub cmdClear_Click(sender As System.Object, e As System.EventArgs)
        RichTextBox1.Text = ""
    End Sub

    Private Sub cmdOpen_Click(sender As System.Object, e As System.EventArgs) Handles cmdOpen.Click
        Process.Start("notepad", txtFilePath.Text)
    End Sub


    Private Sub cmdFileSend_Click(sender As System.Object, e As System.EventArgs) Handles cmdFileSend.Click
        If fileName = "" Then
            MsgBox("Browse a file")
            Exit Sub
        End If

        myThread = New System.Threading.Thread(AddressOf whatever)
        myThread.Start()
        cmdAbort.Enabled = True


        
    End Sub

    Private Sub whatever()
        ' open file
        Dim reader As New System.IO.StreamReader(fileName)
        'myThread = New System.Threading.Thread(AddressOf Module1.showProgress)
        'myThread.Start()
        currentLine = 0
        ' read file
        Do Until reader.EndOfStream


            line = reader.ReadLine
            Me.currentLine = Me.currentLine + 1
            showProgress(Me.currentLine, Me.totalLine)
            Me.rawElement = line.Split("   ")
            Me.rawIndex = 0
            Me.index = 0
            For Me.rawIndex = 0 To Me.rawElement.Length - 1
                'RichTextBox2.Text &= rawIndex & "th rawElement: " & rawElement(rawIndex) & vbCrLf
                If Me.rawElement(rawIndex) <> "" Then
                    Me.element(index) = Me.rawElement(rawIndex)
                    Me.index = Me.index + 1
                End If

            Next
            Me.rawIndex = 0

            For Me.index = 0 To Me.element.Length - 1
                'RichTextBox2.AppendText(index & "th Element: " & element(index) & vbCrLf)
                'RichTextBox2.ScrollToCaret()
                SerialPort1.Write(element(index) & " ") 'concatenate with \n
                'MsgBox("sent")
                'updateText(index, element(index))

            Next
        Loop


        FileClose(fileNum)
    End Sub

  


    Private Sub cmdClear_Click_1(sender As System.Object, e As System.EventArgs) Handles cmdClear.Click
        RichTextBox1.Text = ""
    End Sub


    Private Sub ExitToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ExitToolStripMenuItem.Click
        Dim response As MsgBoxResult

        If cmdAbort.Enabled = True Then
            MsgBox("Stop sending messages first")
            Exit Sub
        Else

            response = MsgBox("Do you want to close?", MsgBoxStyle.Question + MsgBoxStyle.YesNo, "Confirm")
            If response = MsgBoxResult.Yes Then
                Me.Dispose()
            ElseIf response = MsgBoxResult.No Then
                Exit Sub
            End If
        End If



    End Sub

    Private Sub cmdAbort_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdAbort.Click
        myThread.Abort()
        cmdFileSend.Enabled = True
        cmdAbort.Enabled = False


    End Sub

  
End Class
