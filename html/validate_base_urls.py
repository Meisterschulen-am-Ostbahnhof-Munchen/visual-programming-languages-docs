import re
import sys
import urllib.request
import urllib.error

# check_links.py and friends only ever validate a link against the local
# docs/de/ tree of the repo whose files they can see - they have no way to
# catch a wrong *base URL* (a project slug that isn't actually registered on
# ReadTheDocs), since from a filesystem point of view there's nothing local
# to check it against. That exact class of bug shipped once already: both
# lib_base_url and ex_base_url used a "-de" suffix that was never a real
# subproject slug, and every single Bibliotheken/Uebungen link 404'd.
# This asks ReadTheDocs directly which subproject slugs actually exist.

SUBPROJECTS_API = (
    "https://readthedocs.org/api/v3/projects/"
    "meisterschulen-am-ostbahnhof-munchen-docs/subprojects/"
)

EXPECTED_SLUGS = {
    "lib_base_url": "4diac-library-reference-docs",
    "ex_base_url": "4diac-exercises-docs",
}


def extract_slug(url):
    m = re.search(r"/projects/([^/]+)/", url)
    return m.group(1) if m else None


def get_configured_base_urls():
    import edit_abkuerzungen as e
    return {
        "lib_base_url": e.lib_base_url,
        "ex_base_url": e.ex_base_url,
    }


def fetch_registered_slugs():
    req = urllib.request.Request(SUBPROJECTS_API, headers={"User-Agent": "validate_base_urls"})
    with urllib.request.urlopen(req, timeout=20) as response:
        import json
        data = json.loads(response.read().decode("utf-8"))
    return {item["child"]["slug"] for item in data.get("results", [])}


def main():
    configured = get_configured_base_urls()
    try:
        registered = fetch_registered_slugs()
    except (urllib.error.URLError, TimeoutError) as exc:
        print(f"Could not reach ReadTheDocs API: {exc}")
        sys.exit(2)

    problems = []
    for name, url in configured.items():
        slug = extract_slug(url)
        expected = EXPECTED_SLUGS.get(name)
        if slug != expected:
            problems.append(f"{name}: uses slug '{slug}', expected '{expected}'")
        elif slug not in registered:
            problems.append(f"{name}: slug '{slug}' is not a registered RTD subproject")
        else:
            print(f"OK  {name} -> '{slug}' is a registered RTD subproject")

    if problems:
        print("\nProblems found:")
        for p in problems:
            print(f"  - {p}")
        sys.exit(1)

    print("\nAll base URLs point at registered RTD subprojects.")


if __name__ == "__main__":
    main()
