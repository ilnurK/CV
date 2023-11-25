from os import system
import sys

target = "cat"
is_have_error = 0
input_file = f"{target}.txt"
out_control = f"control_test_{target}.txt"
out_test = f"s21_{target}_test.txt"
test = f"../{target}/s21_{target}"
valgrind = f"valgrind --tool=memcheck --leak-check=yes --track-origins=yes -q"

def leaks(common):
    system(f"{valgrind} {test} {common[:-1]} > {out_test}")
    print("tested")

def tests(input_file):
    with open(input_file) as inp:
        list_inp = inp.readlines()
    for common in list_inp:
        if len(sys.argv) > 1 and sys.argv[1] == "val":
            leaks(common)
        else:
            system(f"{target} {common[:-1]} > {out_control}")
            system(f"{test} {common[:-1]} > {out_test}")
            with open(out_control, "r") as f_control, open(out_test, "r") as f_test:
                list_control = f_control.readlines()
                list_test = f_test.readlines()
            len_file = len(list_control)
            flag_err = 0 if len_file == len(list_test) else 1
            i = 0
            while flag_err == 0 and i < len_file:
                if list_control[i] != list_test[i]:
                    global is_have_error
                    is_have_error += 1
                    flag_err = 1
                else:
                    i += 1
            print(common)
            print(f"TEST FAILED at {i} iteration") if flag_err > 0 else print("OK")
            print(" ")


print()
print("*" * 30)

tests(input_file)

print("*" * 30)
print("All tests OK") if is_have_error == 0 else print(f"Find {is_have_error} problem")




