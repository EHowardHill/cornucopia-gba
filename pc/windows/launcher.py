import subprocess
from tkinter import messagebox, Tk

root = Tk()
root.withdraw()

messagebox.showinfo(title="Message from Cinemint",
message="""
Ahoy!\n
This title is a Gameboy Advance ROM bundled with mGBA, an emulator for PC. By default, the buttons are mapped by default as:\n
Arrow Keys:   \tMovement
B Button:     \tZ Key
A Button:     \tX Key
Start:        \tEnter/Return
Left Trigger: \tA Key
Right Trigger:\tS Key\n
You can change these, as well as configure many other settings from Tools -> Settings\n
Thank you, and have fun!\n
- Ethan 'Cinemint' Hill""")

subprocess.run(["mGBA.exe", "corn.gba"])