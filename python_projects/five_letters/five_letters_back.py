FILE_NAME = "dict.txt"
ENCODE = "CP1251"
BLANK = '\0'
N = 5

def on_entry_fitted_changed(entry, true_fit):
    text = entry.get_text()
    name = entry.get_name()
    if text:
        if name == "e_letter1":
            true_fit[0] = text[0]
        elif name == "e_letter2":
            true_fit[1] = text[0]
        elif name == "e_letter3":
            true_fit[2] = text[0]
        elif name == "e_letter4":
            true_fit[3] = text[0]
        elif name == "e_letter5":
            true_fit[4] = text[0]

def on_entry_out_of_pos_changed(entry, out_of_pos_fit):
    text = entry.get_text()
    name = entry.get_name()
    if text:
        if name == "e_letter_pos1":
            out_of_pos_fit[0] = text[0]
        elif name == "e_letter_pos2":
            out_of_pos_fit[1] = text[0]
        elif name == "e_letter_pos3":
            out_of_pos_fit[2] = text[0]
        elif name == "e_letter_pos4":
            out_of_pos_fit[3] = text[0]
        elif name == "e_letter_pos5":
            out_of_pos_fit[4] = text[0]

def on_entry_no_fit_changed(entry, not_fit):
    not_fit[0] = entry.get_text()   

def check_fit_letters(word, true_fit, flag_fit):
    for i in range(N):
        c = true_fit[i].upper()
        if c == BLANK or c == word[i]:
            continue
        else:
            flag_fit = 0
    return flag_fit

def check_pos_letters(word, out_of_pos_fit, flag_fit):
    for i in range(N):
        c = out_of_pos_fit[i].upper()
        if c != BLANK:
            if c in word and word.find(c) != i:
                continue
            else:
                flag_fit = 0
    return flag_fit

def check_no_letters(word, not_fit, flag_fit):
    for i in range(len(not_fit[0])):
        c = not_fit[0][i].upper()
        if c in word:
            flag_fit = 0
    return flag_fit

def check_word(word, true_fit, out_of_pos_fit, not_fit, fit_words):
    flag_fit = 1
    flag_find = 0
    flag_fit = check_fit_letters(word, true_fit, flag_fit)
    if flag_fit:
        flag_fit = check_pos_letters(word, out_of_pos_fit, flag_fit)
    if flag_fit:
        flag_fit = check_no_letters(word, not_fit, flag_fit)
    if flag_fit:
        fit_words.append(word)
        flag_find = 1
    return flag_find

def search_cycle(words, data):
    flag_find = 0
    true_fit = data["true"]
    out_of_pos_fit = data["out"]
    not_fit = data["not"]
    fit_words = data["list"]
    for word in words:
        if len(word) == 6: 
           word = word.upper() 
           if check_word(word, true_fit, out_of_pos_fit, not_fit, fit_words):
               flag_find = 1
    return flag_find
    

def on_search_clicked(button, result, data):
    data["list"].clear()
    flag_find = 0
    name = button.get_name()
    if name == "but_search":
        with open(FILE_NAME, "r", encoding=ENCODE) as inp:
            words = inp.readlines()
            flag_find = search_cycle(words, data)        
    text = ""
    fitted_words = data["list"]
    if flag_find and len(fitted_words) < 100 :
        text = "".join(fitted_words)
    elif flag_find:
        text = "".join([fitted_words[i] for i in range(100)])
        text += "и т.д\n"
    text_buffer = result.get_buffer()
    text_buffer.set_text("")
    text_buffer.set_text(text)
    