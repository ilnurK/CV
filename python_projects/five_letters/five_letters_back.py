FILE_NAME = "dict.txt"
ENCODE = "CP1251"
ENTRY_FIT = "entry_fit"
ENTRY_OUT = "entry_out"
ENTRY_NOT = "entry_not"
BUT_SEARCH = "but_search"
FIT_LIST = "fit_words"
BLANK = "\0"
N = 5


def check_fit_letters(word, true_fit, flag_fit):
    for i in range(N):
        c = true_fit[i].upper()
        if c != BLANK and c != word[i]:
            flag_fit = 0
    return flag_fit


def check_pos_letters(word, out_of_pos_fit, flag_fit):
    for i in range(N):
        c = out_of_pos_fit[i].upper()
        if c != BLANK and c not in word or word.find(c) == i:
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
    true_fit = data[ENTRY_FIT]
    out_of_pos = data[ENTRY_OUT]
    not_fit = data[ENTRY_NOT]
    fit_words = data[FIT_LIST]
    for word in words:
        if len(word) == 6:
            word = word.upper()
            if check_word(word, true_fit, out_of_pos, not_fit, fit_words):
                flag_find = 1
    return flag_find


def get_data(builder):
    true_fit, out_of_pos, not_fit, fit_words = [], [], [], []
    data = {
        ENTRY_FIT: true_fit,
        ENTRY_OUT: out_of_pos,
        ENTRY_NOT: not_fit,
        FIT_LIST: fit_words,
    }
    entries = []
    for i in range(N):
        entries.append(builder.get_object(ENTRY_FIT + str(i)))
    for e in entries:
        text = e.get_text()
        text = text if (len(text)) else BLANK
        data[ENTRY_FIT].append(text)
    entries.clear()
    for i in range(N):
        entries.append(builder.get_object(ENTRY_OUT + str(i)))
    for e in entries:
        text = e.get_text()
        text = text if (len(text)) else BLANK
        data[ENTRY_OUT].append(text)
    data[ENTRY_NOT].append(builder.get_object(ENTRY_NOT).get_text())
    return data


def on_search_clicked(button, result, builder):
    data = get_data(builder)
    flag_find = 0
    name = button.get_name()
    if name == BUT_SEARCH:
        with open(FILE_NAME, "r", encoding=ENCODE) as inp:
            words = inp.readlines()
            flag_find = search_cycle(words, data)
    text = ""
    fitted_words = data[FIT_LIST]
    if flag_find and len(fitted_words) < 100:
        text = "".join(fitted_words)
    elif flag_find:
        text = "".join([fitted_words[i] for i in range(100)])
        text += "и т.д\n"
    text_buffer = result.get_buffer()
    text_buffer.set_text("")
    text_buffer.set_text(text)
