import ctypes as ct
from tkinter import *
from tkinter import messagebox

def make_new_arr():
    str_arr = Entry_input.get().split()
    arr = [int(num) for num in str_arr]
    arr_size = len(arr)
    if arr_size < 1:
        messagebox.showinfo("ERROR", "Invalid size")
        return

    lib = ct.CDLL("libfunc.dll")

    make_new_arr = lib.make_new_arr
    make_new_arr.argtypes = [ct.POINTER(ct.c_int),
                     ct.POINTER(ct.c_int),
                     ct.c_int, ct.c_int]
    make_new_arr.restype = ct.c_int
    arr = (ct.c_int * arr_size)(*arr)
    set_size = 0
    arr_set = (ct.c_int * set_size)()
    set_size = make_new_arr(arr, arr_set, arr_size, set_size)
    arr_set = (ct.c_int * set_size)(*arr_set)
    make_new_arr(arr, arr_set, arr_size, set_size)

    str_arr = ""
    for num in arr_set:
        str_arr += str(num)
        str_arr += ' '

    Entey_set_result.delete(0, END)
    Entey_set_result.insert(END, str_arr)


def fill_fibonacci_arr(arr_size):
    lib = ct.CDLL("libfunc.dll")

    fibonacci_arr = lib.fibonacci_arr
    fibonacci_arr.argtypes = [ct.POINTER(ct.c_int),
                     ct.c_int]
    fibonacci_arr.restype = None

    result = (ct.c_int * arr_size)()
    fibonacci_arr(result, arr_size)

    return list(result)


def create_fibonacci_arr():
    if Entry_input_size.get() == '':
        messagebox.showinfo("ERROR", "Input size")
        return
    arr_size = int(Entry_input_size.get())

    if arr_size < 1:    
        messagebox.showinfo("ERROR", "Invalid size")
        return
    
    arr = fill_fibonacci_arr(arr_size)
    str_arr = ""
    for num in arr:
        str_arr += str(num) + ' '
    
    Entey_fib_result.delete(0, END)
    Entey_fib_result.insert(END, str_arr)

window = Tk()
window.title("LAB_12_02_02")
window.config(bg = "lightgreen")
window.geometry("500x650")

Label_fib =  Label(window, text = "Fibonacci numbers",
                    font = "Helvetica", bg = "lightgreen")
Label_fib.place(x = 200, y = 10)
Label_input_size =  Label(window, text = "Input size:",
                    font = "Helvetica", bg = "lightgreen")
Entry_input_size = Entry(window, width = 40,
                         font = "Helvetica")
Label_input_size.place(x = 60, y = 60)
Entry_input_size.place(x = 60, y = 100)

Button_fib_solve = Button(window, text = "Run",
                    command = lambda: create_fibonacci_arr())
Button_fib_solve.place(x = 200, y = 150)

Label_fib_arr =  Label(window, text = "Array of Fibonacci numbers:",
                    font = "Helvetica", bg = "lightgreen")
Entey_fib_result = Entry(window, font = "Helvetica", width = 40)
Label_fib_arr.place(x = 60, y = 200)
Entey_fib_result.place(x = 60, y = 250)

Label_set =  Label(window, text = "Array", 
                  font = "Helvetica", bg = "lightgreen")
Label_set.place(x = 200, y = 300)
Label_input =  Label(window, text = "Input array:",
                    font = "Helvetica", bg = "lightgreen")
Entry_input = Entry(window, width = 40, font = "Helvetica")
Label_input.place(x = 60, y = 350)
Entry_input.place(x = 60, y = 400)

Button_set_solve = Button(window, text = "Run",
                    command = lambda: make_new_arr())
Button_set_solve.place(x = 200, y = 450)

Label_output =  Label(window, text = "New array:",
                    font = "Helvetica", bg = "lightgreen")
Entey_set_result = Entry(window, font = "Helvetica", width = 40)
Label_output.place(x = 60, y = 500)
Entey_set_result.place(x = 60, y = 550)

Button_quit = Button(window, text = "Quit", command=window.destroy)
Button_quit.place(x = 200, y = 600)

window.mainloop()