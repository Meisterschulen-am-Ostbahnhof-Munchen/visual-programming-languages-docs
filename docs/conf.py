# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys

sys.setrecursionlimit(1500)

SOURCE_DIR = os.path.abspath(os.path.join(".", "..", "src"))
sys.path.insert(0, SOURCE_DIR)


# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = "Visuelle Programmiersprachen: Low-Code (4)"
copyright = "2022-2025, Meisterschulen am Ostbahnhof - München"
author = "Franz Höpfinger"


# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "myst_parser",
    "sphinx_c_autodoc",
    "sphinxcontrib.mermaid",
    "sphinxcontrib.googleanalytics",
]

version = "0.0.2"
release = version
templates_path = ["_templates"]

# -- Options for EPUB output
epub_show_urls = "footnote"

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store", "CHANGELOG.rst"]


# -- MyST settings ---------------------------------------------------

myst_enable_extensions = [
    "colon_fence",
]
myst_heading_anchors = 7

googleanalytics_id = 'G-4WPKCFX4NN'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"
html_theme_options = {
    'navigation_depth': 7,
}


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
