call clean_all.bat

cd .\IMB_PIC_RES(.dat)

call 1.clean.bat

call 2.run.py

call 3.copy_to_inputfile.bat

cd ..

call 1.run.py

call 2.copy_to_sdk.bat

pause