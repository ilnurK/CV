import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
import five_letters_back as fb

def init_widgets(builder):
    window = builder.get_object("window")
    window.connect("destroy", Gtk.main_quit)
        
    letter1 = builder.get_object("e_letter1")
    letter2 = builder.get_object("e_letter2")
    letter3 = builder.get_object("e_letter3")
    letter4 = builder.get_object("e_letter4")
    letter5 = builder.get_object("e_letter5")
    
    true_fit = [fb.BLANK for i in range(fb.N)]
    
    letter1.connect("changed", lambda ent: fb.on_entry_fitted_changed(ent, true_fit))
    letter2.connect("changed", lambda ent: fb.on_entry_fitted_changed(ent, true_fit))
    letter3.connect("changed", lambda ent: fb.on_entry_fitted_changed(ent, true_fit))
    letter4.connect("changed", lambda ent: fb.on_entry_fitted_changed(ent, true_fit))
    letter5.connect("changed", lambda ent: fb.on_entry_fitted_changed(ent, true_fit))

    letter_pos1 = builder.get_object("e_letter_pos1")
    letter_pos2 = builder.get_object("e_letter_pos2")
    letter_pos3 = builder.get_object("e_letter_pos3")
    letter_pos4 = builder.get_object("e_letter_pos4")
    letter_pos5 = builder.get_object("e_letter_pos5")
    
    out_of_pos_fit = [fb.BLANK for i in range(fb.N)]
        
    letter_pos1.connect("changed", lambda ent: fb.on_entry_out_of_pos_changed(ent,  out_of_pos_fit))
    letter_pos2.connect("changed", lambda ent: fb.on_entry_out_of_pos_changed(ent,  out_of_pos_fit))
    letter_pos3.connect("changed", lambda ent: fb.on_entry_out_of_pos_changed(ent,  out_of_pos_fit))
    letter_pos4.connect("changed", lambda ent: fb.on_entry_out_of_pos_changed(ent,  out_of_pos_fit))
    letter_pos5.connect("changed", lambda ent: fb.on_entry_out_of_pos_changed(ent,  out_of_pos_fit))

    letters_no_fit = builder.get_object("e_no_fit")
    
    not_fit = list()
    not_fit.append("")

    letters_no_fit.connect("changed", lambda ent: fb.on_entry_no_fit_changed(ent, not_fit))

    but_search = builder.get_object("but_search")
    result = builder.get_object("result")
        
    fit_words = list()
    data = {"true": true_fit, "out": out_of_pos_fit, "not": not_fit, "list" :fit_words}
        
    but_search.connect("clicked", lambda btn: fb.on_search_clicked(btn, result, data))
    return window

def five_letters_gui(glade_name):
    builder = Gtk.Builder()
    try:
        builder.add_from_file(glade_name)
        window = init_widgets(builder)
        window.show_all()
        Gtk.main()
    except BaseException:
        print("Ошибка открытия файла")

glade_name = "five_letters_gui.glade"
five_letters_gui(glade_name)
