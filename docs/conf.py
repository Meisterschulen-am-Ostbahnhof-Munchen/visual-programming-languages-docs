# -*- coding: utf-8 -*-
# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
sys.path.insert(0, os.path.abspath('..'))


# -- Project information -----------------------------------------------------

project = "visual programming languages Docs"
copyright = "2022, Meisterschulen am Ostbahnhof, München"
author = "Franz Höpfinger"


# -- General configuration ---------------------------------------------------
# -- General configuration

extensions = [
    "sphinx.ext.duration",
    "sphinx.ext.doctest",
    "sphinx.ext.autosectionlabel",
    "sphinx.ext.autodoc",
    "sphinx.ext.intersphinx",
    "sphinx.ext.imgconverter",
    "recommonmark",
    "sphinxcontrib.mermaid",
    "sphinx_markdown_tables"
]

version = "0.0.1"
release = version
intersphinx_mapping = {
    "rtd": ("https://docs.readthedocs.io/en/stable/", None),
    "python": ("https://docs.python.org/3/", None),
    "sphinx": ("https://www.sphinx-doc.org/en/master/", None),
}
intersphinx_disabled_domains = ["std"]

# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.

# Handle failing hawkmoth import gracefully to be able to build the
# documentation on e.g. https://readthedocs.org/ which would otherwise fail due
# to missing clang.

# This is not a good example to follow in regular documentation.
try:
    import hawkmoth
    from hawkmoth.util import doccompat, readthedocs
    from sphinx.ext.napoleon import docstring, Config

    readthedocs.clang_setup()

    extensions.append('hawkmoth')
    tags.add('have_hawkmoth')

    def napoleon_transform(comment):
        config = Config(napoleon_use_rtype=False)
        return str(docstring.GoogleDocstring(comment, config))

    cautodoc_transformations = {
        'napoleon': napoleon_transform,
        'javadoc-liberal': doccompat.javadoc_liberal,
    }
except ImportError:
    sys.stderr.write('Warning: Failed to import hawkmoth. Mocking results.\n')
    sys.path.insert(0, os.path.abspath('ext'))
    # The mock extension will include the hawkmoth test suite expected results
    # into the documentation instead of generating.
    extensions.append('automock')

hawkmoth_root = os.path.join(os.path.abspath(os.path.dirname(__file__)), '../test')

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# -- Options for EPUB output
epub_show_urls = "footnote"

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

