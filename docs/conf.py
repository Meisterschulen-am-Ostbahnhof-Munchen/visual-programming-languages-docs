#
# Configuration file for the Sphinx documentation builder.
# v
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

SOURCE_DIR = os.path.abspath(os.path.join(".", "..", "src"))
sys.path.insert(0, SOURCE_DIR)


# -- Project information -----------------------------------------------------

project = "visual programming languages Docs"
copyright = "2022, Meisterschulen am Ostbahnhof, München"
author = "Franz Höpfinger"


# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "myst_parser",
    "sphinx.ext.autodoc",
    "sphinx.ext.duration",
    "sphinx.ext.doctest",
    "sphinx.ext.intersphinx",
    "sphinx.ext.autosectionlabel",
    "sphinx.ext.todo",
    "sphinx.ext.coverage",
    "sphinx.ext.imgmath",
    "sphinx.ext.viewcode",
    "sphinx.ext.napoleon",
    "sphinx_rtd_theme",
    "sphinxcontrib.autoprogram",
    "sphinx_c_autodoc",
    "sphinx_c_autodoc.napoleon",
    "sphinx_c_autodoc.viewcode",
    "sphinx.ext.intersphinx",
    "sphinx.ext.imgconverter",
    "sphinxcontrib.mermaid",
    "sphinx_markdown_tables"
    # Unfortunatly the typehints fail for the autodoc Documenter class, would
    # really like to work around this, but also want to keep the warning output
    # clean since this is a sphinx extension and would like to know when/if it
    # is producing warnings of its own
    # 'sphinx_autodoc_typehints',
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


# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# -- Options for EPUB output
epub_show_urls = "footnote"

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store", "CHANGELOG.rst"]
# -- MyST settings ---------------------------------------------------

myst_enable_extensions = [
    "dollarmath",
    "amsmath",
    "deflist",
    "fieldlist",
    "html_admonition",
    "html_image",
    "colon_fence",
    "smartquotes",
    "replacements",
    "linkify",
    "strikethrough",
    "substitution",
    "tasklist",
    "attrs_inline",
    "inv_link",
]
myst_number_code_blocks = ["typescript"]
myst_heading_anchors = 9
myst_footnote_transition = True
myst_dmath_double_inline = True

# Prefix document path to section labels, to use:
# `path/to/file:heading` instead of just `heading`
autosectionlabel_prefix_document = True

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
# html_theme_options = {}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]

# -- Options for sphinx_c_autodoc, the extension being documented -----------

c_autodoc_roots = ["../tests/assets/c_source"]
# force libclang access for read the docs.
# Read the docs installs doxygen which will install libclang, unfortunatly it
# doesn't appear the so is in the path so need to grab a _backend_ version of
# the file.
if "READTHEDOCS" in os.environ:
    from clang import cindex

    cindex.Config.set_library_file("/usr/lib/x86_64-linux-gnu/libclang-14.so.1")
