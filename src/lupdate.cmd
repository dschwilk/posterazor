for %%i in (*.ts) do lupdate.exe -no-obsolete controller.cpp mainwindow.cpp -ts %%i