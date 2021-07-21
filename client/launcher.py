import os
from tkinter import Tk, Entry, Label, Button

root = Tk()
root.title("Bears versus Babies Launcher version Beta 1.1")

width = Entry(root, width=30)
code = Entry(root, width=30)
tps = Entry(root, width=30)

width.grid(row=1, column=1)
code.grid(row=0, column=1)
tps.grid(row=2, column=1)

Label(root, text="Width:").grid(row=1, column=0)
Label(root, text="Code:").grid(row=0, column=0)
Label(root, text="TPS:").grid(row=2, column=0)

def launch():
    os.system(f"game.exe --tps={tps.get()} --width={width.get()} {code.get()}")
    exit()

Button(root, text="Launch", command=launch).grid(row=3, column=0)

width.insert(0, "1920")
tps.insert(0, "10")

root.mainloop()
