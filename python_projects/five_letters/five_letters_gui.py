import gi

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
import five_letters_back as fb


def init_widgets(builder):
    window = builder.get_object("window")
    window.connect("destroy", Gtk.main_quit)

    but_search = builder.get_object("but_search")
    result = builder.get_object("result")

    but_search.connect(
        "clicked", lambda btn: fb.on_search_clicked(btn, result, builder)
    )
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
