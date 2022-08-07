import datetime

project = 'myproject'
year = datetime.datetime.now().year
copyright = f'{year}, Read the Docs'
author = 'Read the Docs'

version = '1.0.0'
release = '1.0.0'

extensions = [
    "myst_parser",
]

source_suffix = '.rst'
master_doc = 'index'
html_theme = 'sphinx_rtd_theme'
