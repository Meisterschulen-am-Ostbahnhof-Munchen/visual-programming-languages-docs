import html
import json
import os
import re
import urllib.parse

# The FB/Adapter reference (Bibliotheken/) lives in a separate repo since the
# split (see README.md). scan_missing_entries.py only ever walked this repo's
# own docs/ tree, so as that sibling repo grows, newly-added FB/adapter pages
# never make it into the glossary unless someone remembers to hand-curate
# them into edit_abkuerzungen.py. This does the same "diff docs tree against
# JSON, auto-add what's missing" pass scan_missing_entries.py does, just
# pointed at the sibling repo checkout (expects `ms-docs` repos to be
# siblings under the same parent directory, matching add_isobus_entries.py's
# convention) instead of this repo's own docs/.
JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkuerzungen_und_Bedeutungen.json')
LIB_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '4diac-library-reference-docs', 'docs', 'de'))
LIB_BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/de/latest/'

IGNORE_FILES = {
    'index.md', 'README.md', 'conf.py', 'requirements.txt', 'make.bat', 'Makefile',
}


def url_to_rel_path(url):
    """Normalize a LIB_BASE_URL-prefixed link (pretty '/' URL or '.html') back
    to the source-relative '.md' path it was generated from."""
    rel_path = urllib.parse.unquote(url[len(LIB_BASE_URL):].split('#')[0])
    if rel_path.endswith('/'):
        return rel_path[:-1] + '.md'
    if '.html' in rel_path:
        return rel_path.replace('.html', '.md')
    return rel_path


def record_category_hit(dir_category_map, rel_path, cat_id):
    """Track which category a directory's already-linked files usually belong to."""
    dir_path = os.path.dirname(rel_path)
    dir_category_map.setdefault(dir_path, {})
    dir_category_map[dir_path][cat_id] = dir_category_map[dir_path].get(cat_id, 0) + 1


def get_linked_files_and_dirs(data):
    """Returns a set of normalized relative paths already linked in the JSON
    (pointing at LIB_BASE_URL), and a map of dir -> category_id histogram."""
    linked_files = set()
    dir_category_map = {}

    for category in data.get('categories', []):
        cat_id = category.get('id')
        for entry in category.get('data', []):
            match = re.search(r'href="([^"]+)"', entry.get('link_int', '') or '')
            if not match or not match.group(1).startswith(LIB_BASE_URL):
                continue

            rel_path = url_to_rel_path(match.group(1))
            linked_files.add(rel_path)
            record_category_hit(dir_category_map, rel_path, cat_id)

    return linked_files, dir_category_map


def predict_category(file_rel_path, dir_category_map):
    """Guess category based on siblings already linked from the same directory."""
    dir_path = os.path.dirname(file_rel_path.replace(os.sep, '/'))
    if dir_path in dir_category_map:
        cats = dir_category_map[dir_path]
        return max(cats, key=cats.get)
    return "cat_types"


def find_missing_files(linked_files):
    """Walk LIB_ROOT for '.md' files not yet referenced by any glossary entry."""
    missing_files = []
    for root, dirs, files in os.walk(LIB_ROOT):
        dirs[:] = [d for d in dirs if not d.startswith('.')]

        for file in files:
            if not file.endswith('.md') or file in IGNORE_FILES:
                continue

            abs_path = os.path.join(root, file)
            rel_path_web = os.path.relpath(abs_path, LIB_ROOT).replace(os.sep, '/')

            if rel_path_web not in linked_files:
                missing_files.append((rel_path_web, file))

    return missing_files


def build_entry(rel_path, term):
    """New glossary entry for a not-yet-linked library doc page. The path
    segments and term come straight from filenames on disk, so encode/escape
    them before they end up in an <a> tag that a page later inserts via
    innerHTML (see generate_glossary_html.py)."""
    url_path = urllib.parse.quote(rel_path[:-len('.md')] + '/')
    safe_term = html.escape(term)
    return {
        "nr": "",
        "term": term,
        "mean": f"{term} (Auto-added)",
        "ex": "",
        "exdoc": "",
        "link_int": f'<a href="{LIB_BASE_URL}{url_path}" target="_blank">{safe_term}</a>',
        "vid": "",
        "ext_de": "",
        "ext_en": "",
        "title": term,
        "type": ""
    }


def scan_and_add_missing():
    if not os.path.isdir(LIB_ROOT):
        print(f"Error: sibling repo not found at {LIB_ROOT}")
        return

    print(f"Scanning for markdown files in {LIB_ROOT} not in JSON...")

    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        data = json.load(f)

    linked_files, dir_category_map = get_linked_files_and_dirs(data)
    missing_files = find_missing_files(linked_files)

    if not missing_files:
        print("No missing files found.")
        return

    print(f"Found {len(missing_files)} missing files.")

    categories_by_id = {cat['id']: cat for cat in data['categories']}
    added_count = 0
    for rel_path, filename in missing_files:
        term = os.path.splitext(filename)[0]
        if term.lower() in ('index', 'readme', 'intro'):
            continue

        target_cat_id = predict_category(rel_path, dir_category_map)
        target_cat = categories_by_id.get(target_cat_id)
        if target_cat is None:
            continue

        target_cat['data'].append(build_entry(rel_path, term))
        added_count += 1

    if added_count > 0:
        with open(JSON_PATH, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=3, ensure_ascii=False)
        print(f"\nAdded {added_count} missing entries to {JSON_PATH}.")


if __name__ == '__main__':
    scan_and_add_missing()
