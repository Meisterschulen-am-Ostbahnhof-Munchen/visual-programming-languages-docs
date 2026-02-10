import json
import os

# Configuration
JSON_FILE = 'Abkuerzungen_und_Bedeutungen.json'
HTML_FILE = 'Abkuerzungen_und_Bedeutungen.htm'

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
JSON_PATH = os.path.join(SCRIPT_DIR, JSON_FILE)
HTML_PATH = os.path.join(SCRIPT_DIR, HTML_FILE)

HTML_HEADER = """<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Abkuerzungen_und_Bedeutungen - Strukturiert</title>
    <style>
        /* --- Basis Design --- */
        body {
            font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
            background-color: #f9f9fb;
            color: #333;
            margin: 0;
            padding: 20px;
        }

        /* --- Header & Suche --- */
        .header-container {
            position: sticky;
            top: 0;
            background-color: #f9f9fb;
            padding: 10px 0 10px 0;
            z-index: 1000;
            border-bottom: 1px solid #e0e0e0;
            margin-bottom: 20px;
        }

        h1 { color: #733C24; margin: 0 0 10px 0; font-size: 1.8rem; }

        input#searchInput {
            width: 100%;
            padding: 12px 15px;
            font-size: 16px;
            border: 2px solid #ddd;
            border-radius: 6px;
            box-sizing: border-box;
            box-shadow: 0 2px 5px rgba(0,0,0,0.05);
        }
        input#searchInput:focus {
            border-color: #9A5130;
            outline: none;
        }

        /* --- Inhaltsverzeichnis (TOC) --- */
        .toc-container {
            background: white;
            padding: 15px;
            border-radius: 8px;
            margin-bottom: 30px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.05);
            border-left: 5px solid #9A5130;
        }
        .toc-container h3 { margin-top: 0; color: #555; }
        .toc-list {
            display: flex;
            flex-wrap: wrap;
            gap: 10px;
        }
        .toc-link {
            text-decoration: none;
            color: #007bff;
            background: #f1f5f9;
            padding: 5px 10px;
            border-radius: 4px;
            font-size: 0.9rem;
            transition: background 0.2s;
        }
        .toc-link:hover { background: #e2e6ea; text-decoration: none; }

        /* --- Sektionen & Tabellen --- */
        .category-section {
            margin-bottom: 40px;
            background: white;
            border-radius: 8px;
            box-shadow: 0 4px 15px rgba(0,0,0,0.05);
            overflow: hidden; /* Für border-radius */
        }

        .category-header {
            background-color: #9A5130;
            color: white;
            padding: 15px 20px;
            margin: 0;
            font-size: 1.4rem;
        }

        .table-responsive {
            overflow-x: auto;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            min-width: 1200px;
        }

        th {
            background-color: #f0f0f0;
            color: #333;
            text-align: left;
            padding: 12px 10px;
            font-weight: 600;
            border-bottom: 2px solid #ddd;
        }

        td {
            padding: 10px;
            border-bottom: 1px solid #eee;
            vertical-align: top;
            font-size: 0.95rem;
            line-height: 1.5;
        }

        tr:hover td { background-color: #f8f9fa; }

        /* Farben für Typen (Basierend auf Eclipse 4diac Farbschema) */
        tr.row-event td:nth-child(2) {
            background-color: #E0F2D1; /* Hellgrün tint */
            color: #63B31F;
            font-weight: bold;
            border-left: 4px solid #63B31F;
        }
        tr.row-bool td:nth-child(2) {
            background-color: #F2F3EE; /* Graugrün tint */
            color: #9FA48A;
            font-weight: bold;
            border-left: 4px solid #9FA48A;
        }
        tr.row-adapter td:nth-child(2) {
            background-color: #E6DDF2; /* Violett tint */
            color: #845DAF;
            font-weight: bold;
            border-left: 4px solid #845DAF;
        }
        tr.row-any_bit td:nth-child(2) {
            background-color: #E6ECEE; /* ANY_BIT tint */
            color: #82A3A9;
            font-weight: bold;
            border-left: 4px solid #82A3A9;
        }
        tr.row-any_int td:nth-child(2) {
            background-color: #D1DFF2; /* ANY_INT tint */
            color: #18519E;
            font-weight: bold;
            border-left: 4px solid #18519E;
        }
        tr.row-any_real td:nth-child(2) {
            background-color: #F8F0D1; /* ANY_REAL tint */
            color: #DBB418;
            font-weight: bold;
            border-left: 4px solid #DBB418;
        }
        tr.row-any_string td:nth-child(2) {
            background-color: #F2E7E0; /* ANY_STRING tint */
            color: #BD8663;
            font-weight: bold;
            border-left: 4px solid #BD8663;
        }
        tr.row-time td:nth-child(2) {
            background-color: #CCCCFF; /* TIME tint */
            color: #0000FF;
            font-weight: bold;
            border-left: 4px solid #0000FF;
        }

        /* Links & Bilder */
        a { color: #007bff; text-decoration: none; word-break: break-word; }
        a:hover { text-decoration: underline; }
        img { max-width: 100px; height: auto; display: block; }
        .empty { color: #ccc; font-size: 0.8em; }

        /* Utility Class zum Ausblenden */
        .hidden { display: none !important; }
        
        /* Zähler-Badge */
        .count-badge {
            float: right;
            font-size: 0.8rem;
            background: rgba(255,255,255,0.2);
            padding: 2px 8px;
            border-radius: 10px;
            font-weight: normal;
        }
    </style>
</head>
<body>

    <div class="header-container">
        <h1>Wiki / Glossar</h1>
		<h2>Abkuerzungen_und_Bedeutungen</h2>
		<a href="https://www.ms-muc-docs.de/iec-61499/abk%C3%BCrzungen-und-bedeutungen" target="_blank"> zur Offline-version</a>
		
        <input type="text" id="searchInput" placeholder="Suchbegriff eingeben... (Filtert über alle Kategorien)" onkeyup="filterAllTables()">
        <div style="margin-top:5px; font-size: 0.9em; color: #666;">
            Gesamt gefundene Einträge: <span id="globalCount">0</span>
        </div>
    </div>

    <div class="toc-container" id="tocContainer">
        <h3>Inhaltsverzeichnis</h3>
        <div class="toc-list" id="tocList"></div>
    </div>

    <div id="contentArea"></div>

<script>
    // =================================================================
    // 1. DATEN-TEIL (Aufgeteilt in Kategorien)
    // =================================================================

    const glossaryData = 
"""

HTML_FOOTER = """
;

    // =================================================================
    // 3. PROGRAMMLOGIK (Rendering & Filter)
    // =================================================================

    const contentArea = document.getElementById('contentArea');
    const tocList = document.getElementById('tocList');
    const globalCountDisplay = document.getElementById('globalCount');

    // --- Initiale Erstellung der Seite ---
    function initPage() {
        let globalTotalItems = 0;

        glossaryData.categories.forEach(cat => {
            // 1. Eintrag im Inhaltsverzeichnis
            const tocLink = document.createElement('a');
            tocLink.href = "#" + cat.id;
            tocLink.className = "toc-link";
            tocLink.innerText = cat.title;
            tocLink.onclick = function(e) {
                e.preventDefault(); // Verhindert das Öffnen eines neuen Fensters
                const targetElement = document.getElementById(cat.id);
                if (targetElement) {
                    // Scrollt sanft zum Ziel
                    targetElement.scrollIntoView({ behavior: 'smooth', block: 'start' });
                }
            };
            tocList.appendChild(tocLink);

            // 2. Sektion erstellen (Container)
            const section = document.createElement('div');
            section.className = "category-section";
            section.id = cat.id;

            // 3. Header erstellen
            const header = document.createElement('h2');
            header.className = "category-header";
            header.innerHTML = `${cat.title} <span class="count-badge" id="badge-${cat.id}">${cat.data.length}</span>`;
            section.appendChild(header);

            // 4. Tabelle erstellen
            const tableContainer = document.createElement('div');
            tableContainer.className = "table-responsive";

            const table = document.createElement('table');
            table.innerHTML = `
                <thead>
                    <tr>
                        <th width="3%">Nr</th>
                        <th width="15%">Begriff</th>
                        <th width="20%">Bedeutung</th>
                        <th width="10%">Übung</th>
                        <th width="10%">Intern</th>
                        <th width="5%">Video</th>
                        <th width="10%">Ext. (DE)</th>
                        <th width="10%">Ext. (EN)</th>
                        <th width="17%">Notiz</th>
                    </tr>
                </thead>
                <tbody id="tbody-${cat.id}"></tbody>
            `;

            tableContainer.appendChild(table);
            section.appendChild(tableContainer);
            contentArea.appendChild(section);

            // 5. Daten in Tabelle füllen
            const tbody = table.querySelector('tbody');
            cat.data.forEach(row => {
                const tr = document.createElement('tr');
                if (row.type) {
                    tr.classList.add('row-' + row.type);
                }

                tr.innerHTML = `
                    <td>${safe(row.nr)}</td>
                    <td>${safe(row.term)}</td>
                    <td>${safe(row.mean)}</td>
                    <td>${safe(row.ex)}</td>
                    <td>${safe(row.link_int)}</td>
                    <td>${safe(row.vid)}</td>
                    <td>${safe(row.ext_de)}</td>
                    <td>${safe(row.ext_en)}</td>
                    <td>${safe(row.title)}</td>
                `;
                tbody.appendChild(tr);
            });

            globalTotalItems += cat.data.length;
        });

        globalCountDisplay.innerText = globalTotalItems;
    }

    // Hilfsfunktion für leere Zellen
    function safe(val) {
        return (val && val !== "") ? val : "<span class='empty'>-</span>";
    }

    // --- Filter Logik ---
    function filterAllTables() {
        const input = document.getElementById('searchInput').value.toLowerCase();
        let totalGlobalVisible = 0;

        glossaryData.categories.forEach(cat => {
            const section = document.getElementById(cat.id);
            const tbody = document.getElementById("tbody-" + cat.id);
            const rows = tbody.querySelectorAll('tr');
            let catVisibleCount = 0;

            rows.forEach(row => {
                const text = row.innerText.toLowerCase();
                if (text.includes(input)) {
                    row.classList.remove('hidden');
                    catVisibleCount++;
                } else {
                    row.classList.add('hidden');
                }
            });

            // Update Badge Count
            document.getElementById(`badge-${cat.id}`).innerText = catVisibleCount;

            // Ganze Sektion ausblenden, wenn Tabelle leer ist
            if (catVisibleCount === 0) {
                section.classList.add('hidden');
            } else {
                section.classList.remove('hidden');
            }

            totalGlobalVisible += catVisibleCount;
        });

        globalCountDisplay.innerText = totalGlobalVisible;

        // Optional: Meldung wenn gar nichts gefunden wurde
        if(totalGlobalVisible === 0 && input !== "") {
            // Man könnte hier eine "Nichts gefunden" Meldung einblenden
        }
    }

    // Start
    initPage();

</script>

</body>
</html>
"""

def generate_html():
    if not os.path.exists(JSON_PATH):
        print(f"Error: {JSON_PATH} not found.")
        return

    print(f"Reading JSON from {JSON_PATH}...")
    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        json_content = f.read()

    print("Generating HTML...")
    full_html = HTML_HEADER + json_content + HTML_FOOTER

    with open(HTML_PATH, 'w', encoding='utf-8') as f:
        f.write(full_html)
    
    print(f"Successfully generated {HTML_PATH}")

if __name__ == "__main__":
    generate_html()
