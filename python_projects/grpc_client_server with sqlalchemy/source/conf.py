# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

import sys
import os
sys.path.append(os.path.abspath('../client/'))
sys.path.append(os.path.abspath('../server/'))
sys.path.append(os.path.abspath('../common_files/'))
sys.path.append(os.path.abspath('../protobuf/'))


project = 'Battleship messages'
copyright = '2024, suzannpi'
author = 'suzannpi'
release = '1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['sphinx.ext.autodoc',]

autodoc_default_options = {
       'members': True,
       'undoc-members': True,
       'private-members': False,
       'show-inheritance': True,
}

autodoc_mock_imports = ['numpy', 'pandas']

automodule_content = 'both'


templates_path = ['_templates']
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']
html_logo = '_static/img.png'
html_favicon = '_static/img.png'
html_title = "Battleship messages doc"
