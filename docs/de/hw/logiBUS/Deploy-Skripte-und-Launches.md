# Deploy-Skripte und Launches

Diese Seite beschreibt, wie Programme aus der 4diac IDE auf die logiBUS®-Trainingsknoten (ESP32) gelangen und welche Skripte und Launch-Konfigurationen dafür im Trainingsprojekt vorhanden sind.

!!! info "Wo liegt was?"
    Alle Pfade beziehen sich auf den Ordner `Ventilsteuerung/` des Trainingsprojekts.

    - Python-Skripte: `scripts_central/`
    - Je Workspace (`test_AX`, `test_B`, `test_VV`): `scripts/` (`.bat` für Windows, `.sh` für Linux) und `Launches/` (`.launch`-Dateien für die 4diac IDE)

## Überblick: zwei Wege auf den Knoten

| Weg | Was wird übertragen | Wann |
| --- | --- | --- |
| **Online-Deploy** aus der 4diac IDE (`Deploy_App_*`) | Die Anwendung wird direkt in die laufende FORTE-Instanz geladen. | Schnelles Ausprobieren einer Übung. Nach einem Neustart ist die Anwendung weg. |
| **Boot-Datei-Deploy** (Python-Skripte) | `.fboot`, Bibliotheks-Manifest (`.libs.json`) und die benötigten ELF-Bibliotheken werden per HTTP auf den Knoten kopiert. | Dauerhafte Installation. FORTE lädt die Boot-Datei beim nächsten Start. |

Für den Online-Deploy muss der Knoten vorher mit der ELF-Grundausstattung vorbereitet sein (siehe [Knoten vorbereiten](#knoten-vorbereiten-preload)). Sonst meldet FORTE für Bausteine, deren Bibliothek fehlt, `UNSUPPORTED_TYPE`.

## Python-Skripte in `scripts_central/`

Alle Skripte sind reines Python (nur Standardbibliothek, keine `pip`-Installation nötig).

### Deploy und Bibliotheken

| Skript | Aufgabe |
| --- | --- |
| `make_libs_manifest.py` | Erzeugt lokal `boot-files/<Boot-Datei>.libs.json`. Kein Netzwerkzugriff. Die Option `--out <Pfad>` schreibt das Manifest an einen anderen Ort (Testlauf). |
| `make_4diac_training1_deploy.py` | Lädt die Boot-Datei, das Manifest und die benötigten ELF-Bibliotheken auf die Knoten aus `NODE_ORDER`. |
| `make_4diac_training1_deploy_dido.py` | Deploy für den DIDO-Tester: wie oben, zusätzlich VT-Pool (`DefaultPool.iop`), Sichtbarkeitstabelle (`DefaultPool.vis.json`) und Web-Client (`apixon-diodo.html`). Zielknoten als Argument, Standard `logibus.local`. |
| `make_4diac_training1_elf_preload.py` | Bereitet einen Knoten für den Online-Deploy vor (nur Grundausstattung, keine Boot-Datei). |
| `deploy_common.py` | Kein eigenes Skript, sondern gemeinsames Modul: Zuordnung Knoten-Adresse zu Boot-Datei (`NODE_BASES`, `NODE_ORDER`), Pfade der Boot-Dateien und die Liste der Grundausstattung (`PRELOAD_LIBS`). |
| `elf_libs_manifest_lib.py` | Logik hinter dem Manifest: welcher 4diac-Typ zu welcher Bibliothek gehört, `requires` aus der `MANIFEST.MF`, Architektur der Knoten (`riscv32` oder `xtensa`) und die Firmware-Grenzen. |

### Pool-Erzeugung und Prüfungen

| Skript | Aufgabe |
| --- | --- |
| `compile_iso_designer_project.py` | Übersetzt ein ISO-Designer-Projekt über die Kommandozeile (`ISODesigner.exe /Compile`). Pflichtargument `--pool-dir`. Nur Windows, mit installiertem ISO-Designer. |
| `GcfScript.py` | Erzeugt aus `DefaultPool.iop.h` (und optional `DefaultPool.jop`) die `.gcf`-Konstantendateien für 4diac. |
| `list_mask_objects.py` | Liest die Masken des Pools und schreibt die Sichtbarkeitstabellen (`.vis.csv`, `.vis.json`). |
| `check_mixed_numeric_pool_imports.py` | Findet `.SUB`-Dateien, die VT-Konstanten aus mehreren verschiedenen Pools importieren. |

!!! warning "Generierte `.gcf`-Dateien nicht von Hand ändern"
    `GcfScript.py` baut die `.gcf`-Dateien jedes Mal komplett neu aus `DefaultPool.iop.h`. Von Hand ergänzte Konstanten gehen beim nächsten Lauf verloren. Änderungen gehören in den ISO-Designer, danach den Build-Lauf wiederholen.

## Ablauf eines Boot-Datei-Deploys

`make_4diac_training1_deploy.py` arbeitet die Knoten nacheinander ab:

1. **Dateien prüfen.** Fehlt eine Boot-Datei (`boot-files/…fboot`), bricht das Skript ab. Die Boot-Datei muss vorher aus der 4diac IDE exportiert sein. Das Skript baut selbst nichts.
2. **Knoten prüfen.** Der Name wird einmal aufgelöst. Erlaubt sind nur Knoten im internen Netz (`10.x`, `172.16`–`172.31`, `192.168.x`, `169.254.x`, `*.local`). Nicht erreichbare Knoten werden übersprungen.
3. **Architektur prüfen.** Die Architektur des Knotens muss zu den ELF-Bibliotheken passen, sonst wird für diesen Knoten nichts hochgeladen.
4. **Boot-Datei hochladen** (`POST /upload/<datei>`). Hat der Knoten die neue Firmware, wird die Datei über den SHA-256-Hash verglichen. Unveränderte Dateien werden übersprungen, hochgeladene Dateien werden anschließend verifiziert.
5. **Alte Boot-Dateien entfernen**, die zu diesem Knoten gehören.
6. **Manifest und ELF-Bibliotheken.** Das Skript ermittelt aus der Boot-Datei die benötigten Bibliotheken samt `requires`, räumt alte Versionen in `elf-libs/` auf und lädt fehlende ELF-Dateien nach `elf-libs/` hoch.
7. **Manifest zuletzt hochladen.** Ist mindestens ein ELF-Upload fehlgeschlagen, wird das Manifest bewusst nicht hochgeladen.

Grenzen der Firmware: höchstens 64 Bibliotheken je Knoten und höchstens 8 `requires` je Bibliothek. Wird eine Grenze überschritten, meldet das Skript eine Warnung.

!!! warning "Das Skript startet den Knoten nicht neu"
    Neue Dateien werden erst nach einem Neustart aktiv, zum Beispiel über den Reboot-Button auf `http://<ip>/`. Meldet die Zusammenfassung einen Fehler für einen Knoten, diesen **nicht** neu starten, sondern das Deploy wiederholen.

!!! warning "Es gibt keinen Trockenlauf"
    Das Skript lädt wirklich auf den Knoten hoch. Vor wiederholten Testläufen den freien Speicher unter `http://<ip>/space/` prüfen. Ein fast volles Dateisystem kann bei weiteren Uploads beschädigt werden und wird beim nächsten Start neu formatiert. Dabei sind alle Dateien weg.

### Knoten vorbereiten (Preload)

`make_4diac_training1_elf_preload.py` kopiert die Grundausstattung (`PRELOAD_LIBS` in `deploy_common.py`, plus deren `requires`) nach `/data/elf-libs/` und legt ein eigenes Manifest ohne Boot-Datei an. Alle anderen Manifeste und alle `.fboot`-Dateien auf dem Knoten werden dabei **gelöscht**: FORTE startet danach leer, aber mit geladenen Bibliotheken, und die Übung kommt per Online-Deploy aus der IDE.

    python make_4diac_training1_elf_preload.py                                 # logibus.local
    python make_4diac_training1_elf_preload.py 192.168.178.45   # bestimmter Knoten

Nicht zur Grundausstattung gehören `Funk`, `DataPanel`, `BlinkMarine` und `logiBUS_bosch`. Das Board „Trainer“ hat kein CAN2. Auch hier gilt: Neue Dateien werden erst nach einem Neustart des Knotens aktiv.

Ein späteres normales Deploy ersetzt das Preload-Manifest durch sein eigenes. Die ELF-Dateien der Grundausstattung bleiben liegen und werden per Hash übersprungen.

Die Knotenadressen stehen in `deploy_common.py` und `elf_libs_manifest_lib.py`. Wird ein Knoten ersetzt, müssen sie dort angepasst werden.

## Launch-Konfigurationen in der 4diac IDE

Die Dateien in `Launches/` erscheinen in der IDE unter *Run As* beziehungsweise *Run Configurations*. Es gibt drei Arten:

| Art | Dateiname | Was sie tut |
| --- | --- | --- |
| **External Tool** | `RunSkript_<Name>.bat.launch` | Startet das gleichnamige Skript aus `scripts/`. Arbeitsverzeichnis ist `scripts/` des Workspaces. |
| **4diac-Deployment** | `Deploy_App_<Name>.launch` | Online-Deploy des System-Eintrags (`.sys`) auf die im Launch ausgewählten Geräte und Ressourcen. |
| **Launch-Gruppe** | `Launch_Deploy_App_<Name>.launch` | Führt mehrere Launches nacheinander aus. |

### Workspace `test_AX`

| Launch / Skript | Inhalt |
| --- | --- |
| `RunSkript_DeployAX.bat.launch` | `RunSkript_DeployAX.bat`: erst `make_libs_manifest.py`, dann `make_4diac_training1_deploy.py` (Boot-Datei-Deploy). |
| `RunSkript_MakeLibsManifestAX.bat.launch` | Nur das Manifest erzeugen (lokal). |
| `RunSkript_PreloadELF_AX.bat.launch` | Knoten vorbereiten (Preload, siehe oben). |
| `RunSkript_CheckMixedPoolImports_AX.bat.launch` | Prüfung auf gemischte Pool-Importe. Für Linux gibt es `RunSkript_CheckMixedPoolImports_AX.sh`. |
| `RunSkript_Build<Pool>_AX.bat.launch` | Pool bauen: ISO-Designer-Projekt übersetzen, alte `.gcf` löschen, `GcfScript.py` und `list_mask_objects.py` ausführen. |
| `RunSkript_ALL_AX.bat.launch` | Führt alle Build-Skripte nacheinander aus. Bei einem Fehler bricht die Kette ab. |
| `Deploy_App_AX.launch` | Online-Deploy von `test_AX.sys` auf `FORTE_PC_AX` und `EMB_RES_AX`. |
| `Launch_Deploy_App_AX.launch` | Gruppe: erst `RunSkript_BuildAX.bat` (wartet auf das Ende), dann `Deploy_App_AX`. |
| `RunSkript_Deploy_DIDO_AX.bat` (ohne Launch) | `make_4diac_training1_deploy_dido.py`. Argumente werden durchgereicht, zum Beispiel eine Adresse statt `logibus.local`. |

Die Build-Skripte gibt es für diese Pools: `BuildAX` (Standardpool), `BuildEmpty`, `BuildPWM`, `BuildPWM12`, `BuildTECU`, `BuildHorse`, `BuildDIDO`, `BuildJoystick`, `BuildTC_SC`, `BuildScroll`, `BuildPI`, `BuildAI`, `BuildAI_Calibrate_2P`, `BuildAI_Calibrate_3P`, `BuildDreieck`, `BuildHystereseHorizontal`, `BuildHystereseVertikal`.

### Workspaces `test_B` und `test_VV`

- `test_B`: Die Skripte heißen `RunSkript_Workspace_<Pool>_B.bat` (und `.sh`). `RunSkript_ALL_B.bat` baut alle Pools. `Launch_Deploy_App_B` führt zuerst `RunSkript_ALL_B.bat` aus und danach `Deploy_App_B` (Ziel `FORTE_PC_B`).
- `test_VV`: Ein Skript `RunSkript_Workspace_VV.bat`. Die `Deploy_App_*`-Launches gehören zu den OPC-UA-Beispielen (`CLIENT_SERVER`, `OPC_UA_RES`, `OPC_UA_SUB`, `PUBLISH_SUBSCRIBE` und Varianten) und laden auf mehrere Geräte (zum Beispiel `FORTE_PC_A` und `FORTE_PC_B`). Die zugehörigen `Launch_Deploy_App_*`-Gruppen enthalten nur den Deploy.

!!! note "Linux"
    Die `.sh`-Varianten führen nur `GcfScript.py` aus. Das Übersetzen des ISO-Designer-Projekts braucht Windows, weil `compile_iso_designer_project.py` die `ISODesigner.exe` aufruft. Der Pfad zur Installation ist im Skript festgelegt (ISO-Designer 5.7.2).

## Typische Abläufe

**Neue Übung schnell testen (Online-Deploy)**

1. Einmalig: `RunSkript_PreloadELF_AX` ausführen und den Knoten neu starten.
2. In der IDE `Deploy_App_AX` ausführen.

**Übung dauerhaft installieren**

1. Boot-Datei aus der 4diac IDE exportieren.
2. `RunSkript_DeployAX` ausführen.
3. Knoten neu starten (Reboot-Button auf `http://<ip>/`).

**Pool im ISO-Designer geändert**

1. Passendes `RunSkript_Build…` ausführen (oder `RunSkript_ALL_AX`).
2. Danach die 4diac IDE aktualisieren und neu deployen.
